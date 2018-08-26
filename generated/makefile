all : testProgram

testProgram : main.o source1.o source2.o
	g++ main.o source1.o source2.o -o testProgram
	rm -f *o

main.o : main.cpp
	g++ -c main.cpp

source1.o : source1.cpp
	g++ -c source1.cpp

source2.o : source2.cpp
	g++ -c source2.cpp

clean :
	rm -f *o makeGen