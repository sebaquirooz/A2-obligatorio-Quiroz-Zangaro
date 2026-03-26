#pragma once
#include "hash_func.cpp"
#include <string>

class string_hash : public hash_func<int> {
public:
  virtual int hash(const char *data) override { 
    int i = 0;
    int sum = 0;
    while (data[i] != '\0'){
      sum+= data[i];
      i++;
    }
    return sum;
  }
};
