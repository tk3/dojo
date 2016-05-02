#include "wren.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	WrenConfiguration config; 
	WrenVM* vm;

	wrenInitConfiguration(&config);

	vm = wrenNewVM(&config);

	WrenInterpretResult result = wrenInterpret(vm, "");
	if (result == WREN_RESULT_SUCCESS) {
		printf("success\n");
	} else {
		printf("return code = %d\n", result);
	}

	wrenFreeVM(vm);

	return 0;
}

