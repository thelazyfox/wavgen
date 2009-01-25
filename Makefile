CXX=g++
CXXFLAGS=-Wall

all: wavgen

Tone.o: Tone.cpp Tone.h
	$(CXX) $(CXXFLAGS) -c Tone.cpp -o Tone.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

wavgen: Tone.o main.o
	$(CXX) $(LDFLAGS)  main.o Tone.o -lm -o wavgen

clean:
	rm *.o wavgen
