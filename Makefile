CC = g++
FLAGS= -lm -lfftw3 -O2 -lsndfile -L/usr/X11R6/lib -lX11
FILES= fft.cpp dsp.cpp sound.cpp exception.cpp wave.cpp parser.cpp -ffast-math


default: all

main: 
	$(CC) $(FLAGS) main.cpp fft.a -o fftonwave
lib: 
	$(CC) $(FLAGS) -c $(FILES)
	ar rcs fft.a fft.o dsp.o sound.o exception.o wave.o parser.o

all: lib
	$(CC) $(FLAGS) main.cpp fft.a -o fftonwave

clean:
	rm -f *.o *~ *# *.a