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
class DSP_Exception: public std::exception{
  int err;
public:
  DSP_Exception(int error) throw();
  virtual ~DSP_Exception() throw();
  const char* what();
};

class DSP{
  int fd, size, bitrate, bit, channel;
  int status;
  unsigned char *buffer;
public:
  DSP(int ,int );
  virtual ~DSP();
  void read();
  void write();
  unsigned char* get_buffer() const;
  std::vector<double> get_buffer_double() const;
  bool check(int value);
  int getSize() const;
  int getChannel() const;
  int getBitrate() const;
  int getBit() const;
};

