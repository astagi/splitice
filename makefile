CC=gcc
CFLAGS=-D_FILE_OFFSET_BITS=64 -c
LDFLAGS=-pthread
SOURCES=src/md5.c src/utils.c src/splitice.c src/main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=splitice

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS)
	mkdir build
	mv splitice build

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm src/*.o
	-rm -r build
