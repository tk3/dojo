.DEFAULT_GOAL := build

get-package:
	sudo apt install pkg-config libffi-dev libssl1.0.0

get-mruby:
	git clone https://github.com/mruby/mruby.git

get-gem:
	git clone git@github.com:qtkmz/mruby-ffi.git

build:
	cd mruby;  \
	rake

test:
	cd mruby;  \
	rake test

clean:
	cd mruby;  \
	rake clean

diff:
	cd mruby-ffi;  \
	git diff

irb: build
	./mruby/bin/mirb

sample: build
	./mruby/bin/mruby ./foo.rb

valgrind: build
	valgrind --leak-check=full ./mruby/bin/mruby ./foo.rb

