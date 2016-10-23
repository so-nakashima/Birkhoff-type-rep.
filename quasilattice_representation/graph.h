#ifndef __GRAPH_HEDDER_INCLUEDED__
#define __GRAPH_HEDDER_INCLUEDED__

//from @tmaehara


#include<vector>

typedef int Weight;
struct Edge {
  int src, dst;
  Weight weight;
  Edge(int src, int dst, Weight weight) :
    src(src), dst(dst), weight(weight) { }
};

typedef std::vector<Edge> Edges;
typedef std::vector<Edges> Graph;

void stronglyConnectedComponents(const Graph& g,
    std::vector< std::vector<int> >& scc);

#endif