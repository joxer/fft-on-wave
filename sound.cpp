#include "sound.hpp"


/*
  float Sound::recognize(const std::vector<double>& values, int bitrate, int size, const std::vector<std::string>& _note){
  float freq, note;
  freq = bitrate * FFT::getMaxFreq(values) / size;
  note =  12* log(freq/440)/log(2);
  return rint(note);
}*/

std::vector<double> file(const std::string& file){
  std::vector<double> tmp;
  std::fstream stream(file.c_str(), std::ios_base::in);
    char ch;
    int i = 0;
    while(stream.get(ch) && i++ < 50000){
      tmp.push_back((double)(unsigned char) ch);
    }
    return tmp;
}
Sound::Acquisition::File::File(const std::string& file, int _size){
  size = _size;
  stream = new std::fstream(file.c_str(), std::ios_base::in);
  //stream->exceptions(std::ios::badbit | std::ios::failbit | std::ios::eofbit);
  stream->seekp(11); //to jump the header part
  if(stream->fail());
    //throw std::exception;
};

Sound::Acquisition::File::~File(){
  stream->close();
}

std::vector<double>Sound::Acquisition::File::read(){
  int i = 0;
  std::vector<double> tmp;
  while(!stream->eof() && i++ != size){
    stream->get(ch);
    tmp.push_back((double)(unsigned char)ch);
  }
  return tmp;
}

std::vector<double>Sound::Acquisition::File::_read(int offset){
  stream->seekp(offset);
  int i = 0;
  std::vector<double> tmp;
  while(stream->good() && i++ != size){
    stream->get(ch);
    tmp.push_back((double)(unsigned char)ch);
  }
  return tmp;
}

bool Sound::Acquisition::File::good(){
  return stream->good();
}
