CC = gcc
XX = g++
CFLAGS =   -Wall -g  -std=c++11 
TARGET = test

LIBDIR =  -lpthread

%.o:%.cpp
	$(XX) $(CFLAGS)  -c  $<  -o $@

SOURCES = $(wildcard *.cpp) 
OBJS = $(patsubst %.cpp,%.o,$(SOURCES))

$(TARGET) : $(OBJS)
		$(XX) $(OBJS) -o  $(TARGET)

clean:
	rm -rf *.o  test
