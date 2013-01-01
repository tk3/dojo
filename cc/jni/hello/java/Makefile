.SUFFIXES: .java .class
JAVAC    = javac
SOURCES  = HelloWorld.java
CLASSES  = $(SOURCES:.java=.class)
TARGET   = main

default: $(CLASSES)

.java.class:
	$(JAVAC) $<

clean:
	rm $(CLASSES)

