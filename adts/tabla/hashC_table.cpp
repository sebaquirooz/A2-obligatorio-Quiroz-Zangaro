#pragma once

#include "../../functions/hash/hash_func.cpp"
#include "../../functions/ints.cpp"
#include "table.cpp"
#include <assert.h>

template <class K, class V> class hashC_table : public table<K, V> {
private:
  struct kv_pair {
    K key;
    V value;
    bool is_deleted = false;

    kv_pair(K key, V value) {
      this->key = key;
      this->value = value;
    }
  };

  hash_func<K> *h;
  kv_pair **buckets;
  int bucketCount;
  int elementsCount = 0;

  int fPos(int hash, int collisions) {
    return abs(hash + collisions) % this->bucketCount;
  }

public:
  hashC_table(int expectedSize, hash_func<K> *h) {
    this->h = h;
    this->bucketCount = expectedSize * 2 - 1;
    this->buckets = new kv_pair *[this->bucketCount]();
  }

  virtual void rehash(int newSize) {
    kv_pair **oldArr = this->buckets;
    int oldSize = this->bucketCount;

    this->bucketCount = newSize;
    this->buckets = new kv_pair *[this->bucketCount]();

    for (int i = 0; i < oldSize; i++) {
      kv_pair *pair = oldArr[i];
      if (pair != nullptr && !pair->is_deleted) {
        this->set(pair->key, pair->value);
      }
    }
  }

  virtual void set(K key, V value) override {

    int hash = this->h->hash(key);
    int collisions = 0;

    while (true) {
      int pos = fPos(hash, collisions);
      kv_pair *pair = this->buckets[pos];

      if (pair == nullptr){
        this->bucket[pos] = new kv_pair(key, value);
        this->elementsCout++;
        return;
      }

      if (pair->is_deleted || pair->key == key){ 
        pair->key = key;
        pair->value = value;
        pair->is_deleted = false;
        this->elementsCount++;
        return;
      }
      collisions++;
    }
  }

  virtual bool contains(K key) override {

    int hash = this->h->hash(key);
    int collisions = 0;

    while (true) {
      int pos = fPos(hash, collisions);
      kv_pair *pair = this->buckets[pos];

      if (pair == nullptr) return false;

      if (pair->key == key && !pair->is_deleted){
        return true;
      }
      collisions++;
    }
  }

  virtual void remove(K key) override { 

    int hash = this->h->hash(key);
    int collisions = 0;

    while (true) {
      int pos = fPos(hash, collisions);
      kv_pair *pair = this->buckets[pos];

      if (pair == nullptr) assert(false);

      if (pair->key == key && !pair->is_deleted){ //Evito borrar algo ya eliminado
        pair->is_deleted = true;
        this->elementsCount--;
        return;
      }
      collisions++;
    }
  }

  virtual V get(K key) override {
    int hash = this->h->hash(key);
    int collisions = 0;

    while (true) {
      int pos = fPos(hash, collisions);
      kv_pair *pair = this->buckets[pos];
      if (pair == nullptr) {
        // null es que no lo encontramos, no cumple la
        // precondicion de pertenecer, entonces que explote
        assert(false);
      }
      if (pair->is_deleted || pair->key != key) {
        collisions++;
      } else {
        return pair->value;
      }
    }
  }

  virtual int size() override { return this->elementsCount; }
  };
