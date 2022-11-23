#include <algorithm>

#include "aes.h"
#include "rijndael.h"

namespace aes {
Bytes16 sub_bytes(const Bytes16& input, bool inverse) {
  Bytes16 result;
  const auto& sbox = (!inverse) ? rjindael::SBOX : rjindael::SBOX_INVERSE;
  std::transform(input.begin(), input.end(), result.begin(),
                 [=](uint8_t b) { return sbox[b]; });
  return result;
}
}  // namespace aes