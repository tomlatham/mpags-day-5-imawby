#ifndef MPAGSCIPHER_VIGENERECIPHER_HPP
#define MPAGSCIPHER_VIGENERECIPHER_HPP

// Standard library includes
#include <map>

// Our project headers
#include "Cipher.hpp"
#include "CaesarCipher.hpp"


class VigenereCipher : public Cipher {

public:

  explicit VigenereCipher(const std::string &key);

  void setKey(const std::string &key);

  virtual std::string applyCipher(const std::string &inputText, const CipherMode /*cipherMode*/) const override;


private: 

  // The cipher key
  std::string key_ = "";

  std::string alphabet_ = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

  // Lookup table
  std::map<char, CaesarCipher> charLookup_;

};


#endif
