# mpags-cipher
A simple command line tool for encrypting/decrypting text using classical ciphers

# Building `mpags-cipher`
Compilation of `mpags-cipher` requires the [CMake](http://www.cmake.org)
build tool, plus a  C++11 compatible compiler (GCC 4.8 or better, Clang
3.4 or better are recommended) and `make` on a UNIX operating system.
Windows platforms with Visual Studio 2015 or better are also expected to
work, but not tested.

To build from a clone of this repository, open a terminal window
and change directory into that holding this README. Create a build
directory in which to run `cmake` and the build, and change into it:

```
$ ls
CMakeLists.txt   LICENSE          MPAGSCipher      README.md        mpags-cipher.cpp
$ mkdir ../Build
$ cd ../Build
```

Run `cmake` in this directory, pointing it to the directory holding this
README, and consequently the top level CMake script for the project:

```
$ cmake ../<this dir>
... system specific output ...
-- Configuring done
-- Generating done
-- Build files have been written to: ... your build dir path ...
$
```

The exact output will depend on your system, compiler and build directory
location, but you should not see any errors. CMake will generate
Makefiles by default on UNIX platforms, so to build, simply run `make`
in the build directory:

```
$ ls
CMakeCache.txt      CMakeFiles          Makefile            cmake_install.cmake
$ make
... verbose output ...
[100%] Built target mpags-cipher
...
$
```

Again, the exact output will be system specific, but you should see the
`mpags-cipher` target built without error. The resulting `mpags-cipher`
executable can then be run directly, and provides the following command
line options:

```
$ ./mpags-cipher --help
Usage: mpags-cipher [-i/--infile <file>] [-o/--outfile <file>] [-c/--cipher <cipher>] [-k/--key <key>] [--encrypt/--decrypt]

Encrypts/Decrypts input alphanumeric text using classical ciphers

Available options:

  -h|--help
                      Print this help message and exit

  -v|--version
                      Print version information

  -i|--infile FILE
                      Read text to be processed from FILE
                      Stdin will be used if not supplied

  -o|--outfile FILE
                      Write processed text to FILE
                      Stdout will be used if not supplied

  -c|--cipher CIPHER
                      Specify the cipher to be used to perform the encryption/decryption
                      CIPHER can be caesar, playfair or vigenere - caesar is the default

  -k|--key KEY
                      Specify the cipher KEY
                      A null key, i.e. no encryption, is used if not supplied

  --encrypt
                      Will use the cipher to encrypt the input text (default behaviour)

  --decrypt
                      Will use the cipher to decrypt the input text
```

If no input file is supplied, `mpags-cipher` will wait for user input
from the keyboard until RETURN followed by CTRL-D are pressed.
It will then echo the input to stdout or write it to the file supplied with
the `-o` option.

To ensure the input text can be used with the character sets known to
classical ciphers, it is transliterated using the following rules:

- Alphabetical characters are converted to uppercase
- Digits are translated to their English equivalent words (e.g. '0' -> "ZERO")
- All other characters (punctuation) are discarded

At present, the Caesar, Playfair and Vigenere ciphers are supported.

# Testing

After building the MPAGSCipher library it can be tested by running `ctest -VV` from the build directory.

# Source Code Layout
Under this directory, the code and associated files are organised as
follows:

```
MPAGS-Code
├── README.md             This file, describes the project
├── LICENSE               License file, in our case MIT
├── CMakeLists.txt        CMake build script
├── mpags-cipher.cpp      Main program C++ source file
├── Documentation         Subdirectory for documentation of the MPAGSCipher library
│   ├── CMakeLists.txt
│   └── Doxyfile.in
├── MPAGSCipher           Subdirectory for MPAGSCipher library code
│   ├── CMakeLists.txt
│   ├── Alphabet.hpp
│   ├── CaesarCipher.cpp
│   ├── CaesarCipher.hpp
│   ├── Cipher.hpp
│   ├── CipherFactory.cpp
│   ├── CipherFactory.hpp
│   ├── CipherMode.hpp
│   ├── CipherType.hpp
│   ├── PlayfairCipher.cpp
│   ├── PlayfairCipher.hpp
│   ├── ProcessCommandLine.cpp
│   ├── ProcessCommandLine.hpp
│   ├── TransformChar.cpp
│   ├── TransformChar.hpp
│   ├── VigenereCipher.cpp
│   └── VigenereCipher.hpp
├── Testing               Subdirectory for testing the MPAGSCipher library
│   ├── CMakeLists.txt
│   ├── catch.hpp
│   ├── testCaesarCipher.cpp
│   ├── testCatch.cpp
│   ├── testCiphers.cpp
│   ├── testHello.cpp
│   ├── testPlayfairCipher.cpp
│   ├── testProcessCommandLine.cpp
│   ├── testTransformChar.cpp
│   └── testVigenereCipher.cpp
```

# Copying
`mpags-cipher` is licensed under the terms of the MIT License. Please see
the file [`LICENSE`](LICENSE) for full details.

