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

all: param compile run

param:
	cd ../../py && python export.py

compile: $(CSOURCES)
	$(CC) $^ $(INCLUDS) $(CFLAGS) -o $(TARGET)

run:
	./conv2d_test.exe

clean:
	$(DELETE) *.txt *.exe