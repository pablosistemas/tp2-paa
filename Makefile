CC=g++
CFLAGS=-Wall -std=c++14

all: 2095 2115 1927

2095: src/main2095/main.cc
	mkdir bin || true
	$(CC) $(CFLAGS) src/main2095/main.cc -o bin/2095

2115:
	mkdir bin || true
	$(CC) $(CFLAGS) src/main2115/main.cc -o bin/2115

1927:
	mkdir bin || true
	$(CC) $(CFLAGS) src/main1927/main.cc -o bin/1927

clean:
	rm -rf bin
