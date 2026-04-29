#pragma once

#include "../iterator/iterator.cpp"
#include "./list_iterator/linked_list.cpp"
#include "./graph.cpp"
#include <assert.h>

class adj_list_graph : public graph {
private:
  list<edge> **arr;
  // arrSize
  int vertexCount;
  bool isDirected;
  int edgeCount;

public:
  adj_list_graph(int vertices, bool isDirected) {
    this->vertexCount = vertices;
    this->isDirected = isDirected;
    this->edgeCount = 0;

    this->arr = new list<edge> *[vertices + 1];
    for (int i = 1; i <= this->vertexCount; i++) {
      this->arr[i] = new linked_list<edge>();
    }
  }

  virtual void addEdge(int from, int to) override {
    addWeightedEdge(from, to, 1);
  }

  virtual void addWeightedEdge(int from, int to, int weight) override {
    removeEdge(from, to);

    edge e = edge(from, to, weight);
    this->arr[from]->add(e);
    if (!this->isDirected) {
      edge e = edge(to, from, weight);
      this->arr[to]->add(e);
    }
    this->edgeCount++;
  }

  virtual void removeEdge(int from, int to) override { assert(false); }

  virtual bool hasEdge(int from, int to) override {
    iterator<edge> *it = neighbors(from);
    while (it->hasNext()) {
      edge e = it->next();
      if (e.to == to) {
        return true;
      }
    }

    return false;
  }
  virtual int getWeight(int from, int to) override {
    iterator<edge> *it = neighbors(from);
    while (it->hasNext()) {
      edge e = it->next();
      if (e.to == to) {
        return e.weight;
      }
    }

    assert(false);
  }
  virtual int vertices() override { return this->vertexCount; }
  virtual int countEdges() override { return this->edgeCount; }
  virtual iterator<edge> *edges() override { assert(false); }
  virtual iterator<edge> *neighbors(int v) override {
    return this->arr[v]->iterator();
  }
  virtual int **buildMatrix() override { assert(false); }
};