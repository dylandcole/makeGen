all : makeGen

makeGen : exSelect.o executable.o
	g++ exSelect.o executable.o -o makeGen

exSelect.o : exSelect.cpp
	g++ -c exSelect.cpp

executable.o : executable.cpp
	g++ -c executable.cpp

clean :
	rm -f *o makeGen