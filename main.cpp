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
    //Acquisition::File sound("notes/do.wav", 6000);//dsp.get_buffer_double();
    /* std::vector<double> x;// = FFT::apply_forward(sound.read());
    std::vector<double> y;
    for(int i =0; i < 50000;i++){
      x.push_back(24000*sin(2*3.14*261*i));
      y.push_back(24000*cos(2*3.14*261*i));
    }
    */
    

    //for(int i = 0 ; i < 50000;i++){
      // the value must be multiplicated for 100 cause the signal vary bewteen -1 and 1 and add 128 cause the char is between 256 and 0
      //tmp.push_back(128 + (100*sin(2*3.14*440*i/44100)));
      //      std::cout << 128 + 100*sin(2*3.14*440*i/44100) << std::endl;
    //}


    //    std::cout << recognize(tmp, 44100) << std::endl;
    
    std::vector<double> tmp = Sound::Wave::triangle(44100, 440, 50000);// = FFT::apply_backward(x,y);
    std::string tmpp = "";
    for(int i = 0; i < tmp.size();i++)
      tmpp += 128 + (char)tmp[i];
    dsp.set_buffer(tmpp.c_str());
    dsp.write();
    tmp = Sound::Wave::sawtooth(44100, 440, 50000);// = FFT::apply_backward(x,y);
    tmpp = "";
    for(int i = 0; i < tmp.size();i++)
      tmpp += 128 + (char)tmp[i];
    dsp.set_buffer(tmpp.c_str());
    dsp.write();
  }catch (Sound::Exception::Exception e){
    std::cout << e.what()  << std::endl;
  }
  
  
  return 0;
}
