#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "CaesarCipher.hpp"
#include "PlayfairCipher.hpp"
#include "VigenereCipher.hpp"
#include "CipherMode.hpp"
#include "CipherFactory.hpp"
#include "CipherType.hpp"

void testCipher(const Cipher& cipher, const CipherMode mode, const std::string& inputText, const std::string& outputText);
void testCipher(const std::unique_ptr<Cipher>& cipher, const CipherMode mode, const std::string& inputText, const std::string& outputText);

//--------------------------------------------------------------------------------------------------------------------------------------------------

TEST_CASE("Cipher Encryption Tests", "[encrypt]") {

std::vector<std::unique_ptr<Cipher>> cipherVector;
cipherVector.push_back(cipherFactory(CipherType::Caesar, "2"));
cipherVector.push_back(cipherFactory(CipherType::Playfair, "cipherkey"));
cipherVector.push_back(cipherFactory(CipherType::Vigenere, "cipherkey"));

std::vector<std::string> encryptedStrings = {"LCO", "HKTE", "LIB"};

  for(size_t i(0); i < cipherVector.size(); ++i) {
    testCipher(cipherVector[i], CipherMode::Encrypt, "JAM", encryptedStrings[i]);
  }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

TEST_CASE("Cipher Decryption Tests", "[decrypt]") {

std::vector<std::unique_ptr<Cipher>> cipherVector;
cipherVector.push_back(cipherFactory(CipherType::Caesar, "9"));
cipherVector.push_back(cipherFactory(CipherType::Playfair, "cipherkey"));
cipherVector.push_back(cipherFactory(CipherType::Vigenere, "cipherkey"));

std::vector<std::string> decryptedStrings = {"UZEFJRLI", "FCTNLHNC", "BAYHOJKN"};

  for(size_t i(0); i < cipherVector.size(); ++i) {
    testCipher(cipherVector[i], CipherMode::Decrypt, "DINOSAUR", decryptedStrings[i]);
  }
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

TEST_CASE("Caesar Cipher Encrypt Test", "[caesar]") {
  CaesarCipher cipher("2");
  testCipher(cipher, CipherMode::Encrypt, "JAM", "LCO");
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

TEST_CASE("Caesar Cipher Decrypt Test", "[caesar]") {
  CaesarCipher cipher("9");
  testCipher(cipher, CipherMode::Decrypt, "DINOSAUR", "UZEFJRLI");
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

TEST_CASE("Playfair Cipher Encrypt Test", "[playfair]") {
  PlayfairCipher cipher("cipherkey");
  testCipher(cipher, CipherMode::Encrypt, "JAM" , "HKTE");
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

TEST_CASE("Playfair Cipher Decrypt Test", "[playfair]") {
  PlayfairCipher cipher("cipherkey");
  testCipher(cipher, CipherMode::Decrypt, "DINOSAUR", "FCTNLHNC");
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

TEST_CASE("Vigenere Encrypt Cipher", "[vigenere]") {
  VigenereCipher cipher("cipherkey");
  testCipher(cipher, CipherMode::Encrypt, "JAM", "LIB");
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

TEST_CASE("Vigenere Decrypt Cipher", "[vigenere]") {
  VigenereCipher cipher("cipherkey");
  testCipher(cipher, CipherMode::Decrypt, "DINOSAUR", "BAYHOJKN");
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

void testCipher(const Cipher& cipher, const CipherMode mode, const std::string& inputText, const std::string& outputText) {

  std::string cipheredText = cipher.applyCipher(inputText, mode);
  REQUIRE(cipheredText == outputText);
}

//--------------------------------------------------------------------------------------------------------------------------------------------------

void testCipher(const std::unique_ptr<Cipher>& cipher, const CipherMode mode, const std::string& inputText, const std::string& outputText) {

  std::string cipheredText = cipher->applyCipher(inputText, mode);
  REQUIRE(cipheredText == outputText);
}

