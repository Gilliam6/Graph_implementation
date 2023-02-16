#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>

template < typename T, class Container=std::vector<T> >
class Graph {
   public:
      typedef T         value_type;
      typedef size_t    size_type;
      typedef T&        reference;
      typedef const T&  const_reference;
      typedef Container container_type;

      Graph(size_type size);
      ~Graph();
     // Graph(const Graph& g);
     // Graph&   operator= (const Graph& g);

      std::vector<std::pair<int, int> >   getEdges();
      const size_type&                    getSize()   const;

      void                                addEdge(size_type x, size_type y);
      container_type                      getNeighbours(size_type n);


   private:
      Graph();
      std::vector<container_type>   edges;
      size_type                     numVertices;

};

template < typename T >
class Graph<T, std::vector<T> > {
   public:
      typedef T         value_type;
      typedef size_t    size_type;
      typedef T&        reference;
      typedef const T&  const_reference;
      typedef std::vector<T> container_type;

      Graph(size_type size);
      Graph(const std::vector<std::pair <T, T> >&);
      ~Graph();
     // Graph(const Graph& g);
     // Graph&   operator= (const Graph& g);

      std::vector<std::pair<int, int> >   getEdges();
      const size_type&                    getSize()   const;

      void                                addEdge(size_type x, size_type y);
      bool                                checkEdge(size_type x, size_type y) const;
      container_type                      getNeighbours(size_type n);
      
      void                                depthReq(size_type, std::vector<int>&);
      void                                wideReq(size_type, std::queue<int>&, std::vector<int>&);
      void                                DFS() ;
      void                                BFS() ;


   private:
      Graph();
      std::vector<container_type>   edges;
      size_type                     numVertices;

};

template < typename T >
class Graph<T, std::list<T> > {
   public:
      typedef T         value_type;
      typedef size_t    size_type;
      typedef T&        reference;
      typedef const T&  const_reference;
      typedef std::list<T> container_type;

      Graph(size_type size);
      Graph(const std::vector<std::pair <T, T> >&);
      ~Graph();
      //Graph(const Graph& g);
      //Graph&   operator= (const Graph& g);

      //std::vector<std::list<T> >&  getEdges()  const;
      std::vector<std::pair<int, int> >   getEdges();
      const size_type&                    getSize()   const;

      void                                addEdge(size_type x, size_type y);
      bool                                checkEdge(size_type x, size_type y) const;
      container_type                      getNeighbours(size_type n);

      void                                depthReq(size_type, std::vector<int>&);
      void                                wideReq(size_type, std::queue<int>&, std::vector<int>&);
      void                                DFS() ;
      void                                BFS() ;

   private:
      Graph();
      std::vector<container_type>   edges;
      size_type                     numVertices;

};
