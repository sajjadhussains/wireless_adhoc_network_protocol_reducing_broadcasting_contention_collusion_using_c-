#ifndef NODEPOSITION_H
#define NODEPOSITION_H

#include<iostream>

using namespace std;
class NodePosition
{
    public:
        int m_x;
        int m_y;
        NodePosition();
        void SetXCoordinate(int x);
        void SetYCoordinate(int y);
        int GetXCoordinate();
        int GetYCoordinate();
        void PrintNodePosition();

    protected:

    private:
};

#endif // NODEPOSITION_H

