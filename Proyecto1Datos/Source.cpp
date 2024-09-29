#define _CRTDBG_MAP_ALLOC

#include<iostream>

#include <crtdbg.h>

#ifdef _DEBUG

#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define new DEBUG_NEW

#endif


#include <sstream>
#include <string>

#include "Controladora.h"


int main() {

    Controladora*C0 = new Controladora();
	C0->control0();
    delete C0;
    _CrtDumpMemoryLeaks();
    return 0;
}