#pragma once

#include "./list.cpp"
#include <cassert>

template <class T>
class linked_list : public list<T>
{
private:
   struct node
   {
      T data;
      node *next;
   };


class linked_list_iterator : public Iterator<T> {
  private:
    node *curr;

  public:
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
  node *tail = nullptr;
  int length = 0;

  virtual Iterator<T> *getIterator() override {
    return new linked_list_iterator(this->head);
  }

public:
   linked_list()
   {
      this->head = nullptr;
      this->tail = nullptr;
      this->length = 0;
   }

   virtual void add(T data) override
{
   node *nuevo = new node{data, nullptr};

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
      if (!this->head) return;

      node *aux = this->head;
      node *ant = nullptr;

      while (aux)
      {
         if (aux->data == data)
         {
            if (!ant) this->head = aux->next;
            else ant->next = aux->next;
            if (this->tail == aux) this->tail = ant;

            delete aux;
            this->length--;
            if (this->length == 0) this->tail = nullptr;
            return;
         }
         else{
            ant = aux;
            aux = aux->next;
         }
      }
   }

   virtual void removeAt(int pos) override
   {
      if (pos >= this->length) return;
      node *aux = this->head;
      node *prev = nullptr;
      if (pos == 0)
      {
         this->head = aux->next;
         if (this->tail == aux) this->tail = this->head;
         this->length--;
         delete aux;
         if (this->length == 0) this->tail = nullptr;
         return;
      }
      for (int i = 0; i < pos; i++) 
         {
            prev = aux;
            aux = aux->next;
         }
      prev->next = aux->next;
      if (this->tail == aux) this->tail = prev;
      delete aux;
      this->length--;
      if (this->length == 0) this->tail = nullptr;
      return;
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
      if (this->length == 0) return -1;

      node *aux = this->head;
      int cont = 0;

      while (aux){
         if (aux->data == data) return cont;

         aux = aux->next;
         cont++;
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
