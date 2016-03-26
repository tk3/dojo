#include "wren.h"
#include <stdio.h>
#include <string.h>

static const char* text =
"import \"random\" for Random\n"
"import \"foo\" for Foo\n"
"\n"
"System.print(\"abcd\".byteCount_)"
"\n"
"var random = Random.new(12345)\n"
"var list = (1..5).toList\n"
"random.shuffle(list)\n"
"System.print(list) //> [3, 2, 4, 1, 5]\n"
"\n"
"Foo.say()\n"
"Foo.hey()\n"
;

static const char* foo_class_text = 
"class Foo {\n"
"  static say() {\n"
"    System.print(\"foo!\")\n"
"  }\n"
"  foreign static hey()\n"
"}\n"
;

static void write_func(WrenVM* vm, const char* text);
static void report_func(WrenErrorType type, const char* module, int line, const char* message);

char* sample_load_module(WrenVM* vm, const char* name);
WrenForeignMethodFn sample_foreign_method(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature);
WrenForeignClassMethods sample_foreign_class(WrenVM* vm, const char* module, const char* className);

int main(int argc, char** argv)
{
	WrenConfiguration config; 
	WrenVM* vm;

	wrenInitConfiguration(&config);

	config.writeFn = write_func;
	config.errorFn = report_func;
	config.loadModuleFn = sample_load_module;
	config.bindForeignMethodFn = sample_foreign_method;
	config.bindForeignClassFn = sample_foreign_class;

	vm = wrenNewVM(&config);

	WrenInterpretResult result = wrenInterpret(vm, text);
	if (result == WREN_RESULT_SUCCESS) {
		printf("success\n");
	} else {
		printf("return code = %d\n", result);
	}

	wrenFreeVM(vm);

	return 0;
}

static void write_func(WrenVM* vm, const char* text)
{
	puts(">>>>");
	printf("%s\n", text);
	fflush(stdout);
}

static void report_func(WrenErrorType type, const char* module, int line, const char* message)
{
	switch (type) {
	case WREN_ERROR_COMPILE:
		fprintf(stderr, "[%s line %d] %s\n", module, line, message);
		break;
    case WREN_ERROR_RUNTIME:
		fprintf(stderr, "%s\n", message);
		break;
	case WREN_ERROR_STACK_TRACE:
		fprintf(stderr, "[%s line %d] in %s\n", module, line, message);
		break;
	default:
		break;
	}
}

char* sample_load_module(WrenVM* vm, const char* name)
{
	printf("load) name=[%s]\n", name);

	if (strcmp(name, "foo") == 0) {
		return (char*)foo_class_text;
	}

	return NULL;
}

WrenForeignMethodFn sample_foreign_method(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature)
{
	WrenForeignMethodFn method = NULL;

	printf("foreign method) module=[%s], className=[%s], signature=[%s]\n", module, className, signature);

/*--
	if (vm->config.bindForeignMethodFn != NULL) {
		method = vm->config.bindForeignMethodFn(vm, module, className, isStatic, signature);
	}
--*/

	return method;
}

WrenForeignClassMethods sample_foreign_class(WrenVM* vm, const char* module, const char* className)
{
	WrenForeignClassMethods methods;

	printf("foreign class) module=[%s], className=[%s]\n", module, className);

	methods.allocate = NULL;
	methods.finalize = NULL;

	return methods;
}
