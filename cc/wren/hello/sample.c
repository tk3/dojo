#include "wren.h"
#include <stdio.h>

static const char* text =
"System.print(\"hello, world\")"
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
	config.bindForeignClassFn = NULL;

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
	printf("%s", text);
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
	return NULL;
}

WrenForeignMethodFn sample_foreign_method(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature)
{
	return NULL;
}

WrenForeignClassMethods sample_foreign_class(WrenVM* vm, const char* module, const char* className)
{
	WrenForeignClassMethods methods;

	methods.allocate = NULL;
	methods.finalize = NULL;

	return methods;
}

