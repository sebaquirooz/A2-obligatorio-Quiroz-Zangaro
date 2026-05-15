#pragma once
#include <string>
#include "hash_func.cpp"

class string_hash : public hash_func<std::string> {
    public:
        int hash(std::string palabra) override {
            int a = 0;
            for (char c : palabra) {
                a = a * 31 + c;
            }
            return a;
        }
};
