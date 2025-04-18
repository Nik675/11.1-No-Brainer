#pragma once

#include "GameState.h"
#include "Graph.h"

class MC
{
public:
	MC();
	MC(GameState);
	void buildGraph(GameState);
	void solve();
	Graph<GameState> getGraph();

private:
	Graph<GameState> graph;
};

MC::MC()
{
	GameState start(3, 3, true);
	graph.addVertex(start);
	buildGraph(start);
}

Graph<GameState> MC::getGraph()
{
	return graph;
}

MC::MC(GameState start)
{
	graph.addVertex(start);
	buildGraph(start);
}

void MC::buildGraph(GameState curr)
{
	if (!curr.isValidState())
	{
		return;
	}
	bool boatSide = !curr.isBoatLeft();

	GameState start(3, 3, true);

	for (int m = 0; m <= 2; m++)
	{
		for (int c = 0; c <= 2; c++)
		{
			if (m + c > 2 || m + c == 0)
				continue;

			int missToMove, cansToMove;
			if (curr.isBoatLeft())
			{
				missToMove = curr.getMissionariesLeft() - m;
				cansToMove = curr.getCannibalsLeft() - c;
			}
			else
			{
				missToMove = curr.getMissionariesLeft() + m;
				cansToMove = curr.getCannibalsLeft() + c;
			}

			GameState state(missToMove, cansToMove, boatSide);

			if (state.isValidState() && graph.getVertexPos(state) < 0)
			{
				graph.addVertex(state);
				graph.addEdge(curr, state);
				graph.addEdge(state, curr);
				buildGraph(state);
			}
		}
	}
}

void MC::solve()
{
	
}
