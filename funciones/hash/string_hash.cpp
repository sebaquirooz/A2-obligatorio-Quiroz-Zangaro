#pragma once
#include "hash_func.cpp"
#include <string>

using namespace std;

class string_hash : public hash_func<string> {
public:
  virtual int hash(string data) override { 
    unsigned int hash = 2166136261u;
    for (int i = 0; i < data.length(); i++) {
        hash ^= (unsigned char)data[i];
        hash *= 16777619u;
    }
    return (int)(hash & 0x7fffffff);
  }
};
