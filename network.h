#ifndef NETWORK_H
#define NETWORK_H

#include "link.h"
#include "node.h"
#include "set.h"


#include<iostream>
#include<vector>
#include<map>
#include <unordered_map>

using namespace std;

class Network
{
    public:
        vector <Node> m_nodes;
        map<int, int> m_connectionCheckMap;

        Network();
        Node GetNode(int nodeID);
        bool CheckNodeExist(int nodeID);
        void AddNode(Node newNode);
        bool CheckLinkExist(int fromNodeID, int toNodeID);
        void AddLink(int fromNodeID, int toNodeID, int cost);
        void UpdateLink(int fromNodeID, int toNodeID, int cost);
        void DeleteLink(int fromNodeID, int toNodeID);
        void DeleteNode(int nodeID);
        void PrintNeighborNodes(int nodeID);
        void PrintNetwork();
        // end function from youtube

        int GetNetworkSize();
        void PrintSortedNodeIDs(vector<int> nodeIDList);
        void PrintUnsortedNodeIDs(vector<int> nodeIDList);

        void PrintMapWithVector(map<int, vector<int>> mapWithVector);
        void PrintFloatNumberList(vector<float> floatNumberList);

        vector<int> GetOneHopNeighborNodeIDListWithoutSourceNode(int nodeID);
        vector<int> GetWithinTwoHopNeighborNodeIDListWithoutSourceNode(int nodeID);
        vector<int> GetExactlyTwoHopNeighbors(int nodeID);


        vector<int> GetNodeIDOfNetwork();
        void AddNodeIDToConnectionCheckMap(int nodeID);
        void UpdateFlagOfConnectionCheckMap(int nodeID);
        void PrintMap(map<int, int> connectionCheckMap);
        void PrintMapWithFloatValue(map<int, float> connectionCheckMap);
        void DepthFirstSearchInNetwork(int nodeID);
        bool IsNetworkConnected();


    protected:

    private:
};

#endif // NETWORK_H

