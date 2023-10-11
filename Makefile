all: build compile

rebuild: clean build compile

build:
	g++ main.cpp -o main && clear

compile:
	./main

clean:
	rm -rf main *.out