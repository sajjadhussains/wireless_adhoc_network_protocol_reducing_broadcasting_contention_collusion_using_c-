#include "nodeposition.h"

NodePosition::NodePosition()
{

}


void NodePosition::SetXCoordinate(int x)
{
m_x = x;
}

void NodePosition::SetYCoordinate(int y)
{
m_y = y;
}

int NodePosition::GetXCoordinate()
{
return m_x;
}

int NodePosition::GetYCoordinate()
{
return m_y;
}

void NodePosition::PrintNodePosition()
{
cout << "(" << m_x << " , " << m_y << ")" << endl;
}
