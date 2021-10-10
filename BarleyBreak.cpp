#include <iostream>
#include <iomanip>
#include <random>

std::default_random_engine engine(time(nullptr));
std::uniform_int_distribution<int> rn(0, 14);

const int space = 32; // in ascii table

bool CheckWin(int arr[4][4])
{
	for (int i = 0; i < 4 * 4 - 1; i++)
	{
		if (arr[0][i]  > arr[0][i + 1])
		{
			return false;
		}
	}
	return true;
}
void PrintBoard(int arr[4][4])
{
	int count = 1;
	std::cout << "\nYour Board:\n";
	std::cout << "|---|---|---|---|\n";
	for (int i = 0; i < 4; i++)
	{
		std::cout << "|";
		for (int j = 0; j < 4; j++)
		{
			if (arr[i][j] == space)
			{
				std::cout << std::setw(2) << char(arr[i][j]) << " |";
				continue;
			}
			std::cout  << std::setw(2) << arr[i][j] << " |";
		}
		std::cout << "\n|---|---|---|---|\n";
	}
}
void FindIndexes(int choice, int& indexIChoice, int& indexJChoice, int& indexISpace, int& indexJSpace, int arr[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (arr[i][j] == choice)
			{
				indexIChoice = i;
				indexJChoice = j;
				continue;
			}
			if (arr[i][j] == space)
			{
				indexISpace = i;
				indexJSpace = j;
			}
		}
	}
}
bool CheckRightChoice(int choice, int& indexIChoice, int& indexJChoice, int& indexISpace, int& indexJSpace, int arr[4][4])
{
	FindIndexes(choice, indexIChoice, indexJChoice, indexISpace, indexJSpace, arr);
	if (indexISpace == indexIChoice + 1 && indexJSpace == indexJChoice)
	{
		return true;
	}
	if (indexISpace == indexIChoice - 1 && indexJSpace == indexJChoice)
	{
		return true;
	}
	if (indexISpace == indexIChoice && indexJSpace == indexJChoice + 1)
	{
		return true;
	}
	if (indexISpace == indexIChoice && indexJSpace == indexJChoice - 1)
	{
		return true;
	}
	return false;
}
void NextTurn(int arr[4][4])
{
	int choice;
	int indexIChoice = -1;
	int indexJChoice = -1;
	int indexISpace = 0;
	int indexJSpace = 0;
	std::cout << "Enter num, you want to move please: "; std::cin >> choice;
	while (!CheckRightChoice(choice, indexIChoice, indexJChoice, indexISpace, indexJSpace, arr))
	{
		std::cout << "You cant, pick another. \n";
		std::cout << "Enter num, you want to move please: "; std::cin >> choice;
	}
	std::swap(arr[indexIChoice][indexJChoice], arr[indexISpace][indexJSpace]);
	if (CheckWin(arr))
	{
		PrintBoard(arr);
		std::cout << "Gratz! You won! \n";
	}
	else
	{
		PrintBoard(arr);
		NextTurn(arr);
	}
}
void NewGame(int arr[4][4])
{
	for (int i = 0; i < 15; arr[0][i] = space, i++);
	for (int i = 0; i < 15; i++)
	{
		int pos = rn(engine);
		while (arr[0][pos] != space)
		{
			pos = rn(engine);
		}
		arr[0][pos] = i + 1;
	}
	arr[3][3] = space;
	PrintBoard(arr);
	NextTurn(arr);
}
int main()
{
	int Board[4][4];
	NewGame(Board);
}