#include "Foo.h"
#include <stdio.h>

JNIEXPORT jint JNICALL Java_Foo_say(JNIEnv *env, jobject obj)
{
    printf("hello!\n");
    return 0;
}

