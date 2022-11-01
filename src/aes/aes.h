#include <array>
#include <span>

namespace aes {

using Bytes4 = std::array<uint8_t, 4>;         // an array of 4 bytes
using Bytes16 = std::array<uint8_t, 16>;       // an array of 16 bytes
using Bytes176 = std::array<Bytes16, 11>; // a 2d array of 11*16 (176)

/// If InputArray is not NULL, process all the values in input and store result
/// If inverse is true it will use the Inverse S-Box to perform the substitution instead

/// Process the

/// @brief 
/// @param input An array of 16 bytes
/// @param inverse If true, use the inverse S-Box instead
/// @return 
Bytes16 sub_bytes(const Bytes16 &input, bool inverse);

/// @brief Shifts row2 by 1, row3 by 2, and row4 by 4
/// @param input A 4x4 matrix of bytes 
/// @param left_right If true, shift left, else shift right
/// @return The matrix, shifted
Bytes16 shift_rows(const Bytes16 &input, bool left_right);

// Accepts an input array of 16 bytes and produces an output according to the above M-Box function from Sec 6.3.
// If inverse is TRUE it will calculate based on the Inverse Mix Columns Matrix
// otherwise it will calculate the Mix Columns function.
Bytes16 mix_columns(const Bytes16 &input, bool inverse);

// Accept an input array of bytes key (k0,k1,k2,k3,k4,k5,k6,k7,k8,k9,k10,k11,k12,k13,k14,k15) and
// produce W the 176 byte array to be used as keys for initial round and 10 rounds of AES.
Bytes176 key_expansion(const Bytes16 &input);

}