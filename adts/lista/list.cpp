#pragma once

template <class T>
class list
{
public:
   virtual void add(T data) = 0;
   virtual void remove(T data) = 0;
   virtual void removeAt(int pos) = 0;
   virtual bool exists(T data) = 0;
   virtual int getPos(T data) = 0;
   virtual T get(int pos) = 0;
   virtual bool isEmpty() = 0;
   virtual int size() = 0;
};
