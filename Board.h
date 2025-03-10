#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

const int WIDTH = 333;
const int HEIGHT = 310;
const int MAX_RANK = 6;
const int MAX_FILE = 7;

class Board
{
	RectangleShape m_chips[MAX_FILE][MAX_RANK];
	Texture m_boardTexture;
	Sprite m_boardSprite;
	int m_curPositions[MAX_FILE];

	Vector2f calculateChipPosition(int rank, int file);

public:
	Board();
	RectangleShape* getChips();
	Sprite getBoardSprite();
	void updateBoardWithPick(int column, bool player);
};

