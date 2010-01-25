#include <linux/soundcard.h>
#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <cstring>
#include <vector>
#include <string>
#include <fstream>
#include <ios>
#include <fftw3.h>
#include <cmath>
#include <exception>
#include <errno.h>
#include <sndfile.h>
#ifndef SOUND_HPP
#define SOUND_HPP
namespace Sound{
  namespace Exception{
    class Exception: public std::exception{
      int error;
    public:
      Exception(int) throw();
      virtual ~Exception() throw();
      const char* what();
    };
    class Sound_Exception: public std::exception{
      int error;
    public:
      Sound_Exception(int) throw();
      virtual ~Sound_Exception() throw();
      const char* what();
    };

  }
  
  

  class FFT{
  public:
    static std::vector<double> apply_forward(const std::vector<double>&);
    static std::vector<double> apply_backward(const std::vector<double>&, const std::vector<double>&);
    static std::string apply_backward_string(const std::vector<double>&, const std::vector<double>&);
    static std::vector<std::vector<double> > get_real_and_img(const std::vector<double> &);
    static double get_max_freq(const std::vector<double>&);
  };
  float recognize(const std::vector<double>& , int);
  namespace Acquisition{
    class DSP{
      int fd, size, bitrate, bit, channel;
      int status;
      unsigned char *buffer;
    public:
      DSP(int ,int );
      virtual ~DSP();
      void read();
      void write();
      void set_buffer(const char*);
      unsigned char* get_buffer() const;
      std::vector<double> get_buffer_double() const;
      bool check(int value);
      int get_size() const;
      int get_channel() const;
      int get_bitrate() const;
      int get_bit() const;
    };
    
    
    class File{
      SF_INFO info;
      std::string path;
      SNDFILE *file;
      int *buffer;
      int size;
    public:
      File(const std::string&, int);
      ~File();
      std::vector<double>read();
      int get_bitrate() const;
      int get_channels() const;
    };
  }

  namespace Wave {
    std::vector<double> sine(int, int, int);
    std::vector<double> square(int, int, int);
    std::vector<double> sawtooth(int, int, int);
    std::vector<double> triangle(int, int, int);
    std::vector<double> sum(std::vector<double>, std::vector<double>);
  }
  
}
#endif
