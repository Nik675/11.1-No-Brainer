#pragma once
#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::ostream;
using std::string;

class GameState
{
public:
	GameState() : missionaries(0), cannibals(0), boatIsLeft(false) {}
	GameState(int missionaries, int cannibals, bool boatIsLeft) : missionaries(missionaries), cannibals(cannibals), boatIsLeft(boatIsLeft) {}
	int getMissionariesLeft() const { return missionaries; }
	int getCannibalsLeft() const { return cannibals; }
	bool isValidState() const
	{
		if (missionaries < cannibals && missionaries > 0)
		{
			return false;
		}
		if (3 - missionaries < 3 - cannibals && 3 - missionaries > 0)
		{
			return false;
		}
		if (missionaries < 0 || cannibals < 0 || missionaries > 3 || cannibals > 3)
		{
			return false;
		}
		return true;
	}
	bool isBoatLeft() const
	{
		return boatIsLeft;
	}

	bool operator==(const GameState &other) const
	{
		return other.missionaries == missionaries && other.cannibals == cannibals && other.boatIsLeft == boatIsLeft;
	}
	bool operator!=(const GameState &other) const
	{
		return !(other == *this);
	}

	friend ostream &operator<<(ostream &out, const GameState &state)
	{

		for (int i = 0; i < state.missionaries; i++)
		{
			out << "M";
		}

		for (int i = 0; i < state.cannibals; i++)
		{
			out << "C";
		}

		if (state.boatIsLeft)
		{
			out << " B~~~~~~~ ";
		}
		else
		{
			out << " ~~~~~~~B ";
		}
		for (int i = 0; i < (3 - state.missionaries); i++)
		{
			out << "M";
		}
		for (int i = 0; i < (3 - state.cannibals); i++)
		{
			out << "C";
		}
		return out;
	}

	bool isNeighbor(const GameState &other) const
	{
		if (boatIsLeft == other.boatIsLeft)
		{
			return false;
		}
		int m = abs(missionaries - other.missionaries);
		int c = abs(cannibals - other.cannibals);
		int boat = m + c;
		if (boat > 2)
		{
			return false;
		}

		return true;
	}

private:
	int missionaries;
	int cannibals;
	bool boatIsLeft;
};

namespace std
{
	template <>
	struct hash<GameState>
	{
		size_t operator()(const GameState &state) const
		{
			size_t h1 = hash<int>()(state.getMissionariesLeft());
			size_t h2 = hash<int>()(state.getCannibalsLeft());
			size_t h3 = hash<bool>()(state.isBoatLeft());

			return h1 ^ (h2 << 1) ^ (h3 << 2);
		}
	};
}
