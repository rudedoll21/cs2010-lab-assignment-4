#include <ncurses.h>
#include <vector>
#include <unistd.h> // For usleep()
#include "game.h"

const int WIDTH = 20;
const int HEIGHT = 20;
std::vector<std::vector<bool>> grid(HEIGHT, std::vector<bool>(WIDTH, false));
std::vector<std::vector<bool>> newGrid(HEIGHT, std::vector<bool>(WIDTH, false));

// Initialize ncurses and the game
void initializeGame() {
    initscr();            // Start curses mode
    cbreak();             // Line buffering disabled
    noecho();             // Don't echo while we do getch
    curs_set(0);          // Hide the cursor
    timeout(-1);          // Wait indefinitely for user input

    // Initialize some live cells for testing
    grid[10][10] = true;
    grid[10][11] = true;
    grid[10][12] = true;
}

// Display the current grid
void displayGrid() {
    clear(); // Clear the screen

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (grid[i][j]) {
                mvprintw(i, j, "O"); // Alive cell
            } else {
                mvprintw(i, j, "."); // Dead cell
            }
        }
    }

    refresh(); // Refresh screen to show the changes
}

// Update the grid according to the rules of Game of Life
void updateGrid() {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            int liveNeighbors = countLiveNeighbors(i, j);

            // Apply Game of Life rules
            if (grid[i][j] && (liveNeighbors < 2 || liveNeighbors > 3)) {
                newGrid[i][j] = false; // Underpopulation or Overpopulation
            } else if (!grid[i][j] && liveNeighbors == 3) {
                newGrid[i][j] = true; // Reproduction
            } else {
                newGrid[i][j] = grid[i][j]; // Survival
            }
        }
    }

    // Copy newGrid to grid
    grid = newGrid;
}

// Count live neighbors of a cell
int countLiveNeighbors(int row, int col) {
    int liveNeighbors = 0;

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; // Skip the cell itself
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < HEIGHT && newCol >= 0 && newCol < WIDTH) {
                if (grid[newRow][newCol]) {
                    ++liveNeighbors;
                }
            }
        }
    }

    return liveNeighbors;
}

// Run the game loop
void runGame() {
    bool running = true;

    while (running) {
        displayGrid();
        char ch = getch(); // Wait for keypress
        if (ch == 'q') {
            running = false; // Exit on 'q'
        } else {
            updateGrid(); // Calculate the next generation
            usleep(200000); // Slow down the update for visibility
        }
    }
}

// End the game and clean up ncurses
void endGame() {
    endwin(); // End curses mode
}
