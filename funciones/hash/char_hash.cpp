#pragma once
#include "hash_func.cpp"

class int_hash : public hash_func<int> {
public:
  virtual int hash(char data) override { return (data - 'a'); }
};
