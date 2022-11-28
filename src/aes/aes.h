#ifndef AES_AES_H_
#define AES_AES_H_

#include <array>  // for std::array
#include <cstdint>

namespace aes {

using std::array;

template <int I>
using bytes_t = array<uint8_t, I>;

/// @brief Performs the AES SubBytes operation
/// @param input An array of 16 bytes
/// @param inverse If true, use the inverse S-Box
auto sub_bytes(bytes_t<16> &input, bool inverse = false) -> void;

/// @brief Performs the AES ShiftRows operation
/// @param input An array of 16 bytes
/// @param inverse If true, perform InvShiftRows
auto shift_rows(bytes_t<16> &input, bool inverse = false) -> void;

/// @brief Performs the AES MixColumns operation
/// @param input An array of 16 bytes
/// @param inverse If true, perform InvMixColumns
auto mix_columns(bytes_t<16> &input, bool inverse) -> void;

/// @brief Performs the AES KeyExpansion operation
/// @param key An array of 16 bytes
auto key_expansion(const bytes_t<16> &key) -> array<bytes_t<16>, 11>;
}  // namespace aes

#endif