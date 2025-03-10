#include "Board.h"

Board::Board() {
    m_boardTexture.loadFromFile("graphics/board.png");
    m_boardSprite.setTexture(m_boardTexture);
    for (int i = 0; i < 7; i++) {
        m_curPositions[i] = 0;
    }
}

RectangleShape* Board::getChips() {
    return (RectangleShape*)&m_chips;
}

Sprite Board::getBoardSprite() {
    return m_boardSprite;
}

void Board::updateBoardWithPick(int column, bool player) {
    if (m_curPositions[column-1] < 6) {
        m_curPositions[column-1]++;
        int rank = m_curPositions[column - 1] - 1;
        m_chips[column-1][rank].setSize(Vector2f(WIDTH / MAX_FILE, HEIGHT / MAX_RANK));
        m_chips[column-1][rank].setFillColor(player ? Color::Red : Color::Yellow);
        m_chips[column-1][rank].setPosition(calculateChipPosition(column, m_curPositions[column-1]));
    }
}

Vector2f Board::calculateChipPosition(int file, int rank) {
    float width = WIDTH / 7.0f;
    float height = HEIGHT / 6.0f;
    float x = (file - 1) * width;
    float y = (7.0f - rank - 1) * height;
    return Vector2f(x, y);

}
