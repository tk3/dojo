#include "wren.h"
#include <stdio.h>

static const char* text =
//"import \"foo\" for Foo\n"
"import \"random\" for Random\n"
"\n"
"System.print(\"Hello world\")\n"
"System.print(\"Hello world\")\n";

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
	//puts(">>>>");
	//puts(text);
}

static void report_func(WrenErrorType type, const char* module, int line, const char* message)
{
	return;
}

char* sample_load_module(WrenVM* vm, const char* name)
{
	printf("WrenLoadModuleFn\n");
	printf("name=[%s]\n", name);

	return NULL;
}

WrenForeignMethodFn sample_foreign_method(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature)
{
	printf("WrenForeignMethodFn s\n");
	printf("module=[%s], className=[%s], signature=[%s]\n", module, className, signature);

	return NULL;
}

WrenForeignClassMethods sample_foreign_class(WrenVM* vm, const char* module, const char* className)
{
	WrenForeignClassMethods methods;

	printf("WrenForeignClassMethods\n");
	printf("module=[%s], className=[%s]n", module, className);

	methods.allocate = NULL;
	methods.finalize = NULL;

	return methods;
}
