all: build compile

rebuild: clean build compile 

build: countFunctions
	g++ ../build/countFunctions main.cpp -o ../build/main && clear

countFunctions:
	g++ -c countFunctions.cpp -o ../build/countFunctions

compile:
	../build/main

clean:
	rm -rf ../build/* 
