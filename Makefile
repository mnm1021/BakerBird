all: ahocorasic

ahocorasic: ahocorasic.cpp ahocorasic.h
	g++ -o ahocorasic ahocorasic.cpp

clean:
	rm ahocorasic
