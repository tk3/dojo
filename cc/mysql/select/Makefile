CC       = gcc
SOURCES  = sample.c
OBJS     = $(SOURCES:.c=.o)
INCLUDES = `mysql_config --include`
CFLAGS   = -Wall
LDFLAGS  = `mysql_config --libs_r`
LIBS     = 
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

run:
	@LD_LIBRARY_PATH=/usr/local/mysql/lib ./main

