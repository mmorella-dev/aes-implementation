# morellam-dev / cs-3626-special-project-aes

An partial implementation of the [Advanced Encryption Standard](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard) (AES). Created as a project for CS 3626 - Cryptography.

## Building

Due to the use of C++20 features (including [\<ranges\>](https://en.cppreference.com/w/cpp/ranges), [std::span](https://en.cppreference.com/w/cpp/container/span), and [std::bit_cast](https://en.cppreference.com/w/cpp/numeric/bit_cast), this project is only compatible with the limited number of compilers which fully implement these library features. At time of writing, this requires GCC v12 or later.

```
mkdir -p build && cd build
CXX=(which g++-12) cmake .. --fresh
# g++-12 is for macOS. on other systems, just g++.
make
./src/main # runs tests
```

Currently, [main.cpp](src/main.cpp) only implements a set of tests to ensure each function produces the intended output.

## Disclaimer

This repository contains solutions to school-assigned homework and lab assignments, and should be used only for reference and educational purposes by ***persons who are not currently enrolled students of Kennesaw State University or taking a similar class.*** Plagiarism or uncredited copying of this code is in violation of university policy, and is harshly discouraged.

I create and maintain this repository only for personal use, both to ensure I can access my projects from multiple machines, and as an exercise to improve my skills with GitHub and version control. It is not an attempt to share homework solutions. I hope in the future that its professional appearance may be appealing to potential employers.

***Under no circumstances should any of these files be copied or submitted as your own work.***

## License

Copyright © 2022 morellam-dev. All rights reserved. NO WARRANTY.
