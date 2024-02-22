#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <sstream>

#include "../include/testmain.hpp"

int main() {
    bool testmode = true;
    if (testmode) {
        return testmain();
    }

    return 0;
}