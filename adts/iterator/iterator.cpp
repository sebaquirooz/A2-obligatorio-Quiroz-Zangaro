#pragma once

template <class T> class iterator {
public:
  virtual bool hasNext() = 0;
  virtual T next() = 0;
};

template <class T> class iterable {
public:
  virtual iterator<T> *iterator() = 0;
};