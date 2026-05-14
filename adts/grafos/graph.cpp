#pragma once
#include "../iterator/iterator.cpp"
#include "edge.cpp"

class graph {
public:
  // PRE: -
  // POS: se agrega la arista desde `from` hasta `to`, en caso
  // de que sea un grafo NO dirigido, se agrega en la direccion
  // contraria tambien
  virtual void addEdge(int from, int to) = 0;
  virtual void addWeightedEdge(int from, int to, int weight) = 0;
  virtual void removeEdge(int from, int to) = 0;
  // PRE: existen `from` y `to`
  // POS: -
  // RET: true sii existe arista desde `from` hasta `to`
  virtual bool hasEdge(int from, int to) = 0;
  // PRE: existen `from` y `to`,
  // existe arista desde `from` hasta `to`
  // POS: -
  // RET: retorna el peso de dicha arista
  virtual int getWeight(int from, int to) = 0;
  // PRE: -
  // POS: -
  // RET: devuelve la cantidad de vertices/nodos en el grafo
  // (es decir, el tamano de la primer dimension de la matriz)
  virtual int vertices() = 0;
  virtual int countEdges() = 0;

  virtual Iterador<edge> *edges() = 0;
  // PRE: existe v
  // POS: -
  // RET: iterador sobre las aristas que salen de v
  virtual Iterador<edge> *neighbors(int v) = 0;
  // PRE: -
  // POS: -
  // RET: Una nueva matriz de adyacencia
  virtual int **buildMatrix() = 0;
};
