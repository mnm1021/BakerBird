all: ahocorasic kmp

ahocorasic: ahocorasic.cpp ahocorasic.h
	g++ -o ahocorasic ahocorasic.cpp

kmp: kmp.cpp kmp.h
	g++ -o kmp kmp.cpp

clean:
	rm ahocorasic kmp
