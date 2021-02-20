DIR=./source
BIN=libstatic_test.a
SHARE=--share
CFLAGE=-I./include
LFLAG=
CC=gcc
AR=ar -cr
CO=$(AR)

SRC=$(wildcard $(DIR)/*.c)
OBJ=$(patsubst %.c,%.o,$(SRC))

all:$(BIN)
$(BIN):$(OBJ)
	@mkdir -p libstatic/
	$(CO) ./libstatic/$@ $^
$(DIR)/%.o:$(DIR)/%.c
	$(CC) $(CFLAGE) -o $@ -c $<
.PHONY:clean
clean:
	rm -rf ./libstatic
	rm $(OBJ)