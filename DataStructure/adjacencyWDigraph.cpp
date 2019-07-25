#include "adjacencyWDigragh.h"
#include <utility>

using namespace std;

void recurPrint(int* p, int src, int dest);
void recurPrint2(int* p, int dest);

void adjacencyWDigraphTest()
{
	adjacencyWDigraph<int> g(10);
	cout << "Number of Vertices = " << g.numberOfVertices() << endl;
	cout << "Number of Edges = " << g.numberOfEdges() << endl;
	cout << endl;

	g.insertEdge(new weightedEdge<int>(2, 4, 1));
	g.insertEdge(new weightedEdge<int>(1, 3, 2));
	g.insertEdge(new weightedEdge<int>(2, 1, 3));
	g.insertEdge(new weightedEdge<int>(1, 4, 4));
	g.insertEdge(new weightedEdge<int>(4, 2, 5));
	cout << "The graph is" << endl;
	cout << "Number of Vertices = " << g.numberOfVertices() << endl;
	cout << "Number of Edges = " << g.numberOfEdges() << endl;
	cout << g << endl;
	cout << endl;

	g.eraseEdge(2, 1);
	cout << "The graph after deleting (2,1) is" << endl;
	cout << "Number of Vertices = " << g.numberOfVertices() << endl;
	cout << "Number of Edges = " << g.numberOfEdges() << endl;
	cout << g << endl;

	cout << "existsEdge(3,1) = " << g.existsEdge(3, 1) << endl;
	cout << "existsEdge(1,3) = " << g.existsEdge(1, 3) << endl;
	cout << "inDegree(3) = " << g.inDegree(3) << endl;
	cout << "outDegree(1) = " << g.outDegree(1) << endl;
	cout << "Number of Vertices = " << g.numberOfVertices() << endl;
	cout << "Number of Edges = " << g.numberOfEdges() << endl;
	cout << endl;

	// test iterator
	cout << "Edges incident to vertex 4" << endl;
	vertexIterator<int>* gi = g.iterator(4);
	int vertex;
	while ((vertex = gi->next()) != 0)
		cout << vertex << " " << endl;

	// test findPath
	g.insertEdge(new weightedEdge<int>(3, 5, 1));
	g.insertEdge(new weightedEdge<int>(5, 4, 1));
	g.insertEdge(new weightedEdge<int>(2, 6, 1));
	cout << "findPath(1, 6):1 ";
	int* path = g.rFindPath(1, 6);
	if (path != nullptr) {
		for (int i = 1; i <= path[0]; ++i)
			cout << path[i] << " ";
		cout << endl;
		delete[] path;
	}
	else
		cout << "there is no path from 1 to 2";

	cout << "FindShortestPath(1, 6):1 ";
	int* shortPath = g.FindShortestPath(1, 6);
	if (shortPath != nullptr) {
		recurPrint(shortPath, 1, 6);
		cout << endl;
		delete[] shortPath;
	}
		
	cout << "findPath(2, 1):";
	path = g.rFindPath(2, 1);
	if (path != nullptr) {
		std::copy(path + 1, path + 1 + path[0], std::ostream_iterator<int>(cout, " "));
		cout << endl;
		delete[] path;
	}
	else
		cout << "there is no path from 2 to 1" << endl;

	// test topological order
	adjacencyWDigraph<int> g2(6);
	int order[6] = { 0 };
	g2.insertEdge(new weightedEdge<int>(1, 3, 1));
	g2.insertEdge(new weightedEdge<int>(1, 4, 1));
	g2.insertEdge(new weightedEdge<int>(3, 4, 1));
	g2.insertEdge(new weightedEdge<int>(3, 6, 1));
	g2.insertEdge(new weightedEdge<int>(2, 4, 1));
	g2.insertEdge(new weightedEdge<int>(2, 5, 1));
	g2.insertEdge(new weightedEdge<int>(4, 6, 1));
	g2.insertEdge(new weightedEdge<int>(5, 6, 1));

	cout << "topologicalOrder:" << g2.topologicalOrder(order) << endl;
	for (int i = 0; i < 6; i++)
		cout << order[i] << " ";
	cout << endl;

	// test shortestPaths
	adjacencyWDigraph<int> g3(6);
	int distFromSource[7] = { 0 };
	int predecessor[7] = { 0 };
	g3.insertEdge(new weightedEdge<int>(1, 2, 10));
	g3.insertEdge(new weightedEdge<int>(2, 3, 15));
	g3.insertEdge(new weightedEdge<int>(2, 4, 2));
	g3.insertEdge(new weightedEdge<int>(4, 3, 1));
	g3.insertEdge(new weightedEdge<int>(3, 6, 5));
	g3.insertEdge(new weightedEdge<int>(1, 5, 15));
	g3.insertEdge(new weightedEdge<int>(5, 6, 10));

	g3.shortestPaths(1, distFromSource, predecessor);

	cout << "shortestPaths From 1 to 6:" << endl;
	recurPrint2(predecessor, 6);
	cout << endl;
}

void recurPrint(int* p, int src, int dest)
{
	if (src == dest) return;
	recurPrint(p, src, p[dest]);
	cout << dest << " ";
}

void recurPrint2(int* p, int dest)
{
	if (0 == dest) return;
	recurPrint2(p, p[dest]);
	cout << dest << " ";
}
