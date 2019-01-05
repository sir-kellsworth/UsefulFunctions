GCC		= g++
MAKE		= make
OPTIMIZE	= -O2 -DSUPPORT_LH7 -DMKSTEMP
CFLAGS		= -std=c++11 -Winline -pipe -g -I/opt/usefulFunctions/ -I/usr/include/python2.7 -I /opt/usefulFunctions/matplotlib-cpp/

all : useful.so

useful.o : useful.cpp useful.h
	$(GCC) -c $(CFLAGS) -fPIC useful.cpp -o useful.o

waveform.o : Waveform.cpp Waveform.h
	$(GCC) -c $(CFLAGS) -fPIC Waveform.cpp -o waveform.o

test : test.cpp
	$(GCC) $(CFLAGS) test.cpp -o test -lUseful -lpython2.7

#useful.so : useful.cpp useful.h
#	$(GCC) $(CFLAGS) -fPIC -shared useful.cpp useful.h -o libUseful.so
#	mv libUseful.so libs/

useful.so : useful.o waveform.o
	$(GCC) $(CFLAGS) -shared useful.o waveform.o -o libUseful.so
	mv libUseful.so libs/

install :
	scp useful.h /usr/include/
	scp Waveform.h /usr/include/
	scp libs/libUseful.so /usr/local/lib/libUseful.so
	chmod +x /usr/local/lib/libUseful.so
	ldconfig

uninstall :
	rm /usr/include/useful.h
	rm /usr/local/lib/libUseful.so

clean :
	rm *.o
	rm libs/libUseful.so
	rm test
