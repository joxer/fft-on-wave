#include "sound.hpp"

float Sound::recognize(const std::vector<double>& values, int bitrate){
  float freq, note;
  freq = bitrate * FFT::get_max_freq(values) / values.size() ;
  note =  12* log(freq/440)/log(2);
  return note;
}

Sound::Acquisition::File::File(const std::string& _file, int _size = 5000){
  
  size = _size;
  buffer = new int[size];
  path = _file;

  file = sf_open(path.c_str(), SFM_READ, &info);
  int tmp;
  if(tmp = sf_error(file) != 0)
    throw Exception::Sound_Exception(tmp);
};

Sound::Acquisition::File::~File(){
  free(buffer);
  sf_close(file);
}

std::vector<double>Sound::Acquisition::File::read(){
  std::vector<double> tmp;
  sf_read_int(file, buffer, size);
  for(int k = 0; k < size;tmp.push_back(buffer[k++]));
  return tmp;
}

int Sound::Acquisition::File::get_bitrate() const {
  
  return info.samplerate;

}

int Sound::Acquisition::File::get_channels() const{
  return info.channels;
}
