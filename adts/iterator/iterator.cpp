#pragma once

template <class T>
class Iterador {
public:
  virtual bool hasNext() = 0;
  virtual T next() = 0;
  virtual ~Iterador() {}
};

template <class T>
class Iterable {
public:
  virtual Iterador<T> *iterador() = 0;
  virtual ~Iterable() {}
};