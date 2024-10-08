#ifndef NODE_H
#define NODE_H

#include "link.h"

#include<iostream>
#include<vector>

using namespace std;

class Node
{
    public:

        int m_nodeID;
        vector<Link> m_linkList;
        vector<int> m_receivedFromNode;
        vector<int> m_sendToNode;

        Node();
        Node(int nodeID);
        void SetNodeID(int nodeID);
        int GetNodeID();
        vector<Link> GetLinkList();
        void PrintLinkList();

    protected:

    private:
};

#endif // NODE_H

