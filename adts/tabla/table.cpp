#pragma once

template <class K, class V> class table {
  virtual void set(K key, V value) = 0;
  virtual bool contains(K key) = 0;
  virtual V get(K key) = 0;
  virtual void remove(K key) = 0;
  virtual int size() = 0;
};
