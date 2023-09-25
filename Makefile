all: main_module

rebuild: clean all

main_module: count_integral
	gcc -Wall -Werror -Wextra count_integral.o main_module.c -o main_module -lm

count_integral:
	gcc -c -Wall -Werror -Wextra count_integral.c 

clean:
	rm -rf *.o main_module 