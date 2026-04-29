#pragma once

#include "./list.cpp"

template <class T> class linked_list : public list<T> {
private:
  struct node {
    T data;
    node *next;
  };

  class linked_list_iterator : public iterator<T> {
    node *curr;

    linked_list_iterator(node *head) { this->curr = head; }

    virtual bool hasNext() override { return this->curr != nullptr; }

    virtual T next() override {
      assert(hasNext());
      T ret = this->curr->data;
      this->curr = this->curr->next;
      return ret;
    }
  };

  node *head = nullptr;
  int length = 0;

public:
  linked_list() {}

  virtual iterator<T> *iterator() override {
    return new linked_list_iterator(this->head);
  }

  virtual void add(T data) override {
    if (this->head == nullptr) {
      this->head = new node{};
      this->head->data = data;
      this->head->next = nullptr;
    } else {
      // rellenar
    }
    this->length++;
  }

  virtual void remove(T data) override {}

  virtual void removeAt(int pos) override {}

  virtual bool exists(T data) override {
    node *aux = this->head;
    while (aux != nullptr) {
      if (aux->data == data) {
        return true;
      }

      aux = aux->next;
    }

    return false;
  }

  virtual int getPos(T data) override {}

  virtual T get(int pos) override {}

  virtual bool isEmpty() override { return this->length == 0; }

  virtual int size() override { return this->length; }
};