#include "sound.hpp"

Sound::Acquisition::DSP::DSP(int _bitrate,  int _size = 15000){

  if(_bitrate < 0|| size < 0)
    throw Exception::Exception(28);
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
    throw Exception::Exception(errno);
  else
    return true;
}

int Sound::Acquisition::DSP::get_size() const{
  return size;
}

int Sound::Acquisition::DSP::get_channel() const{
  return channel;
}

int Sound::Acquisition::DSP::get_bitrate() const{
  return bitrate;
}

int Sound::Acquisition::DSP::get_bit() const{
  return bit;
}

void Sound::Acquisition::DSP::set_buffer(const char* in){
  
  memcpy((char*)buffer,in, size);

}
