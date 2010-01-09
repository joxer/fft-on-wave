#include <vector>
#include <string>
#include <fstream>
#include <ios>
#include "fft.hpp"


namespace Sound{
  
  float recognize(const std::vector<double>& values, int bitrate, int size, const std::vector<std::string>& _note){
    float freq, note;
    freq = bitrate * FFT::getMaxFreq(values) / size;
    note =  12* log(freq/440)/log(2);
    return rint(note);
  }
  
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
};
