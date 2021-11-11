CC=g++
CFLAGS=-Wall -std=c++17
BINS=ascensor

all: clean ascensor

ascensor:
	$(CC) $(CFLAGS) -o ascensor ascensor.cpp

clean:
	@echo " [CLN] Removing binary files"
	@rm -f $(BINS)