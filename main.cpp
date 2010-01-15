
#include <iostream>
#include <fstream>
#include <vector>
#include "sound.hpp"
using namespace Sound;
int main(){
  try{
    Sound::Acquisition::DSP dsp(44100, 50000);
    //Acquisition::File sound("notes/do.wav", 10000);//dsp.get_buffer_double();
    dsp.read();
    std::vector<double> uh =   dsp.get_buffer_double();
    std::vector<std::vector<double> > tmp = FFT::get_real_and_img(uh);
    std::string buff = FFT::apply_backward_string(tmp[0], tmp[1]);
    dsp.set_buffer(buff.c_str());
    dsp.write();

    
  }catch (std::fstream::failure e){
    std::cout << e.what()  << std::endl;
  }
  
  
  return 0;
}
