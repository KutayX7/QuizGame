#include <iostream>
#include <ctime>
using namespace std;

int main() {
    srand(time(nullptr));

    const int numberofquestions = 4;
    int answers[numberofquestions] = {2, 3, 1, 4};
    int point = 0;

    cout << "Welcome to the game!\n";
    cout << "You have a total of 10 seconds for each question.\n";
    cout << "Be ready!\n";

    for (int i = 0; i < numberofquestions; i++) {
        cout << "Question " << i+1 << ": ";
        
        switch (i) {
            case 0:
                cout << "What is the capital of France?\n";
                cout << "a) Paris\n";
                cout << "b) London\n";
                cout << "c) Rome\n";
                cout << "d) Madrid\n";
                if (cin.get() == 'a') {
                    point++;
                    cout << "The correct answer!\n";
                } else {
                    cout << "Wrong answer. The correct answer is Paris.\n";
                }
                break;
                
            case 1:
                cout << "Which planet is known as the Red Planet?\n";
                cout << "a) Mars\n";
                cout << "b) Jupiter\n";
                cout << "c) Saturn\n";
                cout << "d) Mercury\n";
                if (cin.get() == 'a') {
                    point++;
                    cout << "The correct answer!\n";
                } else {
                    cout << "Wrong answer. The correct answer is Mars.\n";
                }
                break;

            case 2:
                cout << "What is the chemical symbol for water?\n";
                cout << "a) O2\n";
                cout << "b) H2O\n";
                cout << "c) CO2\n";
                cout << "d) N2\n";
                if (cin.get() == 'b') {
                    point++;
                    cout << "The correct answer!\n";
                } else {
                    cout << "Wrong answer. The correct answer is H2O.\n";
                }
                break;
                
            case 3:
                cout << "What is the largest ocean in the world?\n";
                cout << "a) Pacific Ocean\n";
                cout << "b) Atlantic Ocean\n";
                cout << "c) Indian Ocean\n";
                cout << "d) Arctic Ocean\n";
                if (cin.get() == 'a') {
                    point++;
                    cout << "The correct answer!\n";
                } else {
                    cout << "Wrong answer. The correct answer is Pacific Ocean.\n";
                }
                break;
        }
    }

    cout << "Game over. Total points: " << point << "\n";
    return 0;
}
