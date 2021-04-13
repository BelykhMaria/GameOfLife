#ifndef _GAMELIFE_HPP_
#define _GAMELIFE_HPP_

#include <vector>
#include <map>

using namespace std;

class GameLife {
public:
	GameLife(vector<vector<unsigned short>>, int);
	void makeField(int);
	void printField() const;
	void updatePrevField();
	void updateField();
	unsigned short getCell(int, int) const;
	unsigned short getCellsCount(int, int) const;
	bool isStable() const;
	bool isDead() const;
private:
	vector<vector<unsigned short>> field;
	vector<vector<unsigned short>> prevField;
	int sizeOfField;
};

#endif _GAMELIFE_HPP_


