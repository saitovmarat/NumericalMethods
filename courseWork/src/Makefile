ifeq ($(wildcard ../build),)
    $(shell mkdir ../build)
endif

all: build compile

compile: build
	@clear && ../build/main 

build:
	@g++ main.cpp -o ../build/main

clean:
	@rm -rf ../build