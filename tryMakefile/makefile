CC=g++
CFLAGS= -c -Wall
all: test.exe
test.exe: main.obj mathwork.obj printwork.obj
	$(CC) main.obj mathwork.obj printwork.obj -o test
main.obj:main.cpp
	$(CC) $(CFLAGS) main.cpp -o main.obj
mathwork.obj:mathwork.cpp
	$(CC) $(CFLAGS) mathwork.cpp -o mathwork.obj
printwork.obj:printwork.cpp
	$(CC) $(CFLAGS) printwork.cpp -o printwork.obj
clean:
	del *.obj test.exe