TARGET             := mips-sde-elf-

AS                 := $(TARGET)as -EL -g -mips32
CC                 := $(TARGET)gcc
LD                 := $(TARGET)ld
AR                 := $(TARGET)ar
DECAF              := java -jar decaf.jar 
RM                 := rm -f

LIBDECAFDIR        := $(shell pwd)
UCOREPREFIX        := /src/ucore-thumips


INCLUDE_DIR        += -I$(UCOREPREFIX)/user/libs -I$(UCOREPREFIX)/kern/include
CFLAGS             += -fno-builtin -nostdlib  -nostdinc -mno-float -fno-delayed-branch -g  -EL -G0 -O2 -Wa,-O2 $(INCLUDE_DIR)


LIBS               += -ldecaf -luser 
LIB_DIR            += -L$(UCOREPREFIX)/obj/user -L$(LIBDECAFDIR)
LDFLAGS            += -nostdlib -S -T $(UCOREPREFIX)/user/libs/user.ld $(LIB_DIR)



.PHONY: clean all libdecaf clean_test clean_libdecaf install

all: test

libdecaf.a: decafIo.o decafCall.o
	$(AR) rcs $@ $^

decafIo.o: decafIo.c
	$(CC) -c $(CFLAGS) -o $@ $^

decafCall.o: decafCall.s
	$(AS) -o $@ $^

test.o: test.s
	$(AS) -o $@ $^

test.s: test.decaf
	$(DECAF) $^ > $@
	
test: libdecaf.a test.o
	$(LD) $(LDFLAGS) -o $@ test.o $(LIBS)

install: all
	cp test $(UCOREPREFIX)/user/_archive/

clean: clean_libdecaf clean_test

clean_test: 
	-$(RM) test.s test.o test
clean_libdecaf:
	-$(RM) decafIo.o decafCall.o libdecaf.a