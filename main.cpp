#include <iostream>
#include <fstream>
#include "dsp.hpp"
#include "fft.hpp"
#include <vector>
#include "sound.hpp"


int main(){
  try{
    std::vector<std::string> _note;
    _note.push_back("Do");
    _note.push_back("Re");
    _note.push_back("Mi");
    _note.push_back("Fa");
    _note.push_back("Sol");
    _note.push_back("La");
    _note.push_back("Si");
    
    // DSP dsp(88200, 20000);
    Sound::SoundFile sound("notes/0-440.wav", 4000);//dsp.get_buffer_double();
    
    FFT fft(sound.read(), 4000);
    int i = 0;
    std::vector<double> tmp = sound.read();
    do{
      fft.setBuffer(tmp);
      tmp = fft();
      std::cout << Sound::recognize(tmp, 44100, 4000, _note) << std::endl; 
      tmp = sound.read();
    }while(sound.good());
    
  }catch (std::fstream::failure e){
    std::cout << e.what()  << std::endl;
  }
  
  
  return 0;
}
