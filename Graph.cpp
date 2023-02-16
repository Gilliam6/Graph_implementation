#include "Graph.hpp"

template<typename T>
Graph<T, std::vector<T> >::Graph(size_t size) {
   edges.assign(size, std::vector<T>(size));
   numVertices = size;
};

template<typename T>
Graph<T, std::vector<T> >::Graph(const std::vector<std::pair<T,T> >& v) {
   std::vector<std::pair<int,int>> cp = v;
   std::sort(cp.begin(), cp.end(), [](const auto& l, const auto& r){return std::max(l.first, l.second) > std::max(r.first, r.second); });
   auto max = std::max(cp[0].first, cp[0].second) + 1;
   edges.assign(max, std::vector<T>(max));
   numVertices = max;
   for (auto [x,y] : cp) {
      addEdge(x, y);
   }
};

template<typename T>
Graph<T, std::list<T> >::Graph(size_t size) {
   edges.assign(size, std::list<T>());
   numVertices = size;
};

template<typename T>
Graph<T, std::list<T> >::Graph(const std::vector<std::pair<T,T> >& v) {
   std::vector<std::pair<int,int>> cp = v;
   std::sort(cp.begin(), cp.end(), [](const auto& l, const auto& r){return std::max(l.first, l.second) > std::max(r.first, r.second); });
   auto max = std::max(cp[0].first, cp[0].second) + 1;
   edges.assign(max, std::list<T>());
   numVertices = max;
   for (auto [x,y] : cp) {
      addEdge(x, y);
   }
};

template<typename T>
Graph<T, std::vector<T> >::~Graph() {};

template<typename T>
Graph<T, std::list<T> >::~Graph() {};

template<typename T>
std::vector<std::pair<int,int> > Graph<T, std::vector<T> >::getEdges() {
   std::vector<std::pair<int,int>> edg;
   for (int y = 0; y < numVertices; y++) {
      for (int x = 0; x < numVertices; x++) {
         if (edges[y][x])
            edg.push_back(std::make_pair(y,x));
      }
   }
   return edg;
};

template<typename T>
std::vector<std::pair<int, int> > Graph<T, std::list<T> >::getEdges() {
   std::vector<std::pair<int,int>> edg;
   for (int y = 0; y < numVertices; y++) {
      for (auto it = edges[y].begin(); it != edges[y].end(); it++) {
         edg.push_back(std::make_pair(y,*it));
      }
   }
   return edg;
};

template<typename T>
const size_t&  Graph<T, std::vector<T> >::getSize() const {
   return numVertices;
};

template<typename T>
const size_t&  Graph<T, std::list<T> >::getSize() const {
   return numVertices;
};

template<typename T>
void  Graph<T, std::vector<T> >::addEdge(size_type x, size_type y) {
   if ( x == y ) {
      std::cout << "Graph can't contain hinge\n";
      return;
   }
   if (x < 0 || x >= numVertices || y < 0 || y >= numVertices) {
      std::cout << "Out of Range on Graph Vertices\n";
      return;
   }
   edges[x][y] = 1;
   //edges[y][x] = 1; // Неориентированный граф
};

template<typename T>
void  Graph<T, std::list<T> >::addEdge(size_type x, size_type y) {
   if ( x == y ) {
      std::cout << "Graph can't contain hinge\n";
      return;
   }
   if (x < 0 || x > numVertices || y < 0 || y > numVertices) {
      std::cout << "Out of Range on Graph Vertices\n";
      return;
   }
   edges[x].push_back(y);
   //edges[y].push_back(x); // Неориентированный граф
};

template<typename T>
std::vector<T>  Graph<T, std::vector<T> >::getNeighbours(size_type n) {
   return edges[n];
};

template<typename T>
std::list<T>  Graph<T, std::list<T> >::getNeighbours(size_type n) {
   return edges[n];
};

