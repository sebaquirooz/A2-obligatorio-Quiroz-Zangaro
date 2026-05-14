#pragma once

#include "../iterator/iterator.cpp"
#include "./list_iterator/linked_list.cpp"
#include "./graph.cpp"
#include <assert.h>

class adj_list_graph : public graph
{
private:
  list<edge> **arr;
  // arrSize
  int vertexCount;
  bool isDirected;
  int edgeCount;

public:
  adj_list_graph(int vertices, bool isDirected)
  {
    this->vertexCount = vertices;
    this->isDirected = isDirected;
    this->edgeCount = 0;

    this->arr = new list<edge> *[vertices + 1];
    for (int i = 1; i <= this->vertexCount; i++)
    {
      this->arr[i] = new linked_list<edge>();
    }
  }

  virtual void addEdge(int from, int to) override
  {
    addWeightedEdge(from, to, 1);
  }

  virtual void addWeightedEdge(int from, int to, int weight) override
  {
    removeEdge(from, to);

    edge e = edge(from, to, weight);
    this->arr[from]->add(e);
    if (!this->isDirected)
    {
      edge e = edge(to, from, weight);
      this->arr[to]->add(e);
    }
    this->edgeCount++;
  }

  virtual void removeEdge(int from, int to) override
  {
    bool removed = false;

    list<edge> *nuevaLista = new linked_list<edge>();
    Iterador<edge> *itFrom = neighbors(from);

    while (itFrom->hasNext())
    {
      edge e = itFrom->next();

      if (e.to == to)
      {
        removed = true;
      }
      else
      {
        nuevaLista->add(e);
      }
    }

    this->arr[from] = nuevaLista;

    if (!this->isDirected && from != to)
    {
      list<edge> *nuevaLista2 = new linked_list<edge>();
      Iterador<edge> *itTo = neighbors(to);

      while (itTo->hasNext())
      {
        edge e = itTo->next();

        if (e.to == from)
        {
          removed = true;
        }
        else
        {
          nuevaLista2->add(e);
        }
      }

      this->arr[to] = nuevaLista2;
    }

    if (removed)
    {
      this->edgeCount--;
    }
  }

  virtual bool hasEdge(int from, int to) override
  {
    Iterador<edge> *it = neighbors(from);
    while (it->hasNext())
    {
      edge e = it->next();
      if (e.to == to)
      {
        return true;
      }
    }

    return false;
  }
  virtual int getWeight(int from, int to) override
  {
    Iterador<edge> *it = neighbors(from);
    while (it->hasNext())
    {
      edge e = it->next();
      if (e.to == to)
      {
        return e.weight;
      }
    }

    assert(false);
  }
  virtual int vertices() override { return this->vertexCount; }
  virtual int countEdges() override { return this->edgeCount; }
  virtual Iterador<edge> *edges() override
  {
    list<edge> *listaAristas = new linked_list<edge>();

    for (int i = 1; i <= this->vertexCount; i++)
    {
      Iterador<edge> *iter = neighbors(i);

      while (iter->hasNext())
      {
        edge e = iter->next();

        if (this->isDirected)
        {
          listaAristas->add(e);
        }
        else
        {
          if (e.from <= e.to)
          {
            listaAristas->add(e);
          }
        }
      }
    }

    return listaAristas->iterador();
  }
  virtual Iterador<edge> *neighbors(int v) override
  {
    return this->arr[v]->iterador();
  }
  virtual int **buildMatrix() override
  {
    int **matrix = new int *[this->vertexCount + 1];

    for (int i = 0; i <= this->vertexCount; i++)
    {
      matrix[i] = new int[this->vertexCount + 1];

      for (int j = 0; j <= this->vertexCount; j++)
      {
        matrix[i][j] = 0;
      }
    }

    for (int i = 1; i <= this->vertexCount; i++)
    {
      Iterador<edge> *iter = neighbors(i);

      while (iter->hasNext())
      {
        edge e = iter->next();
        matrix[e.from][e.to] = e.weight;
      }
    }

    return matrix;
  }
};