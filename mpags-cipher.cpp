// Standard Library includes
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// Our project headers
#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"
#include "RunCaesarCipher.hpp"
  
// Main function of the mpags-cipher program
int main(int argc, char* argv[])
{
  // Convert the command-line arguments into a more easily usable form
  const std::vector<std::string> cmdLineArgs {argv, argv+argc};

  // Options that might be set by the command-line arguments
  bool helpRequested {false};
  bool versionRequested {false};
  std::string inputFile {""};
  std::string outputFile {""};
  std::string cipher_key {""};
  bool encrypt {true};

  // Process command line arguments
  bool cmdLineStatus = processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile, cipher_key, encrypt);

  // Any failure in the argument processing means we can't continue
  // Use a non-zero return value to indicate failure
  if( !cmdLineStatus ) {
    return 1;
  }

  // Handle help, if requested
  if (helpRequested) {
    // Line splitting for readability
    std::cout
      << "Usage: mpags-cipher [-i <file>] [-o <file>] [-k <key>] [--encrypt/--decrypt]\n\n"
      << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
      << "Available options:\n\n"
      << "  -h|--help        Print this help message and exit\n\n"
      << "  --version        Print version information\n\n"
      << "  -i FILE          Read text to be processed from FILE\n"
      << "                   Stdin will be used if not supplied\n\n"
      << "  -o FILE          Write processed text to FILE\n"
      << "                   Stdout will be used if not supplied\n\n"
      << "  -k KEY           Specify the cipher KEY\n"
      << "                   A null key, i.e. no encryption, is used if not supplied\n\n"
      << "  --encrypt        Will use the cipher to encrypt the input text (default behaviour)\n\n"
      << "  --decrypt        Will use the cipher to decrypt the input text\n\n";
    // Help requires no further action, so return from main,
    // with 0 used to indicate success
    return 0;
  }

  // Handle version, if requested
  if (versionRequested) {
    std::cout << "0.2.0" << std::endl;
    // Like help, requires no further action, so return from main,
    // with 0 used to indicate success
    return 0;
  }

  // Initialise variables for processing input text
  char inputChar {'x'};
  std::string inputText {""};

  // Read in user input from stdin/file
  if (!inputFile.empty()) {

    // Open the file and check that we can read from it
    std::ifstream inputStream(inputFile);
    if (!inputStream.good()) {
      std::cerr << "[error] failed to create istream on file '" << inputFile << "'" << std::endl;
      return 1;
    }

    // Loop over each character from the file
    while(inputStream >> inputChar)
    {
      inputText += transformChar(inputChar);
    }

  } else {

    // Loop over each character from user input
    // (until Return then CTRL-D (EOF) pressed)
    while(std::cin >> inputChar)
    {
      inputText += transformChar(inputChar);
    }
  }

  // We have the key as a string, but the Caesar cipher needs an unsigned long, so we first need to convert it
  // Since the conversion can throw an exception if the string does not represent an integer, we should handle that eventuality
  // (we have not covered exceptions at all in the course so far but could do so briefly in week 6 if there is sufficient interest
  // - we include the code below for completeness, feel free to ask us about it)
  size_t caesar_key {0};
  if ( ! cipher_key.empty() ) {
    try {

      caesar_key = std::stoul(cipher_key);

    } catch ( const std::invalid_argument& ) {

      std::cerr << "[error] cipher key must be an unsigned long integer for Caesar cipher,\n"
	<< "        the supplied key (" << cipher_key << ") could not be successfully converted" << std::endl;
      return 1;

    } catch ( const std::out_of_range& ) {

      std::cerr << "[error] cipher key must be an unsigned long integer for Caesar cipher,\n"
	<< "        the supplied key (" << cipher_key << ") was not of the right range" << std::endl;
      return 1;
    }
  }

  // Run the Caesar cipher (using the specified key and encrypt/decrypt flag) on the input text
  std::string outputText = runCaesarCipher( inputText, caesar_key, encrypt );

  // Output the transliterated text
  if (!outputFile.empty()) {

    // Open the file and check that we can write to it
    std::ofstream outputStream(outputFile);
    if (!outputStream.good()) {
      std::cerr << "[error] failed to create ostream on file '" << outputFile << "'" << std::endl;
      return 1;
    }

    // Print the transliterated text to the file
    outputStream << outputText << std::endl;

  } else {

    // Print the transliterated text to the screen
    std::cout << outputText << std::endl;
  }

  // No requirement to return from main, but we do so for clarity
  // and for consistency with other functions
  return 0;
}
