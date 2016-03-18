target=libfftw_blitz.a

IFITS =
LFITS =-lcfitsio -lfio

all:$(target)

a.out:	try.o fftw_blitz.o
	g++ try.o fftw_blitz.o ../fio/fio.o  ${LFITS} ../fio/fits_trait.o -o a.out -L/usr/local/lib -lblitz -lfftw3_threads -lfftw3f_threads -lfftw3 -lfftw3f


try.o:try.cc fftw_blitz.hpp
	g++ -c try.cc -I/usr/local/include ${IFITS}


fftw_blitz.o:fftw_blitz.cpp fftw_blitz.hpp
	g++ -c fftw_blitz.cpp -I/usr/local/include

libfftw_blitz.a:fftw_blitz.o
	ar rv $@ $^

clean:
	rm -f *.o
	rm -f *~
