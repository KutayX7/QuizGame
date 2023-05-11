#include <iostream>
#include <ctime>

int main() {
    std::srand(std::time(nullptr));

    const int numberofquestions = 5;
    int answers[numberofquestions] = {4, 7, 2, 9, 5};
    int point = 0;

    std::cout << "Welcome to the game!\n";
    std::cout << "You have a total of 10 seconds for each question.\n";
    std::cout << "Be ready!\n";

    for (int i = 0; i < numberofquestions; i++) {
        std::cout << "Question " << i+1 << ": " << "10 * " << i+1 << " = ";
        int answer;
        std::cin >> answer;

        std::clock_t starttime = std::clock();
        while ((std::clock() - starttime) / (double)CLOCKS_PER_SEC < 10.0) {
            if (answer == answers[i]) {
                std::cout << "The correct answer!\n";
                point++;
                break;
            }
        }
        if (answer != answers[i]) {
            std::cout << "Time is up! The correct answer was " << answers[i] << ".\n";
        }
    }

    std::cout << "Game over. Total points: " << point << "\n";
    return 0;
}
