#include <array>
#include <span>

using Byte = uint8_t;                       // unsigned 8 bit integer
using Bytes4 = std::array<Byte, 4>;         // an array of 4 bytes
using Bytes16 = std::array<Byte, 16>;       // an array of 16 bytes
using Bytes176 = std::array<Bytes16, 11>; // a 2d array of 11*16 (176)

/// If InputArray is not NULL, process all the values in input and store result
/// If inverse is true it will use the Inverse S-Box to perform the substitution instead
Bytes16 sub_bytes(const Bytes16 &input, bool inverse);

/// Accepts an input array of 16 bytes and produces an output according to the above shift from Sec 6.3.
/// If left_right is true it will do the left byte shift operation above, if false it will shift/rotate in the other direction (right).
Bytes16 shift_rows(const Bytes16 &input, bool left_right);

// Accepts an input array of 16 bytes and produces an output according to the above M-Box function from Sec 6.3.
// If inverse is TRUE it will calculate based on the Inverse Mix Columns Matrix
// otherwise it will calculate the Mix Columns function.
Bytes16 mix_columns(const Bytes16 &input, bool inverse);

// Accept an input array of bytes key (k0,k1,k2,k3,k4,k5,k6,k7,k8,k9,k10,k11,k12,k13,k14,k15) and
// produce W the 176 byte array to be used as keys for initial round and 10 rounds of AES.
Bytes176 key_expansion(const Bytes16 &input);