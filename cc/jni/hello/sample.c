#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jni.h"

int main(int argc, char **argv)
{
    JNIEnv         *jenv;
    JavaVM         *jvm;
    JavaVMInitArgs jvm_args;
    JavaVMOption   jvm_options[1];
    jclass         klass;
    jmethodID      mid;
    int            ret;

    jvm_options[0].optionString = "-Djava.class.path=./java";

    jvm_args.version            = JNI_VERSION_1_6;
    jvm_args.options            = jvm_options;
    jvm_args.nOptions           = 1;
    jvm_args.ignoreUnrecognized = 1;

    ret = JNI_CreateJavaVM(&jvm, (void**)&jenv, &jvm_args);
    if (ret < 0) {
        fprintf(stderr, "cannot create JVM\n");
        exit(1);
    }

    klass = (*jenv)->FindClass(jenv, "HelloWorld");
    if (klass == 0) {
        fprintf(stderr, "cannot find class\n");
        exit(1);
    }

    // public static void main (String[] args)
    mid = (*jenv)->GetStaticMethodID(jenv, klass, "main", "([Ljava/lang/String;)V");
    if (mid == 0) {
        fprintf(stderr, "cannot get method id\n");
        exit(1);
    }

    (*jenv)->CallStaticVoidMethod(jenv, klass, mid, NULL);

    (*jvm)->DestroyJavaVM(jvm);

    exit(0);
}

