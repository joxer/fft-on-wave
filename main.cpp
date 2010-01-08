#include <iostream>
#include "dsp.hpp"
#include "fft.hpp"
#include <vector>
int main(){
  try{
    DSP dsp(88200, 8, 1);
    std::vector<double> tmp = dsp.get_buffer_double();;
    FFT fft(tmp, 15000);
    int i = 0;
    while(i++ != 100){
      dsp.read();
      dsp.write();
      tmp = dsp.get_buffer_double();
      fft.setBuffer(tmp);
      tmp = fft();
      int  freq = 88200 * fft.getMaxFreq(tmp) / (15000);
      int note = (int)rint(12* log(88200 * fft.getMaxFreq(tmp) / (15000 )/440)/log(2));
      std::cout << note << std::endl;
      }
  }catch (DSP_Exception e){
    std::cout << e.what() << std::endl;
  }
  
  
  return 0;
}
