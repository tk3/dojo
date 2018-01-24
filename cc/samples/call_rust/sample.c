#include <stdio.h>

void sayGreeting(void);
int rust_add(int x, int y);

int main(int argc, char **argv)
{
    sayGreeting();

    printf("result: %d\n", rust_add(10, 15));

    return 0;
}

