#include "../include/bin_convert.h"

#include <iostream>

void runTest(
    const char* name,
    unsigned int input,
    const char* expected
) {
    std::cout << name << '\n';
    std::cout << "Expected: " << expected << '\n';
    std::cout << "Actual  : ";
    convert(input);
    std::cout << '\n';
}

int main() {
    runTest(
        "Test 1: So 0",
        0u,
        "00000000000000000000000000000000"
    );

    runTest(
        "Test 2: So 1",
        1u,
        "00000000000000000000000000000001"
    );

    runTest(
        "Test 3: So 10",
        10u,
        "00000000000000000000000000001010"
    );

    runTest(
        "Test 4: Bit cao nhat",
        0x80000000u,
        "10000000000000000000000000000000"
    );

    runTest(
        "Test 5: Tat ca bit bang 1",
        0xFFFFFFFFu,
        "11111111111111111111111111111111"
    );

    return 0;
}
