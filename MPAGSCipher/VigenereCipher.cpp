
// Standard library includes
#include <string>
#include <iostream>
#include <algorithm>

#include "Alphabet.hpp"
#include "VigenereCipher.hpp"

VigenereCipher::VigenereCipher(const std::string &key) {

  this->setKey(key);

}

void VigenereCipher::setKey(const std::string &key) {

  key_ = key;

  // Make sure the key is upper case
  std::transform(std::begin(key_), std::end(key_), std::begin(key_), ::toupper);

  // Remove non-alphabet characters
  key_.erase(std::remove_if(std::begin(key_), std::end(key_), [](char c){ return !std::isalpha(c);}), std::end(key_));

  // Check that the key is not now empty
  if(key_.empty()) {
    std::cout << "WARNING - Vigenere Cipher key given is empty, replacing with default (the alphabet)" << std::endl;
    key_ = Alphabet::alphabet;
  }

  // Loop through the key
  charLookup_.clear();
  for( const char &letter : key_) {
    const size_t caesarKey { Alphabet::alphabet.find(letter) };
    charLookup_.insert( std::make_pair( letter, CaesarCipher{caesarKey} ) );
  }




}

std::string VigenereCipher::applyCipher(const std::string &inputText, const CipherMode cipherMode) const {

  std::string outputText {""};
  outputText.reserve( inputText.size() );

  const size_t keySize{key_.size()};

  for(size_t i{0}; i < inputText.size(); ++i) {
    const char matchingKeyLetter { key_[i % keySize] };
    const std::string inputString { inputText[i] };
    const CaesarCipher& cipher { charLookup_.at(matchingKeyLetter) };
    outputText += cipher.applyCipher(inputString, cipherMode);
  }

  return outputText;

}
