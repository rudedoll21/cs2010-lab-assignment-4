#ifndef GAME_H
#define GAME_H

void initializeGame();
void displayGrid();
void updateGrid();
int countLiveNeighbors(int row, int col);
void runGame();
void endGame();

#endif
