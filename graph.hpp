#ifndef GRAPH_HPP_INCLUDED
#define GRAPH_HPP_INCLUDED

#include <exception>
#include <filesystem>
#include <fstream>
#include <iomanip>  //setw
#include <iostream>
#include <sstream>  //stringstream
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

// PRIVATE
template <class T>
int Graph<T>::getSize() const {
  int edgeCount(0);

  for (int i(0); i < vertexCount; i++) {
    for (int j(0); j < vertexCount; j++) {
      if (adjMatrix[i][j] != 0) edgeCount++;
    }
  }

  return edgeCount / 2;
}

template <class T>
int Graph<T>::getDensity() const {
  return 2 * getSize() / (vertexCount * (vertexCount - 1));
}

template <class T>
bool Graph<T>::isEmpty() const {
  return vertexCount == 0;
}

template <class T>
void Graph<T>::copyAll(const Graph& g) {
  if (!isEmpty()) {
    deleteAll();
  }

  nodes = new Vertex[vertexCount];
  adjList = new Edge[vertexCount];

  if (nodes == nullptr or adjList == nullptr)
    throw Exception("Memoria insuficiente, copyAll");

  for (int i(0); i < vertexCount; i++) {
    nodes[i] = g.nodes[i];
    adjList[i] = g.adjList[i];
  }

  adjMatrix = new int*[g.vertexCount];
  for (int i(0); i < g.vertexCount; i++) {
    adjMatrix[i] = new int[g.vertexCount];
    for (int j(0); j < g.vertexCount; j++) adjMatrix[i][j] = g.adjMatrix[i][j];
  }

  vertexCount = g.vertexCount;
}

// PUBLIC
template <class T>
Graph<T>::Graph()
    : nodes(nullptr), adjList(nullptr), adjMatrix(nullptr), vertexCount(0) {}

template <class T>
Graph<T>::Graph(const Graph& g) {
  copyAll(g);
}

template <class T>
Graph<T>& Graph<T>::operator=(const Graph& g) {
  if (this != &g) {
    deleteAll();
    copyAll(g);
  }

  return *this;
}

template <class T>
Graph<T>::~Graph() {
  deleteAll();
}

template <class T>
void Graph<T>::addVertex(const T& lab) {
  // Create new nodes +1
  Vertex* newNodes = new Vertex[vertexCount + 1];
  if (newNodes == nullptr) throw Exception("Memoria insuficiente, addVertex");

  // Copy nodes to newNodes
  for (int i(0); i < vertexCount; i++) newNodes[i] = nodes[i];

  // Add vertex at the end
  newNodes[vertexCount].label = lab;

  // delete[] nodes;

  nodes = newNodes;
  vertexCount++;

  // Create new Matrix +1
  int** newAdjMatrix = new int*[vertexCount];
  if (newAdjMatrix == nullptr)
    throw Exception("Memoria insuficiente, addVertex");

  for (int i(0); i < vertexCount; i++) {
    newAdjMatrix[i] = new int[vertexCount];
    if (newAdjMatrix[i] == nullptr)
      if (newAdjMatrix == nullptr)
        throw Exception("Memoria insuficiente, addVertex");

    for (int j(0); j < vertexCount; j++) {
      if (i < vertexCount - 1 and j < vertexCount - 1) {
        newAdjMatrix[i][j] = adjMatrix[i][j];
      } else
        newAdjMatrix[i][j] = 0;
    }
  }

  /*for(int i = 0; i < vertexCount - 1; i++) {
      delete[] adjMatrix[i];
      }
  delete[] adjMatrix;*/

  adjMatrix = newAdjMatrix;
}

template <class T>
void Graph<T>::deleteVertex(const T& lab) {
  int deleteIndex(-1);

  for (int i(0); i < vertexCount; i++) {
    if (nodes[i].label.getName() == lab.getName()) {
      deleteIndex = i;
      break;
    }
  }

  if (deleteIndex == -1) throw Exception("El v�rtice no existe");

  Vertex* newNodes = new Vertex[vertexCount - 1];
  if (newNodes == nullptr)
    throw Exception("Memoria insuficiente, deleteVertex");

  // Copy nodes, omitting the vertex to be removed
  for (int i(0); i < deleteIndex; i++) newNodes[i] = nodes[i];

  for (int i(deleteIndex + 1); i < vertexCount; i++) newNodes[i - 1] = nodes[i];

  // delete[] nodes;

  nodes = newNodes;
  vertexCount--;

  // delete vertex of the matrix
  int** newAdjMatrix = new int*[vertexCount];
  if (newAdjMatrix == nullptr)
    throw Exception("Memoria insuficiente, deleteVertex");

  for (int i(0); i < vertexCount; i++) {
    newAdjMatrix[i] = new int[vertexCount];
    if (newAdjMatrix[i] == nullptr)
      throw Exception("Memoria insuficiente, deleteVertex");

    for (int j(0); j < vertexCount; j++) {
      if (i < deleteIndex and j < deleteIndex) {
        newAdjMatrix[i][j] = adjMatrix[i][j];
      } else if (i >= deleteIndex and j >= deleteIndex) {
        newAdjMatrix[i][j] = adjMatrix[i + 1][j + 1];
      } else if (i >= deleteIndex) {
        newAdjMatrix[i][j] = adjMatrix[i + 1][j];
      } else
        newAdjMatrix[i][j] = adjMatrix[i][j + 1];
    }
  }

  /*for (int i = 0; i < vertexCount + 1; i++) {
      delete[] adjMatrix[i];
      }
  delete[] adjMatrix;*/

  adjMatrix = newAdjMatrix;
}

