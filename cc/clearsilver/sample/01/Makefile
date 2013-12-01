CLEARSILVER = $(HOME)/apps/clearsilver-0.10.5

CC       = gcc
SOURCES  = sample.c
OBJS     = $(SOURCES:.c=.o)
INCLUDES = -I$(CLEARSILVER)/include/ClearSilver
CFLAGS   = -Wall
LDFLAGS  = -L$(CLEARSILVER)/lib
LIBS     = $(CLEARSILVER)/lib/libneo_cgi.a \
           $(CLEARSILVER)/lib/libneo_utl.a \
           $(CLEARSILVER)/lib/libneo_cs.a
TARGET   = main

$(TARGET): $(OBJS)
#	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

debug:
	make -f Makefile CFLAGS="-g $(CFLAGS)" LDFLAGS="-g $(LDFLAGS)"

clean:
	rm -f $(TARGET) $(OBJS)
