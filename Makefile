CC = gcc
INCLUDE = -I ./ev3dev-c/source/ev3 -I ./headers 
CFLAGS = -O2 -std=gnu99 -W -Wall -Wno-comment -lpthread -lm -lbluetooth
SRCS := bluetooth.c catapult.c color.c final.c grab.c init.c localisation.c movement.c sonar.c testFunctions.c turn.c
vpath %.o obj
vpath %.h headers
#OBJS := $(SRCS:.c=.o)
OBJECTS = $(patsubst %.c,obj/%.o,$(SRCS))
HEADERS = $(patsubst %.c,headers/%.h,$(SRCS))
.SECONDARY: $(OBJECTS)

#gcc -I ./ev3dev-c/source/ev3 -O2 -std=gnu99 -W -Wall -Wno-comment -lpthread -c $< -o $@

all: $(OBJECTS) mainTest main
#all: $(HEADERS) $(OBJECTS) mainTest

$(OBJECTS): | obj
mainTest.o: | obj
main.o : | obj

obj :
	@mkdir -p $@

obj/%.o: %.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@ 

obj/mainTest.o: mainTest.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@ 

obj/main.o: main.c
	$(CC) $(INCLUDE) $(CFLAGS) -c $< -o $@ 


#$(HEADERS): | headers
#
#headers:
#	@mkdir -p $@
#
#headers/%.h: %.c
#	cat $^ | grep "^[a-z]" | grep -v ";"| sed -e "s/{/;/g" > $@
#
#h : $(SRCS)
#	make $(HEADERS)
#
obj/movement.o : movement.c movement.h turn.c turn.h common_variables.h
obj/turn.o : turn.c turn.h common_variables.h
obj/bluetooth.o : common_variables.h bluetooth.h bluetooth.c

mainTest : $(OBJECTS) mainTest.o
	$(CC) $^ $(INCLUDE) $(CFLAGS) -lm -lev3dev-c -lpthread -o $@

main : $(OBJECTS) main.o
	$(CC) $^ $(INCLUDE) $(CFLAGS) -lm -lev3dev-c -lpthread -o $@

clean: 
	rm obj/*.o
	
