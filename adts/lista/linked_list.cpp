#pragma once

#include "./list.cpp"

template <class T>
class linked_list : public list<T>
{
private:
   struct node
   {
      T data;
      node *next;
   };

   node *head = nullptr;
   int length = 0;

public:
   linked_list() {}

   virtual void add(T data) override
   {
      if (this->head == nullptr)
      {
         this->head = new node{};
         this->head->data = data;
         this->head->next = nullptr;
      }
      else
      {
         node *aux = this->head;
         while (aux->next) aux = aux->next;
         aux->next = new node{data, nullptr};
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

            delete aux;
            this->length--;
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
         this->length--;
         delete aux;
         return;
      }
      for (int i = 0; i < pos; i++) 
         {
            prev = aux;
            aux = aux->next;
         }
      prev->next = aux->next;
      delete aux;
      this->length--;
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
      if (pos >= this->length || pos < 0) return T{};
      node *aux = this->head;
      for (int i = 0; i < pos; i++) aux = aux->next;
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

