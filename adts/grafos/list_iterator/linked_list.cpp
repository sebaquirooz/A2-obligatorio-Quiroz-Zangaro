#pragma once

#include <cassert>
#include "./list.cpp"

template <class T>
class linked_list : public list<T>
{
private:
  struct node
  {
    T data;
    node *next;

    node(T data, node *next = nullptr) : data(data), next(next) {}
  };

  class linked_list_iterador : public Iterador<T>
  {
  private:
    node *curr;

  public:
    linked_list_iterador(node *head)
    {
      this->curr = head;
    }

    virtual bool hasNext() override
    {
      return this->curr != nullptr;
    }

    virtual T next() override
    {
      assert(hasNext());

      T ret = this->curr->data;
      this->curr = this->curr->next;

      return ret;
    }
  };

  node *head = nullptr;
  node *tail = nullptr;
  int length = 0;

public:
  linked_list()
  {
    this->head = nullptr;
    this->tail = nullptr;
    this->length = 0;
  }

  virtual Iterador<T> *iterador() override
  {
    return new linked_list_iterador(this->head);
  }

  virtual void add(T data) override
  {
    node *nuevo = new node(data);

    if (this->head == nullptr)
    {
      this->head = nuevo;
      this->tail = nuevo;
    }
    else
    {
      this->tail->next = nuevo;
      this->tail = nuevo;
    }

    this->length++;
  }

  virtual void remove(T data) override
  {
    if (this->head == nullptr)
      return;

    if (this->head->data == data)
    {
      node *aBorrar = this->head;
      this->head = this->head->next;
      if (this->tail == aBorrar) this->tail = this->head;
      delete aBorrar;
      this->length--;
      if (this->length == 0) this->tail = nullptr;
      return;
    }

    node *aux = this->head;

    while (aux->next != nullptr && !(aux->next->data == data))
    {
      aux = aux->next;
    }

    if (aux->next != nullptr)
    {
      node *aBorrar = aux->next;
      aux->next = aux->next->next;
      if (this->tail == aBorrar) this->tail = aux;
      delete aBorrar;
      this->length--;
      if (this->length == 0) this->tail = nullptr;
    }
  }

  virtual void removeAt(int pos) override
  {
    assert(pos >= 0 && pos < this->length);

    if (pos == 0)
    {
      node *aBorrar = this->head;
      this->head = this->head->next;
      if (this->tail == aBorrar) this->tail = this->head;
      delete aBorrar;
      this->length--;
      if (this->length == 0) this->tail = nullptr;
      return;
    }

    node *aux = this->head;

    for (int i = 0; i < pos - 1; i++)
    {
      aux = aux->next;
    }

    node *aBorrar = aux->next;
    aux->next = aux->next->next;
    if (this->tail == aBorrar) this->tail = aux;
    delete aBorrar;
    this->length--;
    if (this->length == 0) this->tail = nullptr;
  }

  virtual bool exists(T data) override
  {
    node *aux = this->head;

    while (aux != nullptr)
    {
      if (aux->data == data)
      {
        return true;
      }

      aux = aux->next;
    }

    return false;
  }

  virtual int getPos(T data) override
  {
    node *aux = this->head;
    int pos = 0;

    while (aux != nullptr)
    {
      if (aux->data == data)
      {
        return pos;
      }

      aux = aux->next;
      pos++;
    }

    return -1;
  }

  virtual T get(int pos) override
  {
    assert(pos >= 0 && pos < this->length);

    node *aux = this->head;

    for (int i = 0; i < pos; i++)
    {
      aux = aux->next;
    }

    return aux->data;
  }

  virtual bool isEmpty() override
  {
    return this->length == 0;
  }

  virtual int size() override
  {
    return this->length;
  }
};
