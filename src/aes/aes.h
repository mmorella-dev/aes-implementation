/// AES.H
///
/// @brief Provides core AES encryption functions
/// @author Mae B. Morella <https://github.com/morellam-dev>

#ifndef AES_AES_H_
#define AES_AES_H_

#include <span>  // for std::span
#include <array> // for std::array
#include <cstdint>

namespace aes {

using byte = uint8_t;

/// @brief Performs the AES SubBytes operation
/// @param input A span of 16 contiuguous bytes
/// @param inverse If true, use the inverse S-Box
auto sub_bytes(std::span<byte, 16> input, bool inverse = false) -> void;

/// @brief Performs the AES ShiftRows operation
/// @param input A span of 16 contiuguous bytes
/// @param inverse If true, perform InvShiftRows
auto shift_rows(std::span<byte, 16> input, bool inverse = false) -> void;

/// @brief Performs the AES MixColumns operation
/// @param input A span of 16 contiuguous bytes
/// @param inverse If true, perform InvMixColumns
auto mix_columns(std::span<byte, 16> input, bool inverse) -> void;

/// @brief Performs the AES KeyExpansion operation
/// @param key An std::array of 16 bytes
auto key_expansion(const std::span<byte, 16> key) -> std::array<std::array<byte, 16>, 11>;
}  // namespace aes

#endif