#include "networktopology.h"

NetworkTopology::NetworkTopology()
{

}


vector<NodePosition> NetworkTopology::NodeDeployment(int networkLength, int networkWidth, int nodeNumber)
{
    vector<NodePosition> nodePositionList;
    NodePosition nodePosition;
    srand(3);

    //nodePosition.SetXCoordinate(networkLength / 2);
    //nodePosition.SetYCoordinate(networkWidth / 2);
    nodePosition.SetXCoordinate(0);
    nodePosition.SetYCoordinate(0);
    nodePositionList.push_back(nodePosition);

    for(int i = 0 ; i < nodeNumber -1 ; i++)
    {
        int x = rand() % networkLength + 0;
        int y = rand() % networkWidth + 0;

        nodePosition.SetXCoordinate(x);
        nodePosition.SetYCoordinate(y);
        nodePositionList.push_back(nodePosition);
    }
return nodePositionList;
}



void NetworkTopology::PrintNodePositionList(vector<NodePosition> nodePositionList)
{
    for(int i = 0 ; i < nodePositionList.size() ; i++)
    {
        nodePositionList[i].PrintNodePosition();
    }
}

int NetworkTopology::Distance(NodePosition nodePositionA, NodePosition nodePositionB)
{
    int x1 = nodePositionA.GetXCoordinate();
    int y1 = nodePositionA.GetYCoordinate();
    int x2 = nodePositionB.GetXCoordinate();
    int y2 = nodePositionB.GetYCoordinate();
    int distance = floor(sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2)));
   // cout << "Distance " << distance << endl;
    return distance;
}

/*
vector<int> DistanceList(NodePosition pA, vector<NodePosition> NodePositionList)
{
    vector<int> distanceList;
    for(int i = 0 ; i < NodePositionList.size() ; i++)
    {
        int distance = Distance(pA, NodePositionList[i])
        distanceList.push_back(distance);
    }
    return distanceList;
}
*/



vector<int> NetworkTopology::OneHopNeighborListFromNetworkTopology(NodePosition nodePosition, vector<NodePosition> nodePositionList, int txRange)
{
    vector<int> oneHopNeighborList;
    for(int i = 0 ; i < nodePositionList.size() ; i++)
    {
        int distance = Distance(nodePosition, nodePositionList[i]);
        if(0 < distance && distance <= txRange)
        {
            oneHopNeighborList.push_back(i+1);  // index start from 0 and node id start from 1
        }
    }
    return oneHopNeighborList;
}



Network NetworkTopology::TopologyConfigurationForNode(int nodeID, vector<int> oneHopNeighborList)
{
    int cost = 1;

    for( int i = 0 ; i < oneHopNeighborList.size() ; i++)
    {
        network.AddLink(nodeID, oneHopNeighborList[i], cost);
    }
    //cout << "Link Successfully Connected and the topology of " << nodeID << " is:" ;
    //network.PrintNetwork();
    return network;
}


Network NetworkTopology::TopologyConfigurationForNetwork(int networkLength, int networkWidth, int nodeNumber, int txRange)
{
    int nodeID;

    vector<NodePosition> nodePositionList;
    nodePositionList = NodeDeployment(networkLength, networkWidth, nodeNumber);

    for(int i = 0 ; i < nodePositionList.size(); i++)
    {
        nodeID = i+1;
        node.SetNodeID(nodeID);
        network.AddNode(node);
    }

    vector<int> oneHopNeighborList;
    for(int i = 0 ; i < nodePositionList.size() ; i++)
    {
      oneHopNeighborList = OneHopNeighborListFromNetworkTopology(nodePositionList[i], nodePositionList, txRange);
      //network.PrintSortedNodeIDs(oneHopNeighborList);
      nodeID = i+1;
      network = TopologyConfigurationForNode(nodeID, oneHopNeighborList);
    }
    return network;
}



