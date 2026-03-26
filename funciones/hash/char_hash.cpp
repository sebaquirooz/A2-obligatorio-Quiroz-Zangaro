#pragma once
#include "hash_func.cpp"

class char_hash : public hash_func<char> {
public:
  virtual int hash(char data) override { return data - 'a'; }
};