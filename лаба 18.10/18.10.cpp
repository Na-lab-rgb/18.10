#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Pair.h"
using namespace std;

void DeleteSmallerElements(char* fileName, int minFirst, double minSecond)
{
    // �������� ������ �� ������ � ������
    ifstream streamR;
    streamR.open(fileName);
    ofstream streamW;
    streamW.open("temp.txt");

    // ������ ����� �����
    while (!streamR.eof())
    {
        Pair element;
        streamR >> element;
        // �������� �� ��������� ������
        if (element != Pair())
        {
            // �������� ������� �������� ��������
            if (element.GetFirstElement() >= minFirst || element.GetSecondElement() >= minSecond)
            {
                streamW << element;
            }
        }
    }

    // �������� �������
    streamR.close();
    streamW.close();
    // �������� ������� ����� � ��������� ��� �����
    remove(fileName);
    rename("temp.txt", fileName);
}

void IncreaseElement(char* fileName, int valueFirst, double valueSecond, int L)
{
    ifstream streamR;
    streamR.open(fileName);
    ofstream streamW;
    streamW.open("temp.txt");

    while (!streamR.eof())
    {
        Pair element;
        streamR >> element;
        if (element != Pair())
        {
            // �������� �������� �� ������� ��� ����������
            if (element.GetFirstElement() == valueFirst && element.GetSecondElement() == valueSecond)
            {
                element.SetFirst(element.GetFirstElement() + L);
                element.SetSecond(element.GetSecondElement() + L);
            }
            streamW << element;
        }
    }

    streamR.close();
    streamW.close();
    remove(fileName);
    rename("temp.txt", fileName);
}

void AddElements(char* fileName, vector<Pair> newElements, int position)
{
    ifstream streamR;
    streamR.open(fileName);
    ofstream streamW;
    streamW.open("temp.txt");

    int count = 0; // ������� ��������� ���������
    if (0 == position)
    {
        // ���������� ��������� � �������� �����
        for (int i = 0; i < newElements.size(); i++)
        {
            streamW << newElements[i];
        }
    }
    while (!streamR.eof())
    {
        Pair element;
        streamR >> element;
        if (element != Pair())
        {
            streamW << element;
            count++;
            // �������� ������� ��� ��������
            if (count == position)
            {
                // ���������� ��������� � �������� �����
                for (int i = 0; i < newElements.size(); i++)
                {
                    streamW << newElements[i];
                }
            }
        }
    }

    streamR.close();
    streamW.close();
    remove(fileName);
    rename("temp.txt", fileName);
}

vector<Pair> ReadFile(string fileName)
{
    vector<Pair> res; // ������������� ������

    ifstream streamR;
    streamR.open(fileName);

    while (!streamR.eof())
    {
        Pair element;
        streamR >> element;
        if (element != Pair())
        {
            res.push_back(element);
        }
    }

    streamR.close();
    return res;
}

void Print(vector<Pair> collection)
{
    for (int i = 0; i < collection.size(); i++)
    {
        cout << "Pair " << i << endl;
        cout << collection[i];
    }
}

int main()
{
    setlocale(LC_ALL, "rus");

    char vvod = '5';
    while (vvod != '0')
    {
        cout << "========================" << endl;
        cout << "0 - �����" << endl;
        cout << "1 - ������ �����" << endl;
        cout << "2 - ������ � ���������" << endl;
        cout << "3 - ������ � ����������" << endl;
        cout << "4 - ������ � �����������" << endl;
        cin >> vvod;

        char path[] = "input.txt";
        vector<Pair> pairs;

        switch (vvod)
        {
        case '1':
        {
            // ===reading===
            cout << "������ �� ����� ��� ���������" << endl;
            pairs = ReadFile(path);
        }; break;
        case '2':
        {
            // ===deleting===
            cout << "������ �� ����� � ��������� ��������� ������ 3" << endl;
            DeleteSmallerElements(path, 3, 3);
            pairs = ReadFile(path);
        }; break;
        case '3':
        {
            // ===changing===
            int f;
            double s;
            cout << "������� ����, ������� ����� ���������" << endl;
            cin >> f >> s;

            cout << "������ �� ����� � ����������� ��������� �� 2" << endl;
            IncreaseElement(path, f, s, 2);
            pairs = ReadFile(path);
        }; break;
        case '4':
        {
            // ===appending===
            int f1, f2, ind = -1;
            double s1, s2;
            cout << "������� 2 ���� (int, double, int double)" << endl;
            cin >> f1 >> s1 >> f2 >> s2;
            pairs = ReadFile(path);
            while (ind < 0 || ind > pairs.size())
            {
                cout << "������� ������" << endl;
                cin >> ind;
            }

            cout << "������ �� ����� � ����������� 2 ���������" << endl;
            vector<Pair> newElements = { Pair(f1, s1), Pair(f2, s2) };
            AddElements(path, newElements, ind);
            pairs = ReadFile(path);
        }; break;
        }
        Print(pairs);
    }
}