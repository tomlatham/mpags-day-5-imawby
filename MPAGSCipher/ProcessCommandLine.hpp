#ifndef MPAGSCIPHER_PROCESSCOMMANDLINE_HPP
#define MPAGSCIPHER_PROCESSCOMMANDLINE_HPP

// Standard library includes
#include <string>
#include <vector>

// Our project headers
#include "CipherMode.hpp"

struct ProgramSettings {
  bool helpRequested;     ///< Indicates the presence of the help flag in the arguments
  bool versionRequested;  ///< Indicates the presence of the version flag in the arguments
  std::string inputFile;  ///< Name of the input file
  std::string outputFile; ///< Name of the output file
  std::string cipherKey;  ///< Key to be used in encrypting/decrypting routine
  CipherMode cipherMode;  ///< Flag indicating the mode in which the cipher should run (i.e. encrypt or decrypt)
};

bool processCommandLine(const std::vector<std::string>& args,
                        ProgramSettings& settings);

#endif // MPAGSCIPHER_PROCESSCOMMANDLINE_HPP 
