ifeq ($(wildcard ../build),)
    $(shell mkdir ../build)
endif

all: build compile

rebuild: clean build compile

build: 
	@g++ main.cpp -o ../build/main

compile:
	@clear && ../build/main

clean:
	@rm -rf ../build 