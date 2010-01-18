#include <stdio.h>
#include <sndfile.h>

int main(){
  
  SF_INFO info;
  const char *path = "la.wav";
  int fd;
  SNDFILE *file;
  file = sf_open(path,SFM_READ, &info);
  int *i = new int[50000];
  sf_read_int(file, i, 50000);
  sf_close(file);
  return 0;
}
