#include <iostream>
#include "dsp.hpp"
#include "fft.hpp"
#include "sound.hpp"
#include <vector>

int main(){
  try{
    DSP dsp(88200, 1500);
    std::vector<double> tmp = dsp.get_buffer_double();;
    FFT fft(tmp, 1500);
    int i = 0;
    while(i++ != 100){
      dsp.read();
      dsp.write();
      tmp = dsp.get_buffer_double();
      fft.setBuffer(tmp);
      tmp = fft();
      std::cout << Sound::recognize(tmp, 88200, 1500) << std::endl;
      }
  }catch (DSP_Exception e){
    std::cout << e.what() << std::endl;
  }
  
  
  return 0;
}
