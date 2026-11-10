
#include "../include/rotate_left.h"
#include "../include/bin_convert.h"
#include <iostream>
using namespace std;

void runTest(const char* name, uint32_t input,
             unsigned int k, uint32_t expected) {
    uint32_t actual = rotate_left(input, k);

    cout << name << endl;
    cout << "Input   : ";
    convert(input);

    cout << "Rotate  : " << k << " bit" << endl;

    cout << "Expected: ";
    convert(expected);
    cout << "Actual  : ";
    convert(actual);
    if (actual == expected)
        cout << "PASS" << endl;
    else
        cout << "FAIL" << endl;
    cout << endl;
}

int main() {
    runTest("Test 1: Xoay 0 bit", 0x12345678, 0, 0x12345678);
    runTest("Test 2: Xoay 8 bit", 0x12345678, 8, 0x34567812);
    runTest("Test 3: Xoay 16 bit", 0x12345678, 16, 0x56781234);
    runTest("Test 4: Xoay 32 bit", 0x12345678, 32, 0x12345678);
    runTest("Test 5: Xoay 40 bit", 0x12345678, 40, 0x34567812);

    return 0;
}
