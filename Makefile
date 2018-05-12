CC=g++
CFLAGS=-Wall -std=c++14

all: 2095 2115

2095: src/main2095/main.cc
	mkdir bin || true
	$(CC) $(CFLAGS) src/main2095/main.cc -o bin/2095

2115:
	mkdir bin || true
	$(CC) $(CFLAGS) src/main2095/main.cc -o bin/2115

clean:
	rm -rf bin