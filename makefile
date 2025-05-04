all: HelloWorld.exe

HelloWorld.exe: HelloWorld.o
	gcc -o HelloWorld.exe HelloWorld.o

HelloWorld.o: HelloWorld.c
	gcc -c HelloWorld.c

clean:
	rm HelloWorld.o HelloWorld.exe
