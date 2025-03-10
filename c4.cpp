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
    Board board;
    RectangleShape* chips = board.getChips();

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

        // update
        while (!waitingForPlayerPick) {
            if (playersTurn) {
                board.updateBoardWithPick(columnPickedByPlayer, true);
                if (board.checkForWin(true)) {
                    std::cout << "Player Wins!\n";
                }
                playersTurn = false;
            }
            else {
                // check for win for player
                // ai makes pick
                //   a) check to see if ai can win with a move
                //   b) check to see if player needs to be blocked
                //   c) pick best option
                board.updateBoardWithPick((rand() % MAX_FILE) + 1, false);
                if (board.checkForWin(false)) {
                    std::cout << "Computer Wins!\n";
                }
                playersTurn = true;
                waitingForPlayerPick = true;
            }
            chips = board.getChips();
        }

        // render
        window.clear();
        for (int i = 0; i < MAX_FILE; i++) {
            for (int j = 0; j < MAX_RANK; j++) {
                int k = (i * MAX_RANK + j);
                window.draw(chips[k]);
            }
        }
        window.draw(board.getBoardSprite());
        window.display();
    }


    return 0;
}


