/// AES.H
///
/// @brief Provides core AES encryption functions
/// @author Mae B. Morella <https://github.com/morellam-dev>

#ifndef AES_AES_H_
#define AES_AES_H_

#include <array>  // for std::array
#include <cstdint>
#include <span>  // for std::span

namespace aes {

using byte = uint8_t;

/// @brief Performs the AES SubBytes operation
/// @param key A span of 16 contiuguous bytes
/// @param inverse If true, use the inverse S-Box
auto SubBytes(std::span<byte, 16> key, bool inverse = false) -> void;

/// @brief Performs the AES ShiftRows operation
/// @param key A span of 16 contiuguous bytes
/// @param inverse If true, perform InvShiftRows
auto ShiftRows(std::span<byte, 16> key, bool inverse = false) -> void;

/// @brief Performs the AES MixColumns operation
/// @param key A span of 16 contiuguous bytes
/// @param inverse If true, perform InvMixColumns
auto MixColumns(std::span<byte, 16> key, bool inverse) -> void;

/// @brief Performs the AES KeyExpansion operation
/// @param key An std::array of 16 bytes
/// @return The initial key and 10 round keys
auto KeyExpansion(const std::span<byte, 16> key)
    -> std::array<std::array<byte, 16>, 11>;

/// @brief Performs the AES AddRoundKey operation
/// @param state The current state vector
/// @param round_key The round key to add.
auto AddRoundKey(std::span<byte, 16> state, const std::span<byte, 16> round_key) -> void;

}  // namespace aes

#endif