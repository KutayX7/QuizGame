#include <iostream>
#include <ctime>
using namespace std;
int main() {
    srand(time(nullptr));

    const int numberofquestions = 5;
    int answers[numberofquestions] = {4, 7, 2, 9, 5};
    int point = 0;

    cout << "Welcome to the game!\n";
    cout << "You have a total of 10 seconds for each question.\n";
    cout << "Be ready!\n";

    for (int i = 0; i < numberofquestions; i++) {
        cout << "Question " << i+1 << ": " << "10 * " << i+1 << " = ";
        int answer;
        cin >> answer;

        clock_t starttime = clock();
        while ((clock() - starttime) / (double)CLOCKS_PER_SEC < 10.0) {
            if (answer == answers[i]) {
               cout << "The correct answer!\n";
                point++;
                break;
            }
        }
        if (answer != answers[i]) {
            cout << "Time is up! The correct answer was " << answers[i] << ".\n";
        }
    }

   cout << "Game over. Total points: " << point << "\n";
    return 0;
}
