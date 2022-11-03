#include "aes.h"
#include "galois_lookup.h"

#include <algorithm>
#include <numeric>

namespace aes
{
    Bytes16 mix_columns(const Bytes16 &s, bool inverse)
    {
        // import lookup tables
        using namespace galois;
        Bytes16 output;
        for (int j = 0; j < 4; j++)
        {
            Bytes4 a = {s[j], s[4 + j], s[8 + j], s[12 + j]};
            if (!inverse)
            {
                uint8_t temp = a[0] ^ a[1] ^ a[2] ^ a[3];
                output[j] = a[0] ^ temp ^ x2[a[0] ^ a[1]];
                output[j + 4] = a[1] ^ temp ^ x2[a[1] ^ a[2]];
                output[j + 8] = a[2] ^ temp ^ x2[a[2] ^ a[3]];
                output[j + 12] = a[3] ^ temp ^ x2[a[3] ^ a[0]];
            }
            else
            {
                output[j] = xE[a[0]] ^ x9[a[3]] ^ xD[a[2]] ^ xB[a[1]];
                output[j + 4] = xE[a[1]] ^ x9[a[0]] ^ xD[a[3]] ^ xB[a[2]];
                output[j + 8] = xE[a[2]] ^ x9[a[1]] ^ xD[a[0]] ^ xB[a[3]];
                output[j + 12] = xE[a[3]] ^ x9[a[2]] ^ xD[a[1]] ^ xB[a[0]];
            }
        }
        return output;
    }
}