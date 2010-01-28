#include "sound.hpp"
#include <cstdlib>
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
      buffer.push_back(127);
    else
      buffer.push_back(129);
  }
  return buffer;
}

std::vector<double> Sound::Wave::sawtooth(int bitrate, int freq, int size){
  std::vector<double> buffer;
  for(int i = 0; i < size; i+=1){
    std::cout << 128*(100.0/(i%100)) << std::endl;
    buffer.push_back(128*(100.0/(i%100)));
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

int max(int i, int b){
  if(i > b)
    return i;
  else
    return b;
}

int min(int i, int b){
  if(i < b)
    return i;
  else
    return b;
}

std::vector<double> Sound::Wave::sum(std::vector<double> first, std::vector<double> second){
  
  std::vector<double> result;
  for(int i = 0; i < first.size();i++){
    result.push_back(0);
    for(int j = max(0, i-first.size()+1); j < min(i, 500);j++){
      result[i] += (first[j] * (second[i-j] ))/128;
    } 
 
  }
  return result;
}
