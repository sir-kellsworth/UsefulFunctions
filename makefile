GCC		= g++
MAKE		= make
OPTIMIZE	= -O2 -DSUPPORT_LH7 -DMKSTEMP
CFLAGS		= -std=c++11 -Winline -pipe -g -I/opt/usefulFunctions/

all : useful.so

useful.o : useful.cpp useful.h
	$(GCC) -c $(CFLAGS) useful.cpp -o useful.o

waveform.o : Waveform.cpp Waveform.h
	$(GCC) -c $(CFLAGS) Waveform.cpp -o waveform.o

test : test.cpp
	$(GCC) $(CFLAGS) test.cpp -o test -lUseful

useful.so : useful.cpp useful.h
	$(GCC) $(CFLAGS) -fPIC -shared useful.cpp useful.h -o libUseful.so
	mv libUseful.so libs/

#useful.so : useful.o waveform.o
#	$(GCC) $(CFLAGS) -fPIC -shared useful.o waveform.o -o libUseful.so

install :
	scp useful.h /usr/include/
	scp libs/libUseful.so /usr/local/lib/libUseful.so
	chmod +x /usr/local/lib/libUseful.so
	ldconfig

uninstall :
	rm /usr/include/useful.h
	rm /usr/local/lib/libUseful.so

clean :
	rm libs/libUseful.so
	rm test
