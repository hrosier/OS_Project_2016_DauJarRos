#COMPILE := "gcc -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c"
#SRCS := $(shell ls | egrep -o "[a-zA-Z0-9]*\.c")
SRCS := grab.c mainT.c movement.c sonar.c testSonar.c tester.c turn.c
#OBJS := $(shell ls | egrep -o "[a-zA-Z0-9]*\.c" | sed "s/.c/.o/g") 
OBJS = $(SRCS:.c=.o)
#OBJS := grab.o grabT.o mainT.o movement.o .o tester.o turn.o
#DESTS := $(shell ls | egrep -o "[a-zA-Z0-9]*\.c" | tr -d ".c" )
DESTS := grab mainT movement sonar testSonar tester turn 

all: $(OBJS) mainT testSonar

%.o: %.c %.h
	gcc -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c $< -o $@

%.h: %.c
	cat $^ | grep "void" | sed -e "s/{/;/g" > $@

mainT : mainT.o grab.o turn.o movement.o
	gcc $^ -Wall -lm -lev3dev-c -o $@

testSonar : testSonar.o sonar.o 
	gcc $^ -Wall -lm -lev3dev-c -o $@

clean: 
	rm *.o
