
// Standard library includes
#include <string>
#include <iostream>
#include <algorithm>

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

  if(key_.empty()) {
    std::cout << "WARNING - Vigenere Cipher key given is empty, replacing with default (the alphabet)" << std::endl;
    key_ = alphabet_;
  }

  for(char &letter : key_) {
    const size_t caesarKey = alphabet_.find(letter);
    charLookup_.insert(std::pair<char, CaesarCipher>(letter, CaesarCipher(caesarKey))); 
  }




}

std::string VigenereCipher::applyCipher(const std::string &inputText, const CipherMode cipherMode) const {

  std::string resizedKey = "";

  std::string outputText = "";

  for(size_t i(0); i < inputText.size(); ++i) {
    resizedKey += key_[i % key_.size()];
  }


  for(size_t i(0); i < inputText.size(); ++i) {
    char matchingKeyLetter = resizedKey[i];
    std::string inputString("");
    inputString += inputText[i];
    outputText += charLookup_.at(matchingKeyLetter).applyCipher(inputString, cipherMode);
  }

  return outputText;

}
