CC = gcc
CFLAGS = -I ./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -lpthread -c -o
#COMPILE := "gcc -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c"
#SRCS := $(shell ls | egrep -o "[a-zA-Z0-9]*\.c")
SRCS := catapult.c catapultTest.c colorTest.c grab.c grabTest.c init.c mainTest.c movement.c movementTest.c sonar.c sonarTest.c tester.c turn.c turnTest.c position.c compassTest.c color.c
#OBJS := $(shell ls | egrep -o "[a-zA-Z0-9]*\.c" | sed "s/.c/.o/g") 
OBJS := $(SRCS:.c=.o)
#OBJSDIR := ./obj/
TESTS := $(SRCS:Test.c=Test)
.SECONDARY: $(OBJS)
IMPS := sonar.o movement.o grab.o turn.o catapult.o init.o position.o color.o
	#gcc -I ./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -lpthread -c $< -o $@

all: $(OBJS) $(TESTS) 

%.o: %.c %.h
	gcc $(CFLAGS) $@ $< 

TMP = ^$
%.h: %.c
	cat $^ | grep "^[a-z]" | grep -v ";"| sed -e "s/{/;/g" > $@

movement.o : movement.c movement.h common_variables.h
turn.o : turn.c turn.h common_variables.h

%Test : $(IMPS) %Test.o
	gcc $^ -Wall -lm -lev3dev-c -lpthread -o $@


clean: 
	rm *.o
