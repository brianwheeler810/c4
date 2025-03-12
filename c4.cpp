#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "Board.h"

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(WIDTH, HEIGHT), "Connect Four");
    Event event;
    int mousePointX;
    float columnPickedByPlayer;
    bool playersTurn = true;
    bool waitingForPlayerPick = true;
    bool gamePaused = false;
    Board* board = new Board;
    RectangleShape* chips = board->getChips();
    char* state = NULL;
    int aiPick = 0;

    Font font;
    bool success = font.loadFromFile("fonts/KOMIKAP_.ttf");

    Text winnerMessage;
    winnerMessage.setFont(font);
    winnerMessage.setCharacterSize(40);
    winnerMessage.setFillColor(Color::Green);

    Text keyMessage;
    keyMessage.setFont(font);
    keyMessage.setCharacterSize(40);
    keyMessage.setFillColor(Color::Green);
    keyMessage.setString("(Q)uit (R)eset");
    keyMessage.setPosition(20.0f, 20.0f);

    FloatRect textRect;

    srand(time(NULL));

    while (window.isOpen()) {

        // input
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::MouseButtonReleased) {
                mousePointX = event.mouseButton.x;
                columnPickedByPlayer = std::ceil(7.0f * mousePointX / WIDTH);
                waitingForPlayerPick = false;
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Q)) {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::R)) {
            board->reset();
            gamePaused = false;
        }

        // update
        while (!waitingForPlayerPick && !gamePaused) {
            if (playersTurn) {
                board->updateBoardWithPick(columnPickedByPlayer, true);
                if (board->checkForWin(true)) {
                    winnerMessage.setString("You Win!");
                    textRect = winnerMessage.getLocalBounds();
                    winnerMessage.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                    winnerMessage.setPosition(WIDTH / 2.0f, HEIGHT / 2.0f);
                    gamePaused = true;
                }
                playersTurn = false;
            }
            else {
                // ai makes pick
                //   a) check to see if ai can win with a move 
                for (int i = 1; i <= MAX_FILE; i++)
                {
                    Board tempBoard(*board);
                    tempBoard.updateBoardWithPick(i, false);
                    if (tempBoard.checkForWin(false)) {
                        aiPick = i;
                        break;
                    }
                }
                //   b) check to see if player needs to be blocked
                if (!aiPick) {
                    for (int i = 1; i <= MAX_FILE; i++)
                    {
                        Board tempBoard(*board);
                        tempBoard.updateBoardWithPick(i, true);
                        if (tempBoard.checkForWin(true)) {
                            aiPick = i;
                            break;
                        }
                    }
                }
                //   c) pick best option <<for now just random>> 
                if (!aiPick) {
                    do
                        aiPick = (rand() % MAX_FILE) + 1;
                    while (!board->isValidPick(aiPick));
                }
                board->updateBoardWithPick(aiPick, false);
                if (board->checkForWin(false)) {
                    winnerMessage.setString("Computer Wins");
                    textRect = winnerMessage.getLocalBounds();
                    winnerMessage.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                    winnerMessage.setPosition(WIDTH / 2.0f, HEIGHT / 2.0f);
                    gamePaused = true;
                }
                playersTurn = true;
                waitingForPlayerPick = true;
                aiPick = 0;
            }
            chips = board->getChips();
        }

        // render
        window.clear();
        for (int i = 0; i < MAX_FILE; i++) {
            for (int j = 0; j < MAX_RANK; j++) {
                int k = (i * MAX_RANK + j);
                window.draw(chips[k]);
            }
        }
        window.draw(board->getBoardSprite());
        if (gamePaused) {
            window.draw(winnerMessage);
            window.draw(keyMessage);
        }
        window.display();
    }


    return 0;
}


