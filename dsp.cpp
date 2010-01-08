#include "dsp.hpp"
DSP_Exception::DSP_Exception(int error) throw(){
  err = error;
}

DSP_Exception::~DSP_Exception() throw(){};
const char* DSP_Exception::what(){ 
  return strerror(err);
};


DSP::DSP(int _bitrate, int _bit, int _channel): bitrate(_bitrate), bit(_bit), channel(_channel){
  fd = open("/dev/dsp", O_RDWR);
  check(fd);
  size = 15000;
  buffer = (unsigned char*) malloc(size*sizeof(unsigned char));
  status = ioctl(fd, SOUND_PCM_WRITE_BITS, &bit);
  check(status);
  status = ioctl(fd, SOUND_PCM_WRITE_CHANNELS, &channel);
  check(status);
  status = ioctl(fd, SOUND_PCM_WRITE_RATE, &bitrate);
  check(status);
};
DSP::~DSP(){
  close(fd);
}
void DSP::read(){
  status = ::read(fd, buffer,size*sizeof(unsigned char) );
  check(status);
}
void DSP::write(){
  status = ::write(fd, buffer, size*sizeof(unsigned char));
  check(status);
  status = ioctl(fd, SOUND_PCM_SYNC, 0); 
  check(status);
  
}
unsigned char* DSP::get_buffer() const{
  return buffer;
}

std::vector<double> DSP::get_buffer_double() const{
  std::vector<double> tmp;
  for(int i = 0; i < size;i++)
    tmp.push_back((double)buffer[i]);
  return tmp;
}

bool DSP::check(int value){
  if(value < 0)
    throw DSP_Exception(errno);
  else
    return true;
}

int DSP::getSize() const{
  return size;
}

int DSP::getChannel() const{
  return channel;
}

int DSP::getBitrate() const{
  return bitrate;
}

int DSP::getBit() const{
  return bit;
}
