CC       = gcc

SOURCES  = sample.c

OBJS     = $(SOURCES:.c=.o)

INCLUDES = $(shell pkg-config --cflags libffi)

CFLAGS   = -Wall

LDFLAGS  = $(shell pkg-config --libs libffi) -lcrypto

LIBS     =

TARGET   = main


$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS) $(NGINX_OBJS) $(LDFLAGS) $(LIBS)

.c.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $<

debug:
	make -f Makefile CFLAGS="-g $(CFLAGS)" LDFLAGS="-g $(LDFLAGS)"

clean:
	rm -f $(TARGET) $(OBJS)

