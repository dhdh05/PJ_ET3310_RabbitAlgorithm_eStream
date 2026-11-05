
#include <iostream>
#include <cassert>

#include "../include/counter.h"
#include "../include/init.h"

using namespace std;

// Test 1: Cộng counter thông thường, không tràn, C[i] = 0
void test_normal() {
    init();
    carry = 0;

    counter_system();

    assert(C[0] == 0x4D34D34D);
    assert(C[1] == 0xD34D34D3);
    assert(C[2] == 0x34D34D34);
    assert(C[3] == 0x4D34D34D);
    assert(C[4] == 0xD34D34D3);
    assert(C[5] == 0x34D34D34);
    assert(C[6] == 0x4D34D34D);
    assert(C[7] == 0xD34D34D3);

    assert(carry == 0);

    cout << "PASS test_normal\n";
}


// Test 2: Tràn tại duy nhất C[0]
void test_single_overflow() {
    init();
    carry = 0;
    C[0] = 0xFFFFFFFF;

    counter_system();

    // C[0] tràn, giữ lại 32 bit thấp, carry = 1 cộng vào C[1]
    assert(C[0] == 0x4D34D34C);
    assert(C[1] == 0xD34D34D4);

    // Các counter còn lại giữ nguyên
    assert(C[2] == 0x34D34D34);
    assert(carry == 0);

    cout << "PASS test_single_overflow\n";
}


// Test 3: Carry lan truyền liên tiếp qua cả 8 counter
void test_carry_propagation() {
    init();
    carry = 0;

    // Thiết lập C[i] để tạo ra carry
    for (int i = 0; i < 8; i++) {
        C[i] = (uint32_t)(((uint64_t)1 << 32) - A[i]);
    }

    counter_system();
    assert(C[0] == 0);

    for (int i = 1; i < 8; i++) {
        assert(C[i] == 1);
    }

    assert(carry == 1);

    cout << "PASS test_carry_propagation\n";
}


// Test 4: Carry đầu vào đã bằng 1
void test_initial_carry() {
    init();
    carry = 1;

    counter_system();
    // Mỗi C[i] đều cộng thêm carry = 1
    assert(C[0] == 0x4D34D34E);
    assert(C[1] == 0xD34D34D3);
    assert(C[2] == 0x34D34D34);

    assert(carry == 0);

    cout << "PASS test_initial_carry\n";
}

// Test 5: Carry khởi tạo và C[0] gây tràn
void test_initial_carry_overflow () {
    init();
    carry = 1;
    C[0] = 0xFFFFFFFF - A[0];
    counter_system();

    assert(C[0] == 0);
    assert(C[1] == 0xD34D34D4);  //C[1] = A[1] + 1 

    assert(carry == 0);
    cout << "PASS test_initial_carry_overflow";

}


int main() {
    test_normal();
    test_single_overflow();
    test_carry_propagation();
    test_initial_carry();
    test_initial_carry_overflow();

    cout << "\nAll counter tests passed!\n";

    return 0;
}
