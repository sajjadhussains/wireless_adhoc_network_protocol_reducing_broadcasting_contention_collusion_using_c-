#ifndef NETWORKTOPOLOGY_H
#define NETWORKTOPOLOGY_H

#include "node.h"
#include "network.h"
#include "nodeposition.h"



#include<vector>
#include <iostream>
#include <cmath>



using namespace std;

class NetworkTopology
{
    public:
        Node node;
        Network network;

        NetworkTopology();
        vector<NodePosition> NodeDeployment(int networkLength, int networkWidth, int nodeNumber);
        void PrintNodePositionList(vector<NodePosition> nodePositionList);
        int Distance(NodePosition nodePositionA, NodePosition nodePositionB);
        vector<int> OneHopNeighborListFromNetworkTopology(NodePosition nodePosition, vector<NodePosition> nodePositionList, int txRange);
        Network TopologyConfigurationForNode(int nodeID, vector<int> oneHopNeighborList);
        Network TopologyConfigurationForNetwork(int networkLength, int networkWidth, int nodeNumber, int txRange);

    protected:

    private:
};

#endif // NETWORKTOPOLOGY_H

