CC       = gcc
SOURCES  = sample.c
OBJS     = $(SOURCES:.c=.o)
INCLUDES =
CFLAGS   = -Wall
LDFLAGS  = -lodbc
LIBS     =
TARGET   = main

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

debug:
	make -f Makefile CFLAGS="-g $(CFLAGS)" LDFLAGS="-g $(LDFLAGS)"

clean:
	rm -f $(TARGET) $(OBJS)
