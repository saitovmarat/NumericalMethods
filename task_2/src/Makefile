ifeq ($(wildcard ../build),)
    $(shell mkdir ../build)
endif

all: build compile

rebuild: clean build compile

build: Function
	@g++ -g ../build/Function -g main.cpp -o ../build/main && clear

Function:
	@g++ -c -g Function.cpp -o ../build/Function

compile:
	@../build/main

clean:
	@rm -rf ../build
