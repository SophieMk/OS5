.PHONY: all clean

all: build test

# lib1.c -> d1.o -> libd1.so -(runtime)-> prog2
build:
	gcc -fPIC -c lib1.c -o d1.o
	gcc -fPIC -c lib2.c -o d2.o

	@# `-lm` -- libmath
	gcc -shared d1.o -lm -o libd1.so
	gcc -shared d2.o -lm -o libd2.so

	@# `-rpath=.` -- сообщаем линковщику (`ld`), что при запуске программы
	@# ей нужно искать динамические библиотеки в текущем каталоге.
	@#
	@# `-L.` -- сообщаем линковщику, что и ему самому нужно искать библиотеки
	@# в текущем каталоге (в частности, чтобы проверить корректность их
	@# использования).
	gcc prog1.c -L. -Wl,-rpath=. -ld1 -o prog1
	gcc prog2.c -L. -Wl,-rpath=. -ldl -o prog2

test:
	echo "1 10 0.2  2 10" | ./prog1
	echo "1  1 10 0.2  2 10  0  1 10 0.2  2 10" | ./prog2

clean:
	rm d1.o d2.o libd1.so libd2.so prog1 prog2
