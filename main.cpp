#include <sndfile.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "sound.hpp"
using namespace Sound;
int main(){
  try{
    //Sound::Acquisition::DSP dsp(44100, 50000);
    Acquisition::File sound("notes/do.wav", 6000);//dsp.get_buffer_double();
    std::vector<double> tmp = FFT::apply_forward(sound.read());
    std::cout << recognize(tmp, sound.get_bitrate()) << std::endl;
    
  }catch (std::fstream::failure e){
    std::cout << e.what()  << std::endl;
  }
  
  
  return 0;
}
