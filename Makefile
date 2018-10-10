all: ahocorasic kmp hw1

ahocorasic: ahocorasic.cpp ahocorasic.h
	g++ -o ahocorasic ahocorasic.cpp

kmp: kmp.cpp kmp.h
	g++ -o kmp kmp.cpp

hw1: hw1.cpp ahocorasic.h kmp.h
	g++ -o hw1 hw1.cpp

clean:
	rm ahocorasic
	rm kmp
	rm hw1
