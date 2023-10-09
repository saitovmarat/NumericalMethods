all: build compile

rebuild: clean build compile

build:
	g++ -Wall -Wextra -Werror main.cpp -o a && clear

compile:
	./a

clean:
	rm -rf a