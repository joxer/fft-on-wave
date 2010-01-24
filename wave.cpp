#include "sound.hpp"

std::vector<double> Sound::Wave::sine(int bitrate, int freq, int size){
  std::vector<double> buffer;
  for(int i = 0; i < size; i++)
    buffer.push_back(128 + 100*sin(2*3.14*freq*i/bitrate));
  return buffer;
}

std::vector<double> Sound::Wave::square(int bitrate, int freq, int size){
  int tmp;
  std::vector<double> buffer;
  for(int i = 0; i < size; i++){
    tmp = 100*sin(2*3.14*freq*i/bitrate);
    if(tmp < 0)
      buffer.push_back(128*-1);
    else
      buffer.push_back(128*1);
  }
  return buffer;
}

std::vector<double> Sound::Wave::sawtooth(int bitrate, int freq, int size){
  std::vector<double> buffer;
  for(int i = 0; i < size; i+=100){
    for(int k = -50; k < 50;k++){
      buffer.push_back(50.0/k);
    }
  }
  return buffer;
}

std::vector<double> Sound::Wave::triangle(int bitrate, int freq, int size){
  std::vector<double> buffer;
  for(int i = 0; i < size; i+=100){
    for(int k = -50; k < 50;k++){
      buffer.push_back( 50.0/k);
    }
    for(int k = -50; k < 50;k++){
      buffer.push_back(k/50);
    }
  }
  return buffer;
}
