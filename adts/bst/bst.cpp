#pragma once

template <class T>
class bst
{
public:
   virtual void insert(T data) = 0;
   virtual void remove(T data) = 0;
   virtual void printInOrder() = 0;
   virtual int size() = 0;
   virtual int height() = 0;
};
