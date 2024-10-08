#include "link.h"

Link::Link()
{

}


Link::Link(int destinationNodeID, int cost)
{
    m_destinationNodeID = destinationNodeID;
    m_cost = cost;
}

void Link::SetLinkCost(int destinationNodeID, int cost)
{
    m_destinationNodeID = destinationNodeID;
    m_cost = cost;
}

void Link::SetCost(int cost)
{
    m_cost = cost;
}

int Link::GetDestinationNodeID()
{
    return m_destinationNodeID;
}

int Link::GetCost()
{
    return m_cost;
}

