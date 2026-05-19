#pragma once

template <class E> class queue {
public:
  virtual bool isEmpty() = 0;
  virtual int size() = 0;
  virtual void push(E elem) = 0;
  virtual E top() = 0;
  virtual E pop() = 0;
};