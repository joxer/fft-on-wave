#include "sound.hpp"
std::vector<double> Sound::FFT::apply_forward(const std::vector<double> &vect){
  int size = vect.size();
  std::vector<double> tmp;
  fftw_complex *fin, *fout;
  fftw_plan p;
  
  // TO DO
  // avoid memory leak here

  fin = (fftw_complex*) fftw_malloc(size * sizeof(fftw_complex)); // <-
  if(fin == NULL)
    throw Exception::FFT_Exception(errno);
  fout = (fftw_complex*) fftw_malloc(size * sizeof(fftw_complex)); // <-
  if(fout == NULL)
    throw Exception::FFT_Exception(errno);
  
  //end to do
  //PS dammit static

  for(int i = 0; i < size;i++){
    fin[i][0] = vect[i];
    fin[i][1] = 0.0;
  }
  
  p = fftw_plan_dft_1d(size, fin,fout, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  for(int i = 0; i < size;i++)
    tmp.push_back(sqrt(fout[i][0] * fout[i][0] + fout[i][1] * fout[i][1]));
  
  fftw_destroy_plan(p);
  fftw_free(fin);
  fftw_free(fout);
  fftw_cleanup();
  
  return tmp;
}

std::vector<std::vector<double> > Sound::FFT::get_real_and_img(const std::vector<double> &vect){
  int size = vect.size();
  std::vector<std::vector<double> > tmp;
  std::vector<double> real, img;
  fftw_complex *fin, *fout;
  fftw_plan p;
  tmp.push_back(real); // really crap solution :(
  tmp.push_back(img); // i'm really sad
  // TO DO
  // avoid memory leak here

  fin = (fftw_complex*) fftw_malloc(size * sizeof(fftw_complex)); // <-
  if(fin == NULL)
    throw Exception::FFT_Exception(errno);
  fout = (fftw_complex*) fftw_malloc(size * sizeof(fftw_complex)); // <-
  if(fout == NULL)
    throw Exception::FFT_Exception(errno);
  
  //end to do
  //PS dammit static

  for(int i = 0; i < size;i++){
    fin[i][0] = vect[i];
    fin[i][1] = 0.0;
  }
  
  p = fftw_plan_dft_1d(size, fin,fout, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  for(int i = 0; i < size;i++){
    tmp[0].push_back(fout[i][0]);
    tmp[1].push_back(fout[i][1]);
  }
  fftw_destroy_plan(p);
  fftw_free(fin);
  fftw_free(fout);
  fftw_cleanup();
  
  return tmp;
}

std::vector<double> Sound::FFT::apply_backward(const std::vector<double> &real, const std::vector<double> &img){
  int size = real.size();
  std::vector<double> tmp;
  fftw_complex *fin, *fout;
  fftw_plan p;
  
  // TO DO
  // avoid memory leak here

  fin = (fftw_complex*) fftw_malloc(size * sizeof(fftw_complex)); // <-
  if(fin == NULL)
    throw Exception::FFT_Exception(errno);
  fout = (fftw_complex*) fftw_malloc(size * sizeof(fftw_complex)); // <-
  if(fout == NULL)
    throw Exception::FFT_Exception(errno);
  
  //end to do
  //PS dammit static

  for(int i = 0; i < size;i++){
    fin[i][0] = real[i];
    fin[i][1] = img[i];
  }
  
  p = fftw_plan_dft_1d(size, fin,fout, FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  for(int i = 0; i < size;i++)
    tmp.push_back(fout[i][0]/size);
  fftw_destroy_plan(p);
  fftw_free(fin);
  fftw_free(fout);
  fftw_cleanup();
  return tmp;
}

std::string Sound::FFT::apply_backward_string(const std::vector<double> &real, const std::vector<double> &img){
  int size = real.size();
  std::string stream;
  fftw_complex *fin, *fout;
  fftw_plan p;
  
  // TO DO
  // avoid memory leak here
  
  fin = (fftw_complex*) fftw_malloc(size * sizeof(fftw_complex)); // <-
  if(fin == NULL)
    throw Exception::FFT_Exception(errno);
  fout = (fftw_complex*) fftw_malloc(size * sizeof(fftw_complex)); // <-
  if(fout == NULL)
    throw Exception::FFT_Exception(errno);
  
  //end to do
  //PS dammit static

  for(int i = 0; i < size;i++){
    fin[i][0] = real[i];
    fin[i][1] = img[i];
  }
  
  p = fftw_plan_dft_1d(size, fin,fout, FFTW_BACKWARD, FFTW_ESTIMATE);
  fftw_execute(p);
  for(int i = 0; i < size;i++)
    stream += (unsigned char)(fout[i][0]/size);
  fftw_destroy_plan(p);
  fftw_free(fin);
  fftw_free(fout);
  fftw_cleanup();
  return stream;
}



double Sound::FFT::get_max_freq (const std::vector<double>& data)  {
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

Sound::Exception::FFT_Exception::FFT_Exception(int err)  throw(): error(err){}
Sound::Exception::FFT_Exception::~FFT_Exception() throw(){}
const char* Sound::Exception::FFT_Exception::what(){
  return strerror(error);
}