template <class T>
typename Graph<T>::Vertex* Graph<T>::retrieveVertex(const T& lab) {
  for (int i(0); i < vertexCount; i++)
    if (nodes[i].label == lab) return &nodes[i];

  throw Exception("No existe el vertice");
}

template <class T>
void Graph<T>::addEdge(const T& origLab, const T& destLab, const int& w) {
  int origIdx(-1);  // origin index
  int destIdx(-1);  // destination index

  for (int i(0); i < vertexCount; i++) {
    if (nodes[i].label.getName() == origLab.getName()) origIdx = i;
    if (nodes[i].label.getName() == destLab.getName()) destIdx = i;
  }

  if (origIdx == -1 or destIdx == -1)
    throw Exception("Uno o ambos vertices no existen");

  Edge aux;
  aux.orig = &nodes[origIdx];
  aux.dest = &nodes[destIdx];
  aux.weight = w;

  // add edge to matrix
  adjMatrix[origIdx][destIdx] = w;
  adjMatrix[destIdx][origIdx] = w;
}

template <class T>
void Graph<T>::deleteEdge(const T& origLab, const T& destLab) {
  Vertex* origVertex = retrieveVertex(origLab);
  Vertex* destVertex = retrieveVertex(destLab);

  if (origVertex == nullptr or destVertex == nullptr)
    throw Exception("Uno o ambos v�rtices no existen");

  int origIndex(-1);
  int destIndex(-1);
  for (int i(0); i < vertexCount; i++) {
    if (&nodes[i] == origVertex) origIndex = i;
    if (&nodes[i] == destVertex) destIndex = i;
  }

  // delete edge of the matrix
  adjMatrix[origIndex][destIndex] = 0;
  adjMatrix[destIndex][origIndex] = 0;
}

template <class T>
void Graph<T>::deleteAll() {
  if (adjMatrix != nullptr) {
    for (int i(0); i < vertexCount; i++) delete[] adjMatrix[i];

    delete[] adjMatrix;
    adjMatrix = nullptr;
  }

  delete[] nodes;
  nodes = nullptr;

  delete[] adjList;
  adjList = nullptr;

  vertexCount = 0;
}

template <class T>
std::string Graph<T>::toList() const {
  std::string str;

  for (int i(0); i < vertexCount; i++) {
    str += nodes[i].label.getName() + " ->";
    for (int j(0); j < vertexCount; j++) {
      if (adjMatrix[i][j] != 0) {
        str += " (" + nodes[j].label.getName() + ", " +
               std::to_string(adjMatrix[i][j]) + "), ";
      }
    }

    str = str.substr(0, str.length() - 2);  // delete last comma and space
    str += "\n\n";
  }

  return str;
}

template <class T>
std::string Graph<T>::toMatrix() const {
  std::stringstream strStream;
  short maxLength(12);

  // headline
  for (int i(0); i < vertexCount; i++) {
    // tools for label centering
    std::string str = nodes[i].label.getName();
    int padding = (maxLength - str.length()) / 2;

    strStream << std::setw(padding + str.length()) << str
              << std::setw(maxLength - padding - str.length() + maxLength)
              << " ";
  }
  strStream << '\n';

  for (int i(0); i < vertexCount; i++) {
    // tools for label centering
    std::string str = nodes[i].label.getName();
    int padding = (maxLength - str.length()) / 2;

    strStream << std::setw(padding + str.length()) << str
              << std::setw(maxLength - padding - str.length() + maxLength)
              << " ";
    for (int j(0); j < vertexCount; j++) {
      // weights
      strStream << std::setw(maxLength) << std::to_string(adjMatrix[i][j]);
    }
    strStream << '\n';
  }

  return strStream.str();  // convert from stringstream to string
}

template <class T>
void Graph<T>::importToDisk(const std::string& fileName) {
  
}

template <class T>
void Graph<T>::exportFromDisk(const std::string& fileName) {
  
}

#endif  // GRAPH_HPP_INCLUDED
