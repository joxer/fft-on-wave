#include <vector>
#include <fftw3.h>
#include <cmath>
class FFT{
  int size;
  std::vector<double*> in ,out;
  fftw_complex *fin, *fout;
  fftw_plan p;
public:
  FFT(const std::vector<double>&, int);
  ~FFT();
  std::vector<double> operator()();
  double getMaxFreq(const std::vector<double>&);
  double getFreq(int);
  void setBuffer(const std::vector<double>&);
};
