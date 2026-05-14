#pragma once

#include "./priority_queue.cpp"
#include <assert.h>

template <class E, class P> class min_heap : public priority_queue<E, P> {
private:
  struct pair {
    E elem;
    P prio;

    pair() : elem(), prio() {}

    pair(E elem) { this->elem = elem; }

    pair(E elem, P prio) {
      this->elem = elem;
      this->prio = prio;
    }
  };

  pair *arr;
  int arrSize;
  int count;

  int leftChild(int n) { return n * 2; }

  int rightChild(int n) { return n * 2 + 1; }

  int parent(int n) { return n / 2; }

  void swap(int a, int b){ //el que sube va primero
    pair aux = arr[b];
    arr[b] = arr[a];
    arr[a] = aux;
  }

  void siftUp(int pos) {
        if (pos <= 0 || pos > count) assert(false);
        if (pos == 1) return;

        int p = parent(pos);
        if (arr[p].prio <= arr[pos].prio) return;

        swap(pos, p);
        siftUp(p);
    }
  void siftDown(int pos) {
        if (pos <= 0 || pos > count) assert(false);

        int posLC = leftChild(pos);
        int posRC = rightChild(pos);

        if (posLC > count) return; // no hijos

        int menor = posLC;

        if (posRC <= count && arr[posRC].prio < arr[posLC].prio) {
            menor = posRC;
        }

        if (arr[menor].prio < arr[pos].prio) {
            swap(menor, pos);
            siftDown(menor);
        }
    }

  void resize(int newSize) {
    pair *oldArr = this->arr;
    this->arr = new pair[newSize];
    this->arrSize = newSize;

    for (int i = 1; i <= this->count; i++) {
      this->arr[i] = oldArr[i];
    }

    delete[] oldArr;
  }

public:
  min_heap(int expectedSize) {
    this->arr = new pair[expectedSize + 1];
    this->count = 0;
    this->arrSize = expectedSize + 1;
  }

  virtual bool isEmpty() override { return this->count == 0; }
  virtual int size() override { return this->count; }
  virtual void push(E elem, P prio) override {
    if (this->count + 1 >= this->arrSize) {
      int newCap = this->arrSize * 2;
      if (this->count + 2 > newCap) {
        newCap = this->count + 2;
      }
      resize(newCap);
    }

    this->count++;
    this->arr[this->count] = pair(elem, prio);

    siftUp(this->count);
  }
  virtual E top() override {
    assert(!isEmpty());
    return this->arr[1].elem;
  }
  virtual E pop() override {
    assert(!isEmpty());
    E ret = this->arr[1].elem;

    this->arr[1] = this->arr[this->count];
    this->count--;
    if (this->count > 0) {
      siftDown(1);
    }

    return ret;
  }
};