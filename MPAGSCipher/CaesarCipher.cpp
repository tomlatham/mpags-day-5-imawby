
// Standard library includes
#include <string>
#include <vector>

// Out project headers
#include "CaesarCipher.hpp"

CaesarCipher::CaesarCipher( const size_t key )
  : key_{key}
{
}

std::string CaesarCipher::applyCipher( const std::string& inputText, const CipherMode cipherMode ) const
{
  // Create the output string
  std::string outputText {};

  // Loop over the input text
  char processedChar {'x'};
  for ( const auto& origChar : inputText ) {

    // For each character in the input text, find the corresponding position in
    // the alphabet by using an indexed loop over the alphabet container
    for ( size_t i{0}; i < alphabetSize_; ++i ) {

      if ( origChar == alphabet_[i] ) {

	// Apply the appropriate shift (depending on whether we're encrypting
	// or decrypting) and determine the new character
	// Can then break out of the loop over the alphabet
	switch ( cipherMode ) {
	  case CipherMode::Encrypt :
	    processedChar = alphabet_[ (i + key_) % alphabetSize_ ];
	    break;
	  case CipherMode::Decrypt :
	    processedChar = alphabet_[ (i + alphabetSize_ - key_) % alphabetSize_ ];
	    break;
	}
	break;
      }
    }

    // Add the new character to the output text
    outputText += processedChar;
  }

  return outputText;
}
