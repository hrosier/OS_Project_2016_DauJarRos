#COMPILE := "gcc -I./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -c"
#SRCS := $(shell ls | egrep -o "[a-zA-Z0-9]*\.c")
SRCS := catapult.c catapultTest.c colorTest.c grab.c grabTest.c init.c mainTest.c movement.c movementTest.c sonar.c sonarTest.c tester.c turn.c turnTest.c position.c compassTest.c
#OBJS := $(shell ls | egrep -o "[a-zA-Z0-9]*\.c" | sed "s/.c/.o/g") 
OBJS := $(SRCS:.c=.o)
TESTS := $(SRCS:Test.c=Test)
.SECONDARY: $(OBJS)
IMPS := sonar.o movement.o grab.o turn.o catapult.o init.o position.o

all: $(OBJS) $(TESTS) 

%.o: %.c %.h
	gcc -I ./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -lpthread -c $< -o $@

%.h: %.c
	cat $^ | grep "^[a-z]" | sed -e "s/{/;/g" > $@

colorTest: init.o colorTest.o 
	gcc $^ -Wall -lm -lev3dev-c -lpthread -o $@

%Test : $(IMPS) %Test.o
	gcc $^ -Wall -lm -lev3dev-c -lpthread -o $@


clean: 
	rm *.o
