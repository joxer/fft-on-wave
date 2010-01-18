#include "sound.hpp"
Sound::Exception::Exception::Exception(int err)  throw(): error(err){}
Sound::Exception::Exception::~Exception() throw(){}
const char* Sound::Exception::Exception::what(){
  return strerror(error);
}

Sound::Exception::Sound_Exception::Sound_Exception(int err)  throw(): error(err){}
Sound::Exception::Sound_Exception::~Sound_Exception() throw(){}
const char* Sound::Exception::Sound_Exception::what(){
  return sf_error_number(error);
}

