CC = g++
FLAGS= -lm -lfftw3 -O2
FILES= fft.cpp dsp.cpp sound.cpp


deafult: all


lib: 
	$(CC) $(FLAGS) -c $(FILES)
	ar rcs fft.a fft.o dsp.o sound.o

all: lib
	$(CC) $(FLAGS) main.cpp fft.a -o fftonwave.o

clean:
	rm -f *.o *~ *# *.a