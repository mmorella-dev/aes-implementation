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
/// @param state A span of 16 contiguous bytes (modified in place)
/// @param inverse If true, use the inverse S-Box
auto SubBytes(std::span<byte, 16> state, bool inverse = false) -> void;

/// @brief Performs the AES ShiftRows operation
/// @param state A span of 16 contiguous bytes (modified in place)
/// @param inverse If true, perform InvShiftRows
auto ShiftRows(std::span<byte, 16> state, bool inverse = false) -> void;

/// @brief Performs the AES MixColumns operation
/// @param state A span of 16 contiguous bytes (modified in place)
/// @param inverse If true, perform InvMixColumns
auto MixColumns(std::span<byte, 16> state, bool inverse = false) -> void;

/// @brief Performs the AES KeyExpansion operation
/// @param state An std::array of 16 bytes
/// @return The initial state and 10 round keys
auto KeyExpansion(const std::span<byte, 16> state)
    -> std::array<std::array<byte, 16>, 11>;

/// @brief Performs the AES AddRoundKey operation
/// @param state The current state vector
/// @param round_key The round state to add.
auto AddRoundKey(std::span<byte, 16> state, const std::span<byte, 16> round_key) -> void;

/// @brief Encrypts a 128-bit block using AES
/// @param state The state vector to encrypt
/// @param initial_key The state to use
auto Encrypt(std::span<byte, 16> state, const std::span<byte, 16> initial_key) -> void;
/// 
/// @brief Decrypts a 128-bit block using AES
/// @param state The state vector to decrypt
/// @param initial_key The state to use
auto Decrypt(std::span<byte, 16> state, const std::span<byte, 16> initial_key) -> void;

}  // namespace aes

#endif