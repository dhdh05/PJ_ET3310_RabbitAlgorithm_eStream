#include "rabbit.h"
#include "utils.h"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

// So test da chay va so test that bai, dung chung cho moi ham test.
static int totalTests = 0;
static int failedTests = 0;

// In PASS/FAIL cho mot truong hop kiem tra.
static void check(const std::string& name, bool ok) {
    totalTests++;
    if (!ok) failedTests++;
    std::cout << "  " << name << ": " << (ok ? "[PASS]" : "[FAIL]") << "\n";
}

// Khoa va IV co dinh dung chung cho cac test.
static const uint8_t KEY[16] = {
    0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
    0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF
};
static const uint8_t IV[8] = {0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};

// Test 1: ma hoa chuoi roi giai ma bang doi tuong moi phai ra lai chuoi goc.
static void testString() {
    const std::string text = "Xin chao ET3310!";
    const std::vector<uint8_t> plain(text.begin(), text.end());
    std::vector<uint8_t> cipher(plain.size());
    std::vector<uint8_t> decrypted(plain.size());

    RabbitCipher enc;
    enc.setupKey(KEY);
    enc.setupIV(IV);
    enc.process(plain.data(), cipher.data(), plain.size());

    RabbitCipher dec;
    dec.setupKey(KEY);
    dec.setupIV(IV);
    dec.process(cipher.data(), decrypted.data(), cipher.size());

    check("chuoi: giai ma ra lai ban goc", decrypted == plain);
    check("chuoi: ban ma khac ban ro", cipher != plain);
}

// Test 2: 1MB du lieu ngau nhien ma hoa roi giai ma phai ra dung ban goc.
static void testLargeData() {
    const size_t n = 1024 * 1024;
    std::vector<uint8_t> plain(n);
    std::srand(12345);
    for (size_t i = 0; i < n; i++) {
        plain[i] = static_cast<uint8_t>(std::rand() & 0xFF);
    }

    std::vector<uint8_t> cipher(n);
    std::vector<uint8_t> decrypted(n);

    RabbitCipher enc;
    enc.setupKey(KEY);
    enc.setupIV(IV);
    enc.process(plain.data(), cipher.data(), n);

    RabbitCipher dec;
    dec.setupKey(KEY);
    dec.setupIV(IV);
    dec.process(cipher.data(), decrypted.data(), n);

    check("1MB: giai ma ra dung ban goc", decrypted == plain);
    check("1MB: ban ma khac ban ro", cipher != plain);
}

// Test 3: du lieu rong (length = 0) khong duoc gay loi va khong thay doi gi.
static void testEmptyData() {
    std::vector<uint8_t> buf;
    RabbitCipher cipher;
    cipher.setupKey(KEY);
    cipher.setupIV(IV);
    cipher.process(buf.data(), buf.data(), 0);
    check("rong: xu ly length=0 khong loi, khong doi gi", buf.empty());
}

// Test 4: ma hoa tai cho (input va output cung mang) phai cho ket qua giong
// ma hoa sang mang khac, voi cung khoa/IV.
static void testInPlace() {
    const std::string text = "Du lieu dung de kiem tra ma hoa tai cho, dai hon mot khoi 16 byte.";
    const std::vector<uint8_t> plain(text.begin(), text.end());

    std::vector<uint8_t> cipherSeparate(plain.size());
    RabbitCipher encA;
    encA.setupKey(KEY);
    encA.setupIV(IV);
    encA.process(plain.data(), cipherSeparate.data(), plain.size());

    std::vector<uint8_t> buf = plain;
    RabbitCipher encB;
    encB.setupKey(KEY);
    encB.setupIV(IV);
    encB.process(buf.data(), buf.data(), buf.size());

    check("tai cho: giong ma hoa sang mang khac", buf == cipherSeparate);
}


int main() {
    std::cout << "=== TEST MA HOA / GIAI MA ===\n";

    testString();
    testLargeData();
    testEmptyData();
    testInPlace();

    std::cout << "\nTong: " << totalTests - failedTests << "/" << totalTests << " PASS\n";
    return failedTests == 0 ? 0 : 1;
}
