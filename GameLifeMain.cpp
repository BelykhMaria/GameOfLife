#include "GameLife.hpp"
#include <iostream>
#include <vector>

using namespace std;

bool isGood(int N)
{
    return (N >= 0 && N <= 400);
}

int main()
{
    cout << "The game of live!" << endl;
    cout << "\"*\" - living cell, \"-\" - dead cell." << endl;
    cout << "Please, enter number of living cells (integer from 0 to 400): " << endl;

    
    int livingCells = 0;
    cin >> livingCells;

    //пока пользователь не введет подходящее число, программа запращивает новое
    while (!isGood(livingCells))
    {
        cout << "Please, enter appropriate number (integer from 0 to 400): " << endl;
        cin >> livingCells;
    }

    vector<vector<unsigned short>> field(20, vector <unsigned short>(20, 0));
    GameLife game(field, 20);

    game.makeField(livingCells);
    game.printField();

    //первая генерация происходит не в цикле,
    //поскольку prevField и field проиницилизированы одинаково => game.isStable == true
    game.updateField();
    game.printField();

    int counter = 0; //остановка по счетку, если генерации не вымирают, не стабилизируются или не превышают заданное число итераций
    while (!game.isStable() && !game.isDead() && counter < 500)
    {
        game.updateField();
        game.printField();
        counter++;
    }
    
    return 0;
}
