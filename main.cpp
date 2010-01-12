
#include <iostream>
#include <fstream>
#include "dsp.hpp"
#include "fft.hpp"
#include <vector>
#include "sound.hpp"


int main(){
  try{
    DSP dsp(44100, 4000);
    //Sound::SoundFile sound("notes/0-440.wav", 4000);//dsp.get_buffer_double();
    
    FFT fft(dsp.get_buffer_double(), 4000);
    int i = 0;
    std::vector<double> tmp;
    tmp = fft.apply();
    /*do{
      fft.setBuffer(tmp);
      tmp = fft.apply();
      std::cout << Sound::recognize(tmp, 44100, 4000) << std::endl; 
      dsp.read();
      tmp = dsp.get_buffer_double();
    }while(i++ != 100);
    */
  }catch (std::fstream::failure e){
    std::cout << e.what()  << std::endl;
  }
  
  
  return 0;
}
