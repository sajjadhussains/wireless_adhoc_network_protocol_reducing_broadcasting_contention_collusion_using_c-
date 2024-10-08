#ifndef SET_H
#define SET_H

#include<iostream>
#include<vector>
#include <bits/stdc++.h>

using namespace std;


class Set
{
    public:
        vector<int> m_setZ;

        Set();
        void DoDispose();
        vector<int> IntegerToVector(int integer);
        vector<int> SetDifference(vector<int> setA, vector<int> setB);
        vector<int> SetDifference(vector<int> setA, vector<int> setB, vector<int> setC);
        vector<int> SetDifference(vector<int> setA, vector<int> setB, vector<int> setC, vector<int> setD);
        vector<int> SetUnion(vector<int> setA, vector<int> setB);
        vector<int> SetIntersection(vector<int> setA, vector<int> setB);
        bool SetIdenticalTest(vector<int> setA, vector<int> setB);
        vector<int> CreateUniqueVector(vector<int> setA);
        void PrintSet(vector<int> setA);


    protected:

    private:
};

#endif // SET_H


