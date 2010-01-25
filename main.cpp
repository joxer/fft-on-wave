#include <sndfile.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "sound.hpp"
using namespace Sound;
int main(){
  try{
    Sound::Acquisition::DSP dsp(44100, 50000);
    std::vector<double> square1 = Sound::Wave::square(44100, 440, 50000);
    std::vector<double> square2 = Sound::Wave::square(44100, 440, 50000);
    std::vector<double> square = Sound::Wave::sum(square1, square2);
    /*for(int i= 0; i < sine.size();i++){
      result.push_back(0);
      for(int j = -128; j < 128;j++)
      result[i] += sine[i] * (square[i] - j)/(128*128);
      //std::cout << result[i] << std::endl;
    }
    */
    std::string tmpp = "";
    for(int i = 0; i < square.size();i++){
      tmpp += (unsigned char)square[i];
    }
    dsp.set_buffer(tmpp.c_str());
    dsp.write();
    
  }catch (Sound::Exception::Exception e){
    std::cout << e.what()  << std::endl;
  }
  
  
  return 0;
}
