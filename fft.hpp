#include <vector>
#include <fftw3.h>
#include <cmath>
#include <exception>
#include <errno.h>
#include <cstring>
#include <iostream>

class FFT_Exception: public std::exception{
  int error;
public:
  FFT_Exception(int) throw();
  virtual ~FFT_Exception() throw();
  const char* what();

};

class FFT{
  int size;
  std::vector<double*> in ,out;
  fftw_complex *fin, *fout;
  fftw_plan p;
public:
  FFT(const std::vector<double>&, int);
  FFT( int);
  virtual ~FFT();
  std::vector<double> operator()();
  static double getMaxFreq(const std::vector<double>&);
  double getFreq(int);
  void setBuffer(const std::vector<double>&);
};
