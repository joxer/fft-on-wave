#include "fft.hpp"

FFT::FFT(const std::vector<double>& vect, int _size){
  size = _size;
  fin = (fftw_complex*) fftw_malloc(size * sizeof(fftw_complex));
  fout = (fftw_complex*) fftw_malloc(size * sizeof(fftw_complex));
  for(int i = 0; i < size;i++){
    fin[i][0] = vect[i];
    fin[i][1] = 0.0;
  }
}

FFT::FFT(int _size){
  size = _size;
  fin = (fftw_complex*) fftw_malloc(size * sizeof(fftw_complex));
  fout = (fftw_complex*) fftw_malloc(size * sizeof(fftw_complex));
}


void FFT::setBuffer(const std::vector<double>& buffer){
  if(buffer.size() != size)
    throw FFT_Exception(28);
  for(int i = 0; i < size;i++){
     fin[i][0] = buffer[i];
     fin[i][1] = 0.0;
   }
}

std::vector<double> FFT::operator()(){
  std::vector<double> tmp;
  p = fftw_plan_dft_1d(size, fin,fout, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  for(int i = 0; i < size;i++)
    tmp.push_back(sqrt(fout[i][0] * fout[i][0] + fout[i][1] * fout[i][1]));
  return tmp;
}
FFT::~FFT(){
  fftw_destroy_plan(p);
  fftw_free(fin);
  fftw_free(fout);
  fftw_cleanup();
}

static double FFT::getMaxFreq (const std::vector<double>& data)  {
	int i, maxIndex = 1;
	double maxFreq = data[maxIndex];
	
	for (i=2; i < data.size(); i++)  {
		if (data[i] > maxFreq)  {
			maxIndex = i;
			maxFreq = data[i];
		}
	}
	return maxIndex;
}

FFT_Exception::FFT_Exception(int err)  throw(): error(err){}
FFT_Exception::~FFT_Exception() throw(){}
const char* FFT_Exception::what(){
  return strerror(error);
}
