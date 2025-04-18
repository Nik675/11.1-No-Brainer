#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <algorithm>
#include <queue>
#include <string>

using namespace std;

template <typename Type>
class Graph;

template <typename Type>
ostream &operator<<(ostream &out, const Graph<Type> &g);

template <typename Type>
class Graph
{
private:
    vector<Type> vertices;
    unordered_map<Type, list<Type> > adjList;

public:
    Graph() {}
    ~Graph() {}

    void addVertex(const Type &item)
    {
        if (find(vertices.begin(), vertices.end(), item) == vertices.end())
        {
            vertices.push_back(item);
            adjList[item] = list<Type>();
        }
    }

    void addEdge(const Type &source, const Type &dest)
    {
        addVertex(source);
        addVertex(dest);
        list<Type> &edges = adjList[source];
        if (find(edges.begin(), edges.end(), dest) == edges.end())
        {
            edges.push_back(dest);
        }
    }

    int getVertexPos(const Type &item) const
    {
        typename vector<Type>::const_iterator it = find(vertices.begin(), vertices.end(), item);
        if (it != vertices.end())
        {
            return distance(vertices.begin(), it);
        }
        return -1;
    }

    int getNumVertices() const
    {
        return vertices.size();
    }

    bool isEdge(const Type &source, const Type &dest) const
    {
        if (!hasVertex(source) || !hasVertex(dest))
        {
            return false;
        }
        const list<Type> &edges = adjList.at(source);
        return find(edges.begin(), edges.end(), dest) != edges.end();
    }

    bool hasVertex(const Type &item) const
    {
        return find(vertices.begin(), vertices.end(), item) != vertices.end();
    }

    vector<Type> getPath(const Type &source, const Type &dest) const
    {
        vector<Type> path;
        if (!hasVertex(source) || !hasVertex(dest))
        {
            return path;
        }

        unordered_map<Type, Type> parent;
        queue<Type> q;
        q.push(source);

        while (!q.empty())
        {
            Type current = q.front();
            q.pop();

            if (current == dest)
            {
                Type curr = dest;
                while (curr != source)
                {
                    path.push_back(curr);
                    curr = parent[curr];
                }
                path.push_back(source);
                reverse(path.begin(), path.end());
                return path;
            }

            typename list<Type>::const_iterator it;
            for (it = adjList.at(current).begin(); it != adjList.at(current).end(); ++it)
            {
                if (parent.find(*it) == parent.end())
                {
                    parent[*it] = current;
                    q.push(*it);
                }
            }
        }

        return path;
    }

    void removeVertex(const Type &item)
    {
        typename vector<Type>::iterator it = find(vertices.begin(), vertices.end(), item);
        if (it != vertices.end())
        {
            vertices.erase(it);
            adjList.erase(item);
            for (typename unordered_map<Type, list<Type> >::iterator mapIt = adjList.begin(); 
                 mapIt != adjList.end(); ++mapIt)
            {
                typename list<Type>::iterator listIt = find(mapIt->second.begin(), mapIt->second.end(), item);
                if (listIt != mapIt->second.end())
                {
                    mapIt->second.erase(listIt);
                }
            }
        }
    }

    void removeEdge(const Type &source, const Type &dest)
    {
        if (isEdge(source, dest))
        {
            typename list<Type>::iterator it = find(adjList[source].begin(), adjList[source].end(), dest);
            if (it != adjList[source].end())
            {
                adjList[source].erase(it);
            }
        }
    }

    friend ostream &operator<<(ostream &out, const Graph<Type> &g)
    {
        for (typename vector<Type>::const_iterator vertexIt = g.vertices.begin(); 
             vertexIt != g.vertices.end(); ++vertexIt)
        {
            out << *vertexIt << ": ";
            typename list<Type>::const_iterator edgeIt;
            for (edgeIt = g.adjList.at(*vertexIt).begin(); 
                 edgeIt != g.adjList.at(*vertexIt).end(); ++edgeIt)
            {
                out << *edgeIt << " ";
            }
            out << endl;
        }
        return out;
    }
};

#endif