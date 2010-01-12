#include <vector>
#include <string>
#include <fstream>
#include <ios>
#include "fft.hpp"
#include "dsp.hpp"
#ifndef SOUND_HPP
#define SOUND_HPP
namespace Sound{
  
  


  //float recognize(const std::vector<double>& , int , int/* , const std::vector<std::string>& */);
  class SoundFile{
    std::fstream *stream;
    int size;
    char ch;
  public:
    SoundFile(const std::string&, int);
    ~SoundFile();
    std::vector<double>read();
    std::vector<double>_read(int offset = 0);
    bool good();
  };
};
#endif
