#include "Graph.cpp"
#include <iostream>


void print(const std::vector<std::pair<int, int> >& arr) {
   for (const auto& [y, x] : arr) {
      std::cout << y << " " << x << "\n";
   }
   std::cout << "-----------------------------------------\n";
}

void  print(const std::vector<int>& arr) {
   for (auto c: arr) {
      std::cout << c << " ";
   }
      std::cout << "\n";
      std::cout << "-----------------------------------------\n";
}

void  print(const std::list<int>& arr) {
   for (auto c: arr) {
      std::cout << c << " ";
   }
      std::cout << "\n";
      std::cout << "-----------------------------------------\n";
}

int main() {
   Graph<int, std::vector<int> > g(5);
   g.addEdge(1,4);
   g.addEdge(1,2);
   g.addEdge(2,1);
   print(g.getEdges());
   print(g.getNeighbours(1));
   std::cout << "VECTOR INITIALIZED LIST\n";
   Graph<int, std::vector<int> > g2(std::vector<std::pair<int,int> >({{1,4}, {1,2}, {2,1}, {4, 2},{4,3},{3,0},{0,1},{2,3},{0,3},{0,4}}));

   print(g2.getEdges());
   print(g2.getNeighbours(1));
   std::cout << "VECTOR DFS\n";
   g2.DFS();
   std::cout << "VECTOR BFS\n";
   g2.BFS(); 
   
   std::cout << "LIST INITIALIZED LIST\n";
   Graph<int, std::list<int> > l2(std::vector<std::pair<int,int> >({{1,4}, {1,2}, {2,1}, {4, 2},{4,3},{3,0},{0,1},{2,3},{0,3},{0,4}}));
   print(l2.getEdges());
   print(l2.getNeighbours(1));
   std::cout << "VECTOR DFS\n";
   l2.DFS();
   std::cout << "\nVECTOR BFS\n";
   l2.BFS(); 

   return(0);
};
