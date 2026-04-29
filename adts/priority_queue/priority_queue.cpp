#pragma once

template <class E, class P> class priority_queue {
public:
  virtual bool isEmpty() = 0;
  virtual int size() = 0;
  virtual void push(E elem, P prio) = 0;
  virtual E top() = 0;
  virtual E pop() = 0;
};