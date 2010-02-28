#include <sndfile.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "sound.hpp"
#include "parser.cpp"
#include "x11utils.hpp"
using namespace Sound;
int main(){
  try{
    /*
      
    std::vector<double> square1 = Sound::Wave::sine(44100, 440, 50000);
    std::vector<double> square2 = Sound::Wave::square(44100, 440, 50000);
    std::vector<double> result = Sound::Wave::sum(square1, square2);
    /*for(int i= 0; i < sine.size();i++){
      result.push_back(0);
      for(int j = -128; j < 128;j++)
      result[i] += sine[i] * (square[i] - j)/(128*128);
      //std::cout << result[i] << std::endl;
    }
    */
    /*
    std::string tmpp = "";
    for(int i = 0; i < result.size();i++){
      tmpp += (unsigned char)result[i];
    }
    dsp.set_buffer(tmpp.c_str());
    dsp.write();
    
    dsp.read();
    std::vector<double> tmp = dsp.get_buffer_double();
    dsp.write();
    std::vector<double> tmp2 = FFT::apply_forward(tmp);
    std::cout << recognize(tmp2, 44100) << std::endl;
    

    std::vector<double> s = CreateSound(ParseFile("notes.txt"));
    std::string tmpp = "";
    for(int i = 0; i < s.size();i++){
      tmpp += (unsigned char)s[i];
    }
    dsp.set_buffer(tmpp.c_str());
    dsp.write();
    */

    /*
    Sound::Acquisition::DSP dsp(44100, 10000);
    std::vector<double> tmp, tmp2;
    int i;
    while(1){
      dsp.read();
      tmp = dsp.get_buffer_double();
      tmp2 = FFT::apply_forward(tmp);
      //dsp.write();
      i = (recognize(tmp2, 44100)) +12; 
      std::cout << i << std::endl;
      if(i == 0  && i < 30 && i > -30)
	presskey(XK_DOWN);
      else if(i == 2 && i < 30 && i > -30 )
	presskey(XK_UP);
      else if(i == 3 && i < 30 && i > -30 )
	mouseClick(1);//XK_Left);
      else if(i == -2 && i < 30 && i > -30 )
	presskey(XK_LEFT);
      else if(i == -4 && i < 30 && i> -30)
	presskey(XK_RIGHT);
      
    }
    */

    Acquisition::File file(std::string("01_aria.wav"), 300);
    std::vector<double> tmp;
    for(int i = 0; i < 2000;i++)
      {
	
	int c = get_freq(FFT::apply_forward(file.read()), 44100);
	std::cout <<  c << ";" ;
      }
    
    
    std::vector<double> s = CreateSound(ParseFile("notes.txt"));
    Acquisition::DSP dsp(44100, s.size());
    std::string tmpp = "";
    for(int i = 0; i < s.size();i++){
      tmpp += (unsigned char)s[i];
    }
    dsp.set_buffer(tmpp.c_str());
    dsp.write();
    
  }catch (Sound::Exception::Exception e){
    std::cout << e.what()  << std::endl;
  }
  
  
  return 0;
}
