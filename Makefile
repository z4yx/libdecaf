TARGET             := mipsel-unknown-linux-gnu-

AS                 := $(TARGET)as -EL -g -mips32
CC                 := $(TARGET)gcc
LD                 := $(TARGET)gcc
AR                 := $(TARGET)ar
DECAF              := java -jar decaf.jar 
RM                 := rm -f

LIBDECAFDIR        := $(shell pwd)


INCLUDE_DIR        += 
CFLAGS             += -fno-builtin -fno-delayed-branch -g  -EL -G0 -O2 -Wa,-O2 $(INCLUDE_DIR)


LIBS               += -ldecaf 
LIB_DIR            += -L$(LIBDECAFDIR)
LDFLAGS            += $(LIB_DIR) -static



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