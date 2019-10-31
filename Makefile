CC=g++
CFLAGS=-c -std=c++11 -I/usr/local/include
LDFLAGS=-L/usr/local/lib
SOURCES=canmain.cpp Range.cpp Socket.cpp
LIBS=-pthread
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=CAN

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(LIBS) $^ -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)
	touch *
