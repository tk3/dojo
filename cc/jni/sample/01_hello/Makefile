CC       = gcc
SOURCES  = sample.c
OBJS     = $(SOURCES:.c=.o)
INCLUDES = -I$(JAVA_HOME)/include \
           -I$(JAVA_HOME)/include/darwin
CFLAGS   = -Wall
LDFLAGS  = -L$(JAVA_HOME)/jre/lib/server -ljvm
LIBS     =
TARGET   = main

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

debug:
	make -f Makefile CFLAGS+="-g" LDFLAGS+="-g"

clean:
	rm -f $(TARGET) $(OBJS)

run:
	@export LD_LIBRARY_PATH=$(JAVA_HOME)/jre/lib/server; \
	./$(TARGET)
