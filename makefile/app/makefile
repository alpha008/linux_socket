DIR=./source
STALIB=../staticlib
DYNAMICLIB=../dynamic
BIN=app
SHARE=
CFLAGE=-Wall -c
INCLUDE=-I./include \
	-I../staticlib/include\
	-I../dynamic/include
LFLAG=-L../staticlib/libstatic\
	   -L../dynamic/libdynamic
LIBS=-lstatic_test -ldynamic
CC=gcc
AR=ar -cr
CO=$(AR)

SRC=$(wildcard $(DIR)/*.c)
OBJ=$(patsubst %.c,%.o,$(SRC))

all:$(BIN)
$(BIN):$(OBJ)
	$(CC) $^ -o $@ $(LFLAG) $(LIBS)
$(DIR)/%.o:$(DIR)/%.c
	make -C $(STALIB)
	make -C $(DYNAMICLIB)
	$(CC) -c $(INCLUDE) $(CFLAGE) $<  -o  $@
.PHONY:clean
clean:
	rm $(OBJ)
	rm -rf ../dynamic/libdynamic
	rm -rf ../staticlib/libstatic