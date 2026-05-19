#pragma once
#include "./queue.cpp"
#include <cassert>

template <class E>
class cola : public queue<E> {
private:
  struct node {
    E elem;
    node *next;
  };

  node *head = nullptr;
  node *tail = nullptr;
  int length = 0;

public:
  cola() {
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
  }

  virtual bool isEmpty() override {
    return this->length == 0;
  }

  virtual int size() override {
    return this->length;
  }

  virtual void push(E elem) override {
    node *nuevo = new node{elem, nullptr};

    if (this->head == nullptr) {
      this->head = nuevo;
      this->tail = nuevo;
    } else {
      this->tail->next = nuevo;
      this->tail = nuevo;
    }

    this->length++;
  }

  virtual E top() override {
    assert(!isEmpty());
    return this->head->elem;
  }

  virtual E pop() override {
    assert(!isEmpty());

    node *aux = this->head;
    E ret = aux->elem;
    this->head = this->head->next;
    if (this->head == nullptr) {
      this->tail = nullptr;
    }

    delete aux;
    this->length--;
    return ret;
  }
};