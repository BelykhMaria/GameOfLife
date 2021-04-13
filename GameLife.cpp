#include "GameLife.hpp"
#include <iostream>
#include <algorithm>
#include <random>

GameLife::GameLife(vector<vector<unsigned short>> zeroField, int sizeOfField)
{
	field = zeroField;
	prevField = zeroField;
	this->sizeOfField = sizeOfField;
}

void GameLife::makeField(int N)
{
	//инициализация начального поля

	//создается вектор из 0 размерности 20x20=400
	//на первых N местах ставится 1
	vector<unsigned short> fieldAsVector(400, 0);
	for (int i = 0; i < N; ++i)
		fieldAsVector[i] = 1;

	//затем вектор случайно перемешивается
	random_device rd;
	shuffle(fieldAsVector.begin(), fieldAsVector.end(), rd);

	//из вектора, у которого N единиц расположены на случайных позициях
	//создается матрица 20x20
	for (int i = 0; i < sizeOfField; ++i)
		for (int j = 0; j < sizeOfField; ++j)
		{
			field[i][j] = fieldAsVector.back();
			fieldAsVector.pop_back();
		}
}

void GameLife::printField() const
{
	cout << endl;
	for (int i = 0; i < sizeOfField; ++i)
	{
		for (int j = 0; j < sizeOfField; ++j)
		{
			if (field[i][j] == 1)
				cout << "*";
			else
				cout << "-";
		}
		cout << endl;
	}	
}

void GameLife::updatePrevField()
{
	for (int i = 0; i < sizeOfField; ++i)
	{
		for (int j = 0; j < sizeOfField; ++j)
		{
			prevField[i][j] = field[i][j];
		}
	}
}

void GameLife::updateField()
{
	updatePrevField();
	for (int i = 0; i < sizeOfField; ++i)
	{
		for (int j = 0; j < sizeOfField; ++j)
		{
			unsigned short cellsCount = getCellsCount(i, j);
			//если у мертвой клетки 3 живых соседа она оживает
			//иначе клетка остается мертвой
			if (prevField[i][j] == 0)
			{
				if (cellsCount == 3)
				{
					field[i][j] = 1;
				}
			}
			//если клетка живая и у нее больше трех соседей, то она умирает от "перенаселения"
			//если у нее меньше двух соседей, то она "вымирает"
			else if ((cellsCount < 2) || (cellsCount > 3))
			{
				field[i][j] = 0;
			}
		}
	}
}


unsigned short GameLife::getCell(int x, int y) const
{
	//получение всех соседей
	//если координаты выходят за пределы поля, выдается результат 0,
	//что не влиет на сумму в методе getCellsCount
	if ((x < 0) || (x > sizeOfField - 1) || (y < 0) || (y > sizeOfField - 1))
	{
		return 0;
	}
	return prevField[x][y];
}

unsigned short GameLife::getCellsCount(int x, int y) const
{
	//подсчет числа живых соседей
	return getCell(x - 1, y) + getCell(x - 1, y - 1) + getCell(x, y - 1) + getCell(x + 1, y - 1) +
		getCell(x + 1, y) + getCell(x + 1, y + 1) + getCell(x, y + 1) + getCell(x - 1, y + 1);
}

bool GameLife::isStable() const
{
	//Проверка стабилизации генерации (критерий остановки)
	return prevField == field;
}

bool GameLife::isDead() const
{
	//Проверка того, что генерации вымерла (критерий остановки)
	vector<vector<unsigned short>> zero_field(20, vector <unsigned short>(20, 0));
	return field == zero_field;
}