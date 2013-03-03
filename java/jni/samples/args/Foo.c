#include "Foo.h"
#include <stdio.h>

JNIEXPORT void JNICALL Java_Foo_sendInt(JNIEnv *jenv, jobject jobj, jint i)
{
    int val;

    val = i;

    printf("recv: [%d]\n", val);

    return;
}

JNIEXPORT void JNICALL Java_Foo_sendString(JNIEnv *jenv, jobject jobj, jstring s)
{
    const char *val = (*jenv)->GetStringUTFChars(jenv, s, 0);

    printf("recv: [%s]\n", val);

    return;
}

JNIEXPORT void JNICALL Java_Foo_sendStrings(JNIEnv *jenv, jobject jobj, jobjectArray array)
{
    int len;
    int i;
    jstring s;
    const char *val;

    len = (*jenv)->GetArrayLength(jenv, array);

    printf("length: [%d]\n", len);

    for (i = 0; i < len; i++) {
        s = (*jenv)->GetObjectArrayElement(jenv, array, i);

        val = (*jenv)->GetStringUTFChars(jenv, s, 0);

        printf("  %d) [%s]\n", i, val);

        (*jenv)->ReleaseStringUTFChars(jenv, s, val);
    }

    return;
}
