
#include <sstream>
#include <string>

#include "Controladora.h"


int main(){

    Controladora*C0 = new Controladora();
	C0->control0();
    delete C0;
    return 0;
}