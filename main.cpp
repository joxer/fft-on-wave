
#include <iostream>
#include <fstream>
#include <vector>
#include "sound.hpp"
using namespace Sound;
int main(){
  try{
    Sound::Acquisition::DSP dsp(44100, 10000);
    Acquisition::File sound("notes/do.wav", 10000);//dsp.get_buffer_double();
    dsp.read();
    std::vector<double> uh = sound.read();
    std::vector<std::vector<double> > tmp = FFT::get_real_and_img(uh);
    std::vector<double> tmp2 = FFT::apply_backward(tmp[0], tmp[1]);
    std::string buff = "";
    for(int i = 0; i < tmp2.size();i++)
      buff += (unsigned char)tmp2[i];
    dsp.setBuffer(buff.c_str());
    dsp.write();

    
  }catch (std::fstream::failure e){
    std::cout << e.what()  << std::endl;
  }
  
  
  return 0;
}
