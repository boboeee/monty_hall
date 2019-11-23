#include <iostream>
#include <vector>
#include <cassert>
#include <ctime>

const int DOORS = 3;
const int SIMULATIONS = 10000;
bool play(int idx, bool simulate, int simulateSwap = 0);
int main(void) {

    srand(time(0));
    
    std::cout << "Welcome To The Monty Hall Simulation!" << std::endl;
    std::cout << "Do you want to play OR simulate?" << std::endl;
    std::string input;
    std::cin >> input;
    if (input.compare("play") == 0) {
        std::cout << "You have 3 Doors, which two doors contain a goat, and one door contains a CAR!" << std::endl;
        std::cout << "Choose a door: ";
        int idx;
        std::cin >> idx; 
        bool won = play(idx, false);
        std::cout << (won ? "You won!!!" : "You lost") << std::endl;
    } else if (input.compare("simulate") == 0) {
        int winCount = 0;
        std::cout << "Do you want a simulation for swapping doors?" << std::endl;
        std::string s;
        std::cin >> s;
        int swap = s.compare("yes") == 0 ? 1 : 0;
        for (int i = 0; i < SIMULATIONS; i++) {
            if (play(rand() % 3, true, swap)) winCount++;
        }
        printf("%.2lf%%\n", (double)winCount/SIMULATIONS * 100);
    }
    
    return 0;
}

int findOtherGoat(std::vector<bool> montyArray, int idx) {
    montyArray[idx] = true;
    for (int i = 0; i < montyArray.size(); i++) {
        if (montyArray.at(i) == false) {
            return i;
        }
    }
    return -1;
}

bool play(int idx, bool simulate, int simulateSwap) {
    std::vector<bool> montyArray(3, false);
    int car = rand() % DOORS;
    montyArray.at(car) = true;
    //Check if PLAYER has opened a goat or car
    int goat;
    if (car == idx) {
        goat = (car + 1) % DOORS;
    } else {
        goat = findOtherGoat(montyArray, idx);
        assert(goat != -1);
    }

    int swap;
    if (!simulate) {
        std::cout << "Door " << goat << " has a goat. Do you want switch to the 3rd door or stay? (yes/no)" << std::endl;
        std::string s;
        std::cin >> s;
        if (s.compare("yes") == 0) {
            swap = 1;
        } else if (s.compare("no") == 0) {
            swap = 0;
        }
    } else {
        swap = simulateSwap;
    }
    return swap ? car != idx : car == idx;
}