#pragma once

struct edge {
  int from;
  int to;
  int weight;

  bool operator==(const edge &other) const {
    return this->from == other.from && this->to == other.to;
  }

  edge(int from, int to) {
    this->from = from;
    this->to = to;
    this->weight = 1;
  }

  edge(int from, int to, int weight) {
    this->from = from;
    this->to = to;
    this->weight = weight;
  }
};