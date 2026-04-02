#pragma once
#include "hash_func.cpp"
#include <string>

using namespace std;

class string_hash : public hash_func<string> {
public:
  virtual int hash(string data) override { 
    int sum = 0;
    for (int i = 0; i < data.length(); i++) {
        sum += data[i];
    }
    return sum;
  }
};