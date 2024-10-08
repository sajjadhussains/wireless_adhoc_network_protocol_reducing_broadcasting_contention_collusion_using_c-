#include "node.h"

Node::Node()
{
    m_nodeID = 0;
}



Node::Node(int nodeID)
{
    m_nodeID = nodeID;
}

void Node::SetNodeID(int nodeID)
{
    m_nodeID = nodeID;
}


int Node::GetNodeID()
{
    return m_nodeID;
}

vector<Link> Node::GetLinkList()
{
return m_linkList;
}

void Node::PrintLinkList()
{
    cout << "[ ";
    for(auto it = m_linkList.begin() ; it != m_linkList.end() ; it++)
    {
        cout << it->GetDestinationNodeID() << "(" << it->GetCost() << ") ";
    }
    cout << "]";
    cout << endl;
}

