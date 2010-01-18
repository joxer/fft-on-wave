CC = g++
FLAGS= -lm -lfftw3 -O2 -lsndfile
FILES= fft.cpp dsp.cpp sound.cpp exception.cpp


deafult: all


lib: 
	$(CC) $(FLAGS) -c $(FILES)
	ar rcs fft.a fft.o dsp.o sound.o exception.o

all: lib
	$(CC) $(FLAGS) main.cpp fft.a -o fftonwave.o

clean:
	rm -f *.o *~ *# *.a