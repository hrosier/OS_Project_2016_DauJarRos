

all:
	gcc -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c tester.c -o tester.o
	gcc tester.o -Wall -lm -lev3dev-c -o tester

runT:
	gcc -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c runTest.c -o runTest.o
	gcc runTest.o grab.o -Wall -lm -lev3dev-c -o runTest

grabT:
	gcc -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c grabT.c -o grabT.o
	gcc grabT.o -Wall -lm -lev3dev-c -o grabTest

grab:
	gcc -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c grab.c -o grab.o

movement:
	gcc -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c movement.c -o movement.o

test:
	gcc -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c mainT.c -o mainT.o

linker:
	gcc *.o -Wall -lm -lev3dev-c -o run

