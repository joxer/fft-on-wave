#include <linux/soundcard.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <exception>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <cstring>
#include <vector>
#include <vector>
#include <string>
#include <fstream>
#include <ios>
#include <vector>
#include <fftw3.h>
#include <cmath>
#include <exception>
#include <errno.h>
#include <cstring>
#include <iostream>

#ifndef SOUND_HPP
#define SOUND_HPP
namespace Sound{
  namespace Exception{
    class FFT_Exception: public std::exception{
      int error;
    public:
      FFT_Exception(int) throw();
      virtual ~FFT_Exception() throw();
      const char* what();
    };
    class DSP_Exception: public std::exception{
      int err;
    public:
      DSP_Exception(int error) throw();
      virtual ~DSP_Exception() throw();
      const char* what();
    };
  }
  
  class FFT{
  public:
    static std::vector<double> apply_forward(const std::vector<double>&);
    static std::vector<double> apply_backward(const std::vector<double>&, const std::vector<double>&);
    static std::vector<std::vector<double> > get_real_and_img(const std::vector<double> &);
    static double getMaxFreq(const std::vector<double>&);
  };
  float recognize(const std::vector<double>& , int , int/* , const std::vector<std::string>& */);
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
      void setBuffer(const char*);
      unsigned char* get_buffer() const;
      std::vector<double> get_buffer_double() const;
      bool check(int value);
      int getSize() const;
      int getChannel() const;
      int getBitrate() const;
      int getBit() const;
    };
    
    
    class File{
      std::fstream *stream;
      int size;
      char ch;
    public:
      File(const std::string&, int);
      ~File();
      std::vector<double>read();
      std::vector<double>_read(int offset = 0);
      bool good();
    };
  }
}
#endif
