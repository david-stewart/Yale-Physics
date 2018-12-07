/* #include "MyLoop.h" */
#include "EventTree.h"
#include "InputSapling.h"
#include <assert.h>

#include <vector>
#include <array>
#include <map>

/* #include <iostream> */
/* #include <iomanip> */
/* #include <unistd.h> */

using namespace std;

int main(int argc, const char** argv) {
    InputSapling input{argc, argv};
    input.ExploratoryLoop();
}

