#include "Board.h"

Board::Board() {
    m_boardTexture.loadFromFile("graphics/board.png");
    m_boardSprite.setTexture(m_boardTexture);
    for (int i = 0; i < 7; i++) {
        m_curPositions[i] = 0;
    }
    for (int i = 0; i < MAX_FILE; i++) {
        for (int j = 0; j < MAX_RANK; j++) {
            m_boardState[i][j] = '_';
        }
    }
}

Board::Board(const Board& other) {
    m_boardTexture = other.m_boardTexture;
    m_boardSprite = other.m_boardSprite;
    for (int i = 0; i < MAX_FILE; i++) {
        m_curPositions[i] = other.m_curPositions[i];
    }
    for (int i = 0; i < MAX_FILE; i++) {
        for (int j = 0; j < MAX_RANK; j++) {
            m_boardState[i][j] = other.m_boardState[i][j];
        }
    }
    for (int i = 0; i < MAX_FILE; i++) {
        for (int j = 0; j < MAX_RANK; j++) {
            m_chips[i][j] = other.m_chips[i][j];
        }
    }
}

void Board::reset() {
    for (int i = 0; i < MAX_FILE; i++) {
        m_curPositions[i] = 0;
    }
    for (int i = 0; i < MAX_FILE; i++) {
        for (int j = 0; j < MAX_RANK; j++) {
            m_boardState[i][j] = '_';
        }
    }
    for (int i = 0; i < MAX_FILE; i++) {
        for (int j = 0; j < MAX_RANK; j++) {
            m_chips[i][j] = RectangleShape();
        }
    }
}

RectangleShape* Board::getChips() {
    return (RectangleShape*)&m_chips;
}

char* Board::getBoardState() {
    return (char*)&m_boardState;
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
        m_boardState[column - 1][m_curPositions[column - 1] - 1] = player ? 'P' : 'A';
    }
}

bool Board::checkForWin(bool isPlayer) {
    char playerChar = isPlayer ? 'P' : 'A';  //P is player  A is AI

    //across
    for (int i = 0; i < 7; i++) {  
        for (int j = 0; j < 3; j++) { 
            if (m_boardState[i][j] == m_boardState[i][j+1] && 
                m_boardState[i][j+1] == m_boardState[i][j+2] && 
                m_boardState[i][j+2] == m_boardState[i][j+3] &&
                m_boardState[i][j+3] == playerChar) {
                return true;
            }
        }
    }
    //up and down
    for (int i = 0; i < 4; i++) {  
        for (int j = 0; j < 6; j++) {
            if (m_boardState[i][j] == m_boardState[i+1][j] && 
                m_boardState[i+1][j] == m_boardState[i+2][j] &&
                m_boardState[i+2][j] == m_boardState[i+3][j] &&
                m_boardState[i+3][j] == playerChar) {
                return true;
            }
        }
    }
    //diagonally
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (m_boardState[i][j] == m_boardState[i+1][j+1]  &&
                m_boardState[i+1][j+1] == m_boardState[i+2][j+2] &&
                m_boardState[i+2][j+2] == m_boardState[i+3][j+3] &&
                m_boardState[i+3][j+3] == playerChar) {
                return true;
            }
        }
    }
    for (int i = 3; i < 7; i++) {
        for (int j = 0; j < 3; j++) {
            if (m_boardState[i][j] == m_boardState[i-1][j+1] && 
                m_boardState[i-1][j+1] == m_boardState[i-2][j+2] &&
                m_boardState[i-2][j+2] == m_boardState[i-3][j+3] &&
                m_boardState[i-3][j+3] == playerChar) {
                return true;
            }
        }
    }

    return false;
}


bool Board::isValidPick(int pick) {
    return m_curPositions[pick - 1] < MAX_RANK ? true : false;
}

Vector2f Board::calculateChipPosition(int file, int rank) {
    float width = WIDTH / 7.0f;
    float height = HEIGHT / 6.0f;
    float x = (file - 1) * width;
    float y = (7.0f - rank - 1) * height;
    return Vector2f(x, y);
}
