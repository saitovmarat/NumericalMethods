ifeq ($(wildcard ../build),)
    $(shell mkdir ../build)
endif

all: build compile

rebuild: clean build compile

build: countFunctions printResults 
	@g++ ../build/countFunctions ../build/printResults main.cpp -o ../build/main && clear

countFunctions:
	@g++ -c countFunctions.cpp -o ../build/countFunctions

printResults:
	@g++ -c printResults.cpp -o ../build/printResults

compile:
	@../build/main

clean:
	@rm -rf ../build
