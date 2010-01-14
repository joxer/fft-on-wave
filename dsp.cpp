#include "sound.hpp"

Sound::Exception::DSP_Exception::DSP_Exception(int error) throw(){
  err = error;
}

Sound::Exception::DSP_Exception::~DSP_Exception() throw(){};
const char* Sound::Exception::DSP_Exception::what(){ 
  return strerror(err);
};


Sound::Acquisition::DSP::DSP(int _bitrate,  int _size = 15000){

  if(_bitrate < 0|| size < 0)
    throw Exception::DSP_Exception(28);
  bitrate = _bitrate;
  bit = 8;
  channel = 1;
  size = _size;
  fd = open("/dev/dsp", O_RDWR);
  check(fd);
  buffer = (unsigned char*) malloc(size*sizeof(unsigned char));
  status = ioctl(fd, SOUND_PCM_WRITE_BITS, &bit);
  check(status);
  status = ioctl(fd, SOUND_PCM_WRITE_CHANNELS, &channel);
  check(status);
  status = ioctl(fd, SOUND_PCM_WRITE_RATE, &bitrate);
  check(status);
};
Sound::Acquisition::DSP::~DSP(){
  close(fd);
}
void Sound::Acquisition::DSP::read(){
  status = ::read(fd, buffer,size*sizeof(unsigned char) );
  check(status);
}
void Sound::Acquisition::DSP::write(){
  status = ::write(fd, buffer, size*sizeof(unsigned char));
  check(status);
  status = ioctl(fd, SOUND_PCM_SYNC, 0); 
  check(status);
  
}
unsigned char* Sound::Acquisition::DSP::get_buffer() const{
  return buffer;
}

std::vector<double> Sound::Acquisition::DSP::get_buffer_double() const{
  std::vector<double> tmp;
  for(int i = 0; i < size;i++)
    tmp.push_back((double)buffer[i]);
  return tmp;
}

bool Sound::Acquisition::DSP::check(int value){
  if(value < 0)
    throw Exception::DSP_Exception(errno);
  else
    return true;
}

int Sound::Acquisition::DSP::getSize() const{
  return size;
}

int Sound::Acquisition::DSP::getChannel() const{
  return channel;
}

int Sound::Acquisition::DSP::getBitrate() const{
  return bitrate;
}

int Sound::Acquisition::DSP::getBit() const{
  return bit;
}

void Sound::Acquisition::DSP::setBuffer(const char* in){
  
  memcpy((char*)buffer,in, size);

}
