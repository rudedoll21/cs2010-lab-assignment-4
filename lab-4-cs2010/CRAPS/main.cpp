#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function prototypes
void playGame(int &balance);
int die();
int rollDice();

int main() {
    char ans;
    bool done = false;
    int balance = 100;  // Start with 100 credits

    srand(static_cast<unsigned int>(time(0))); // Seed random number generator

    while (!done) {
        if (balance <= 0) {
            cout << "You have run out of credits! Game over!" << endl;
            break;
        }

        cout << "Your current balance is: " << balance << " credits." << endl;
        playGame(balance);  // Play one round of the game

        cout << "Play again (y/n)? ";
        cin >> ans;
        if (ans == 'n' || ans == 'N') 
            done = true;
        else 
            done = false;
    }

    return 0;
}

// Function to simulate rolling a die
int die() {
    return (rand() % 6) + 1;  // Random number between 1 and 6
}

// Function to simulate rolling two dice
int rollDice() {
    int die1 = die();
    int die2 = die();
    return die1 + die2;
}

// Function to play a single round of Craps
void playGame(int &balance) {
    int wager;
    bool validWager = false;

    // Ask for wager amount
    while (!validWager) {
        cout << "Enter your wager: ";
        cin >> wager;
        if (wager > balance) {
            cout << "You don't have enough credits. Please enter a smaller amount." << endl;
        } else {
            validWager = true;
        }
    }

    int point = 0;
    int sum = rollDice();
    cout << "You rolled: " << sum << endl;

    // Determine the outcome based on the first roll
    if (sum == 7 || sum == 11) {
        cout << "You win!" << endl;
        balance += wager * 2;
    } else if (sum == 2, sum == 3, sum == 12) {
        cout << "Craps! You lose." << endl;
        balance -= wager;
    } else {
        point = sum;
        cout << "Your point is: " << point << endl;

        // Keep rolling until you make the point or roll a 7
        bool keepRolling = true;
        while (keepRolling) {
            sum = rollDice();
            cout << "You rolled: " << sum << endl;

            if (sum == point) {
                cout << "You made your point! You win!" << endl;
                balance += wager * 2;
                keepRolling = false;
            } else if (sum == 7) {
                cout << "You rolled a 7. You lose." << endl;
                balance -= wager;
                keepRolling = false;
            }
        }
    }
}
