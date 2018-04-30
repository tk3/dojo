#include <stdio.h>
#include "ffi.h"

struct Foo {
  int x;
  int y;
};

int foo_add(struct Foo foo);

int main(int argc, char **argv)
{
    struct Foo f = {};
	int r;

	f.x = 11;
	f.y = 17;

	r = foo_add(f);

	printf("result = %d\n", r);

    return 0;
}

int foo_add(struct Foo f)
{
	return f.x + f.y;
}
