all: build compile

rebuild: clean build compile 

build: countF countL
	g++ ../build/countF ../build/countL main.cpp -o ../build/main

countF:
	g++ -c countF.cpp -o ../build/countF

countL:
	g++ -c countL.cpp -o ../build/countL

compile:
	../build/main

clean:
	rm -rf ../build/* 
