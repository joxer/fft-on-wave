CC = g++
FLAGS= -lm -lfftw3 -O2
FILES= fft.cpp dsp.cpp

lib: 
	$(CC) $(FLAGS) -c $(FILES)
	ar rcs fft.a fft.o dsp.o

all: lib
	$(CC) $(FLAGS) main.cpp fft.a -o fftonwave.o

deafult: all

clean:
	rm -f *.o *.~ *#