template<typename T>
bool     Graph<T, std::vector<T> >::checkEdge(size_type x, size_type y) const {
   if ( x == y ) {
      return false;
   }
   if (x < 0 || x > numVertices || y < 0 || y > numVertices) {
      return false;
   }
   return edges[x][y]; 
}

template<typename T>
bool     Graph<T, std::list<T> >::checkEdge(size_type x, size_type y) const {
   if ( x == y ) {
      return false;
   }
   if (x < 0 || x > numVertices || y < 0 || y > numVertices) {
      return false;
   }
   auto lst = edges[x];
   for (auto it : lst) {
      if (it == y)
         return true;
   }
   return false; 
}

template<typename T>
void  Graph<T, std::vector<T> >::depthReq(size_type x, std::vector<int>& isVisited) {
      if (isVisited[x] == 1) {
         return;
      }
      std::cout << x << " ";
      isVisited[x] = 1;
      for (auto y = 0; y < numVertices; y++) {
         if (getNeighbours(x)[y] == 1) {
            depthReq(y, isVisited);
         }
      }
};

template<typename T>
void     Graph<T, std::vector<T> >::DFS() {
      std::vector<int> isVisited(numVertices);
      for (auto i = 0; i < numVertices; i++) {
         depthReq(i, isVisited);
      }
      std::cout << std::endl;
};


template<typename T>
void  Graph<T, std::list<T> >::depthReq(size_type x, std::vector<int>& isVisited) {
      if (isVisited[x] == 1) {
         return;
      }
      std::cout << x << " ";
      isVisited[x] = 1;
      for (auto it : getNeighbours(x)) {
         depthReq(it, isVisited);
      }
};

template<typename T>
void     Graph<T, std::list<T> >::DFS() {
      std::vector<int> isVisited(numVertices);
      for (auto i = 0; i < numVertices; i++) {
         depthReq(i, isVisited);
      }
}; 

template<typename T>
void  Graph<T, std::vector<T> >::wideReq(size_type x, std::queue<int>& q,  std::vector<int>& isVisited) {
   if (q.empty())
      return;
   auto arr = getNeighbours(x); 
   for (auto i = 0; i < numVertices; i++) {
      if (arr[i] == 1 && isVisited[i] == 0) {
         q.push(i);
         isVisited[i] = 1;
      }
   }
   std::cout << q.front() << " ";
   q.pop();
   //std::cout << q.front() << " FRONT\n";
   wideReq(q.front(), q, isVisited);
};

template<typename T>
void     Graph<T, std::vector<T> >::BFS() {
      std::vector<int> isVisited(numVertices);
      std::queue<int>  q;
      for (auto i = 0; i < numVertices; i++) {
         if (isVisited[i] == 0) {
            q.push(i);
        // std::cout << i << " ";
            isVisited[i] = 1;
         }
         wideReq(i, q, isVisited);
      }
      std::cout << "\n-------------------------\n";
}


template<typename T>
void  Graph<T, std::list<T> >::wideReq(size_type x, std::queue<int>& q,  std::vector<int>& isVisited) {
   if (q.empty())
      return;
   auto arr = getNeighbours(x); 
   for (auto it = arr.begin(); it != arr.end(); it++) {
      if (isVisited[*it] == 0) {
         q.push(*it);
         isVisited[*it] = 1;
      }
   }
   std::cout << q.front() << " ";
   q.pop();
   //std::cout << q.front() << " FRONT\n";
   wideReq(q.front(), q, isVisited);
};

template<typename T>
void     Graph<T, std::list<T> >::BFS() {
      std::vector<int> isVisited(numVertices);
      std::queue<int>  q;
      for (auto i = 0; i < numVertices; i++) {
         if (isVisited[i] == 0) {
            q.push(i);
        // std::cout << i << " ";
            isVisited[i] = 1;
         }
         wideReq(i, q, isVisited);
      }
      std::cout << "\n-------------------------\n";

};
