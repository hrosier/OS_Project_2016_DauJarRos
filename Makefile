CC = gcc
INCLUDE = -I ./ev3dev-c/source/ev3 -I ./headers 
CFLAGS = -O2 -std=gnu99 -W -Wall -Wno-comment -lpthread -lm -lbluetooth
#SRCS := $(shell ls | egrep -o "[a-zA-Z0-9]*\.c")
SRCS := catapult.c color.c grab.c init.c mainTest.c movement.c position.c sonar.c turn.c bluetooth.c final.c
#OBJS := $(shell ls | egrep -o "[a-zA-Z0-9]*\.c" | sed "s/.c/.o/g") 
vpath %.o obj
vpath %.h headers
#OBJS := $(SRCS:.c=.o)
OBJECTS = $(patsubst %.c,obj/%.o,$(SRCS))
HEADERS = $(patsubst %.c,headers/%.h,$(SRCS))
.SECONDARY: $(OBJECTS)

#gcc -I ./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -lpthread -c $< -o $@

all: $(HEADERS) $(OBJECTS) mainTest

$(OBJECTS): | obj
obj :
	@mkdir -p $@

obj/%.o: %.c %.h
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@ 

$(HEADERS): | headers

headers:
	@mkdir -p $@

headers/%.h: %.c
	cat $^ | grep "^[a-z]" | grep -v ";"| sed -e "s/{/;/g" > $@

h : $(SRCS)
	make $(HEADERS)

obj/movement.o : movement.c movement.h turn.c turn.h common_variables.h
obj/turn.o : turn.c turn.h common_variables.h
obj/bluetooth.o : common_variables.h bluetooth.h bluetooth.c

mainTest : $(OBJECTS) mainTest.o
	$(CC) $^ $(INCLUDE) $(CFLAGS) -lm -lev3dev-c -lpthread -o $@

clean: 
	rm obj/*.o
