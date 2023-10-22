#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <fstream>
#include <iostream>
#include <string>

template <class T>
class Graph {
  class Vertex {
    friend class Graph;

    T label;
    int grade;

    bool isReachable;
    bool isConnected;
    bool isCutpoint;

   public:
    Vertex() : grade(0) {}
    Vertex(const Vertex& v) : label(v.label), grade(v.grade) {}
    Vertex& operator=(const Vertex& v) {
      label = v.label;
      grade = v.grade;

      return *this;
    }
  };

  class Edge {
    friend class Graph;

    Vertex* orig;  // origin
    Vertex* dest;  // destination
    int weight;

    bool isBridge;

   public:
    Edge() : orig(nullptr), dest(nullptr), weight(0), isBridge(false) {}
    Edge(const Edge& e)
        : orig(e.orig), dest(e.dest), weight(e.weight), isBridge(e.isBridge) {}
    Edge& operator=(const Edge& e) {
      orig = e.orig;
      dest = e.dest;
      weight = e.weight;
      isBridge = e.isBridge;

      return *this;
    }
  };

  Vertex* nodes;
  Edge* adjList;
  int** adjMatrix;

  int vertexCount;

  int getSize() const;  // graph size
  int getDensity() const;

  bool isEmpty() const;

  void copyAll(const Graph&);

 public:
  class Exception : public std::exception {
   public:
    Exception(const std::string& message) : msg(message) {}
    const char* what() const noexcept override { return msg.c_str(); }

   private:
    std::string msg;
  };

  Graph();
  Graph(const Graph&);

  Graph& operator=(const Graph&);

  ~Graph();

  void addVertex(const T&);
  void deleteVertex(const T&);
  void findVertex(const T&);

  Vertex* retrieveVertex(const T&);

  void addEdge(const T&, const T&, const int&);  // orig, dest, weight
  void deleteEdge(const T&, const T&);           // orig, dest

  void deleteAll();

  std::string toList() const;
  std::string toMatrix() const;

  /// paths
  /// routes

  void importToDisk(const std::string&);    // file name
  void exportFromDisk(const std::string&);  // file name
};

#endif  // GRAPH_HPP_INCLUDED
