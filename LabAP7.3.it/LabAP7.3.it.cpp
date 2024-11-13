#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

void Create(int** matrix, const int size, const int Low, const int High)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] = Low + rand() % (High - Low + 1);
}

void Print(int** matrix, const int size)
{
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
            cout << setw(4) << matrix[i][j];
        cout << endl;
    }
    cout << endl;
}

int SumRowsWithoutNegatives(int** matrix, const int size)
{
    int totalSum = 0;
    for (int i = 0; i < size; i++)
    {
        bool hasNegative = false;
        int rowSum = 0;
        for (int j = 0; j < size; j++)
        {
            if (matrix[i][j] < 0)
            {
                hasNegative = true;
                break;
            }
            rowSum += matrix[i][j];
        }
        if (!hasNegative)
            totalSum += rowSum;
    }
    return totalSum;
}

void MinSumParallelDiagonals(int** matrix, const int size, int& minSum)
{
    bool isFirstDiagonal = true;
    for (int start = 1 - size; start < size; start++)
    {
        int diagSum = 0;
        for (int i = 0; i < size; i++)
        {
            int j = i + start;
            if (j >= 0 && j < size)
                diagSum += matrix[i][j];
        }
        if (isFirstDiagonal)
        {
            minSum = diagSum;
            isFirstDiagonal = false;
        }
        else if (diagSum < minSum)
            minSum = diagSum;
    }
}

int main()
{
    srand((unsigned)time(NULL));

    int size, Low = -10, High = 10;
    cout << "n = ";
    cin >> size;

    int** matrix = new int* [size];
    for (int i = 0; i < size; i++)
        matrix[i] = new int[size];

    Create(matrix, size, Low, High);
    Print(matrix, size);

    int sum = SumRowsWithoutNegatives(matrix, size);
    cout << "SumPositiveRows: " << sum << endl;

    int minDiagonalSum;
    MinSumParallelDiagonals(matrix, size, minDiagonalSum);
    cout << "MinSumParallelDiagonals: " << minDiagonalSum << endl;

    for (int i = 0; i < size; i++)
        delete[] matrix[i];
    delete[] matrix;

    return 0;
} 