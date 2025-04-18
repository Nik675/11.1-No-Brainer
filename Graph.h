#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <algorithm>
using namespace std;

template < typename Type >
class Graph;

template < typename Type >
ostream& operator<<( ostream& out , const Graph< Type >& g );

template <typename Type>

class Graph {

private:

    vector< Type > vertices; 
    unordered_map<Type, list< Type > > adjList; 


public:
    Graph( );

    void addVertex( Type vertex ) ;

    void addEdge( Type source, Type target );

    int getVertexPos( Type item );

    int getNumVertices( ) const;

    bool isEdge( Type source, Type target);
	
    friend ostream& operator<< <>(ostream& out, const Graph<Type>& g);
};

template < typename Type >
Graph< Type >::Graph( ) {}

template <typename Type>
void Graph<Type>::addVertex(Type vertex) {

    if ( find(vertices.begin(), vertices.end(), vertex) == vertices.end() ) {
		
        vertices.push_back( vertex );
        adjList[vertex] = list<Type>();

    }
}

template < typename Type > 
void Graph< Type >::addEdge(Type source, Type target) {

    if (adjList.find(source) != adjList.end() && adjList.find(target) != adjList.end()) {
        adjList[source].push_back(target);
    }
}

template < typename Type >

int Graph< Type >::getVertexPos(Type item) {
    auto it = find(vertices.begin( ), vertices.end(), item);

    if ( it != vertices.end( ) ) {
        return distance(vertices.begin(), it);

    }
    return -1;
}

template <typename Type>
int Graph<Type>::getNumVertices() const {
    return vertices.size( );
}

template < typename Type >
bool Graph<Type>::isEdge( Type source, Type target )  {
    if ( adjList.find(source) != adjList.end( ) ) {

        auto& edges = adjList[source];
        return find( edges.begin( ), edges.end( ), target) != edges.end();

    }
    return false;
}

template <typename Type>
ostream& operator<<(ostream& out, const Graph<Type>& g) {

    for (const auto& vertex : g.vertices) {
        out << vertex << ": ";
		
        for (const auto& edge : g.adjList.at(vertex)) {

            out << edge << " ";

        }
        out << endl;
    }

    return out;

}