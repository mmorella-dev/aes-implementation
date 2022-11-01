#include <cassert>
#include <iostream>

#include "aes/aes.h"

using namespace aes;

bool bytes16_eq(const Bytes16 &first, const Bytes16 &second)
{
    for (int i = 0; i < 16; i++)
    {
        if (first[i] != second[i])
            return false;
    }
    return true;
}
void bytes16_print(const Bytes16 &first)
{
    for (int i = 0; i < 16; i++)
        std::cout << "0x" << std::hex << (int)first[i] << " ";
    std::cout << '\n';
}

bool test_sub_bytes()
{
    // example from page 176;
    const Bytes16 init = {
        0xEA, 0x04, 0x65, 0x85, //
        0x83, 0x45, 0x5D, 0x96, //
        0x5C, 0x33, 0x98, 0xB0, //
        0xF0, 0x2D, 0xAD, 0xC5};
    const Bytes16 expected = {
        0x87, 0xF2, 0x4D, 0x97, //
        0xEC, 0x6E, 0x4C, 0x90, //
        0x4A, 0xC3, 0x46, 0xE7, //
        0x8C, 0xD8, 0x95, 0xA6};
    // Call sub_bytes
    Bytes16 result = sub_bytes(init, false);
    assert(bytes16_eq(expected, result));
    // Call sub_bytes inverse
    Bytes16 result2 = sub_bytes(expected, true);
    assert(bytes16_eq(result2, init));
    return true;
}

bool test_shift_rows()
{
    // example from page 179
    const Bytes16 init = {
        0x87, 0xF2, 0x4D, 0x97, //
        0xEC, 0x6E, 0x4C, 0x90, //
        0x4A, 0xC3, 0x46, 0xE7, //
        0x8C, 0xD8, 0x95, 0xA6  //
    };
    const Bytes16 result = shift_rows(init, true);
    const Bytes16 expected = {
        0x87, 0xF2, 0x4D, 0x97, //
        0x6E, 0x4C, 0x90, 0xEC, //
        0x46, 0xE7, 0x4A, 0xC3, //
        0xA6, 0x8C, 0xD8, 0x95  //
    };
    assert(bytes16_eq(result, expected));
    return true;
}

bool test_mix_columns()
{
    // example from p. 181
    const Bytes16 init = {
        0x87, 0xF2, 0x4D, 0x97, //
        0x6E, 0x4C, 0x90, 0xEC, //
        0x46, 0xE7, 0x4A, 0xC3, //
        0xA6, 0x8C, 0xD8, 0x95  //
    };
    Bytes16 result = mix_columns(init, false);
    const Bytes16 expected = {
        0x47, 0x40, 0xA3, 0x4C, //
        0x37, 0xD4, 0x70, 0x9F, //
        0x94, 0xE4, 0x3A, 0x42, //
        0xED, 0xA5, 0xA6, 0xBC  //
    };
    assert(bytes16_eq(result, expected));
    Bytes16 result2 = mix_columns(expected, true);
    assert(bytes16_eq(result2, init));
    return true;
}

int main()
{
    assert(test_sub_bytes());
    assert(test_shift_rows());
    assert(test_mix_columns());
    std::cout << "All passed!\n";
}