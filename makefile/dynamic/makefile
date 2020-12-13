DIR=./source
BIN=libdynamic.so
SHARE=-fPIC -shared 
CFLAGE=-I./include
LFLAG=
CC=gcc
AR=ar -cr
CO=$(AR)

SRC=$(wildcard $(DIR)/*.c)
OBJ=$(patsubst %.c,%.o,$(SRC))

all:$(BIN)
$(BIN):$(OBJ)
	@mkdir -p libdynamic/
	$(CO) ./libdynamic/$@ $^
$(DIR)/%.o:$(DIR)/%.c
	$(CC) $(CFLAGE) $(SHARE) -o $@ -c $<
.PHONY:clean
clean:
	rm -rf ./libdynamic
	rm $(OBJ)