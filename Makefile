# BH test code

APP_NAME    = test

APP_SRC     = test.cpp
LIB_NAME    = $(APP_NAME).a

DEFAULT: obj app

CC          := g++

SRC         =$(wildcard *.cpp)
SRC_H       =$(wildcard *.h)

LIB_SRC     = $(filter-out $(APP_SRC), $(SRC))
CFLAGS      = -Wall -std=c++11
LDFLAGS     =
ARFLAGS 	= rcs
LIBS        = -lcurl


obj:
	$(CC) -c $(CFLAGS) $(SRC)

app: obj
	$(CC) -o $(APP_NAME).exe $(subst .cpp,.o,$(SRC)) $(LDFLAGS) $(LIBS)
	rm -f *.o
	echo DONE

clean: 
	rm -f *.o
	rm -f *.a
	rm -f *.exe
