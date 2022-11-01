CC = gcc
TARGET = conv2d_test.exe
PYTHON = python
# DELETE = rm
DELETE = del

CSOURCES = \
conv2d_test.c \
../../impl_c/conv2d.c\
../../impl_c/dataLoadSave.c 

INCLUDS = \
-I../../impl_c

CFLAGS =  \
-DDEBUG

all: compile generate run

compile: $(CSOURCES)
	$(CC) $^ $(INCLUDS) $(CFLAGS) -o $(TARGET)

generate:
	$(PYTHON) ../py/conv2d_test.py

run:
	./conv2d_test.exe

clean:
	$(DELETE) *.txt *.exe 