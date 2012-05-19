CC       = gcc
SOURCES  = sample.c
OBJS     = $(SOURCES:.c=.o)
INCLUDES =
CFLAGS   = -Wall
LDFLAGS  =
LIBS     =
TARGET   = main

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

debug:
	make -f Makefile CFLAGS="-g $(CFLAGS)" LDFLAGS="-g $(LDFLAGS)"

clean:
	rm -f $(TARGET) $(OBJS)
