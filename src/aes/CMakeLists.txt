# Aes library
add_library(aes STATIC
    "sub_bytes.cpp"
    "shift_rows.cpp"
    "mix_columns.cpp"
    "key_expansion.cpp"
    "aes.h"
)