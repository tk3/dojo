.DEFAULT_GOAL := build

pkg-mruby:
	sudo apt install bison

pkg-ffi:
	sudo apt install pkg-config libffi-dev

get-mruby:
	git clone https://github.com/mruby/mruby.git

get-gem:
	git clone git@github.com:qtkmz/mruby-ffi.git

config-init:
	cp build_config.rb ./mruby

build: config-init
	cp build_config.rb ./mruby; \
	cd mruby;  \
	rake

test: config-init
	cp build_config.rb ./mruby; \
	cd mruby;  \
	rake test

clean:
	cd mruby;  \
	rake clean

diff:
	cd mruby-ffi;  \
	git diff

irb:
	./mruby/bin/mirb

run:
	./mruby/bin/mruby ./foo.rb

valgrind:
	valgrind --leak-check=full ./mruby/bin/mruby ./foo.rb

