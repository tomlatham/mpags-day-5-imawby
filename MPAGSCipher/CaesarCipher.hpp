#ifndef MPAGSCIPHER_CAESARCIPHER_HPP
#define MPAGSCIPHER_CAESARCIPHER_HPP

#include <string>
#include <vector>

//! Encrypt or decrypt text using the Caesar cipher with the given key
class CaesarCipher {
  public:
    CaesarCipher( const size_t key );

    std::string applyCipher( const std::string& inputText, const bool encrypt ) const;

  private:
    const std::vector<char> alphabet_ = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    const std::vector<char>::size_type alphabetSize_ = alphabet_.size();

    size_t key_ = 0;
};

#endif
