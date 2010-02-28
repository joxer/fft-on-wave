#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <ios>
#include "sound.hpp"

using namespace Sound;
void StringSplit(std::string str, std::string delim, std::vector<std::string>* results)
{
  int cutAt;
  while( (cutAt = str.find_first_of(delim)) != str.npos )
    {
      if(cutAt > 0)
	{
	  results->push_back(str.substr(0,cutAt));
	}
      str = str.substr(cutAt+1);
    }
  if(str.length() > 0)
    {
      results->push_back(str);
    }
}

std::vector<double> ParseFile(std::string stream){
  std::vector<std::string> tmp;
  std::fstream file(stream.c_str(), std::ios_base::in);
  char ch;
  std::string value;
  while(file.get(ch) && file.good()){
    if(ch != ';')
      value += ch;
    else{
      tmp.push_back(value);
      value = "";
    };
  }
  file.close();
  StringSplit(stream, ";", &tmp);
  std::vector<double> waves;
  for(int i = 0; i < tmp.size();i++)
    waves.push_back(atof(tmp[i].c_str()));
  return waves;

  

}

std::vector<double> CreateSound(std::vector<double> sound){
  std::vector<double> tmp;
  for(int i = 0; i < sound.size();i++){
    std::vector<double> tmpsine = Wave::sine(44100, sound[i], 300);
    for(int j = 0; j < tmpsine.size();j++)
      tmp.push_back(tmpsine[j]);
  }
  return tmp;
}
