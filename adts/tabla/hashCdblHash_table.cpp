#pragma once

#include "../../funciones/hash/hash_func.cpp"
#include "../../funciones/enteros.cpp"
#include "table.cpp"
#include <assert.h>

template <class K, class V>
class hashCdblHash_table : public table<K, V>
{
private:
  struct kv_pair
  {
    K key;
    V value;
    bool is_deleted = false;

    kv_pair(K key, V value)
    {
      this->key = key;
      this->value = value;
    }
  };

  hash_func<K> *h;
  kv_pair **buckets;
  int bucketCount;
  int elementsCount = 0;

  int fPos(int hash, int collisions)
  {
    int h1 = abs(hash) % this->bucketCount;
    int h2 = 1 + (abs(hash) % (this->bucketCount - 1));
    return (h1 + collisions * h2) % this->bucketCount;
  }

public:
  hashCdblHash_table(int expectedSize, hash_func<K> *h)
  {
    this->h = h;
    this->bucketCount = expectedSize * 2 - 1;
    if (this->bucketCount < 3)
      this->bucketCount = 3; // arregla problema tabla de tamaño 1. en tests/ejercicio2/minimo.in.txt nos quedaba una tabla de tamaño 1, y al hacer fPos, en h2 nos hacia un % 0.
    this->buckets = new kv_pair *[this->bucketCount]();
  }

  virtual ~hashCdblHash_table()
  {
    for (int i = 0; i < this->bucketCount; i++)
    {
      delete this->buckets[i];
    }

    delete[] this->buckets;
  }

  /*virtual void rehash(int newSize) {
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
  }*/
  virtual void rehash(int newSize)
  {
    kv_pair **oldArr = this->buckets;
    int oldSize = this->bucketCount;

    if (newSize < 3)
    {
      newSize = 3;
    }
    this->bucketCount = newSize;
    this->buckets = new kv_pair *[this->bucketCount]();
    this->elementsCount = 0;

    for (int i = 0; i < oldSize; i++)
    {
      kv_pair *pair = oldArr[i];
      if (pair != nullptr)
      {
        if (!pair->is_deleted)
        {
          this->set(pair->key, pair->value);
        }
        delete pair;
      }
    }
    delete[] oldArr;
  }
  virtual void set(K key, V value) override
  {

    int hash = this->h->hash(key);
    for (int collisions = 0; collisions < this->bucketCount; collisions++)
    {
      int pos = fPos(hash, collisions);
      kv_pair *pair = this->buckets[pos];

      if (pair == nullptr)
      {
        this->buckets[pos] = new kv_pair(key, value);
        this->elementsCount++;
        return;
      }

      if (pair->is_deleted || pair->key == key)
      {
        bool was_deleted = pair->is_deleted;
        pair->key = key;
        pair->value = value;
        pair->is_deleted = false;
        if (was_deleted)
        {
          this->elementsCount++;
        }
        return;
      }
    }
    this->rehash(this->bucketCount * 2 + 1);
    this->set(key, value);
  }
  /*
  virtual void set(K key, V value) override {

    int hash = this->h->hash(key);
    int collisions = 0;

    while (true) {
      int pos = fPos(hash, collisions);
      kv_pair *pair = this->buckets[pos];

      if (pair == nullptr){
        this->buckets[pos] = new kv_pair(key, value);
        this->elementsCount++;
        return;
      }

      if (pair->is_deleted || pair->key == key){
        pair->key = key;
        pair->value = value;
        pair->is_deleted = false;
        if (pair->is_deleted) this->elementsCount++;
        return;
      }
      collisions++;
    }
  }
  */

  /*
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
    */
  virtual bool contains(K key) override
  {

    int hash = this->h->hash(key);
    for (int collisions = 0; collisions < this->bucketCount; collisions++)
    {
      int pos = fPos(hash, collisions);
      kv_pair *pair = this->buckets[pos];

      if (pair == nullptr)
        return false;

      if (pair->key == key && !pair->is_deleted)
      {
        return true;
      }
    }
    return false;
  }

  /*
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
  */
  virtual void remove(K key) override
  {

    int hash = this->h->hash(key);
    for (int collisions = 0; collisions < this->bucketCount; collisions++)
    {
      int pos = fPos(hash, collisions);
      kv_pair *pair = this->buckets[pos];

      if (pair == nullptr)
        assert(false);

      if (pair->key == key && !pair->is_deleted)
      { // Evito borrar algo ya eliminado
        pair->is_deleted = true;
        this->elementsCount--;
        return;
      }
    }
    assert(false);
  }
  /*
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
  */

  virtual V get(K key) override
  {
    int hash = this->h->hash(key);
    for (int collisions = 0; collisions < this->bucketCount; collisions++)
    {
      int pos = fPos(hash, collisions);
      kv_pair *pair = this->buckets[pos];
      if (pair == nullptr)
      {
        assert(false);
      }
      if (!pair->is_deleted && pair->key == key)
      {
        return pair->value;
      }
    }
    assert(false);
  }

  virtual int size() override { return this->elementsCount; }
};
