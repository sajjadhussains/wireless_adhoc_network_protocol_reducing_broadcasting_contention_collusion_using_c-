#include "network.h"

Network::Network()
{
}



Node Network::GetNode(int nodeID)
{
    Node emptyNode;
    for(int i = 0 ; i < m_nodes.size() ; i++)
    {
        emptyNode = m_nodes.at(i);
        if(emptyNode.GetNodeID() == nodeID)
        {
        return emptyNode;
        }
    }
    return emptyNode;
}

bool Network::CheckNodeExist(int nodeID)
{
    for(int i = 0 ; i < m_nodes.size() ; i++)
    {
        if(m_nodes.at(i).GetNodeID() == nodeID)
        {
            return true;
        }
    }
return false;
}

void Network::AddNode(Node newNode)
{
    bool checkNodeExist = CheckNodeExist(newNode.GetNodeID());
    if(checkNodeExist == true)
    {
        //cout << "Node With This ID Already Exist. " << endl;
    }
    else
    {
        m_nodes.push_back(newNode);
        //cout << "New Node Added Successfully. " << endl;
    }
}



bool Network::CheckLinkExist(int fromNodeID, int toNodeID)
{
    Node node = GetNode(fromNodeID);
    vector<Link> link;
    link = node.GetLinkList();
    for(auto it = link.begin() ; it != link.end() ; it++)
    {
        if(it->GetDestinationNodeID() == toNodeID)
        {
            return true;
            break;
        }
    }
    return false;
}

void Network::AddLink(int fromNodeID, int toNodeID, int cost)
{
    bool checkFromNodeIDExist = CheckNodeExist(fromNodeID);
    bool checkToNodeIDExist = CheckNodeExist(toNodeID);
    if(checkFromNodeIDExist && checkToNodeIDExist == true)
    {
        bool checkLinkExist = CheckLinkExist(fromNodeID, toNodeID);
        if(checkLinkExist == true)
        {
            //cout << "Link Between " << fromNodeID << " and" << toNodeID << " Already Exists. " << endl;
        }
        else
        {
            for(int i = 0 ; i < m_nodes.size() ; i++)
            {
                if(m_nodes.at(i).GetNodeID() == fromNodeID)
                {
                    Link link(toNodeID, cost);
                    m_nodes.at(i).m_linkList.push_back(link);
                }
                else if(m_nodes.at(i).GetNodeID() == toNodeID)
                {
                    Link link(fromNodeID, cost);
                    m_nodes.at(i).m_linkList.push_back(link);
                }
            }
        //cout << "Link Between " << fromNodeID << " and " << toNodeID << " are Added Successfully." << endl;
        }
    }
    else
    {
    //cout << "Invalid Node ID entered." << endl;
    }
}

void Network::UpdateLink(int fromNodeID, int toNodeID, int cost)
{
    bool checkLinkExist = CheckLinkExist(fromNodeID, toNodeID);
    if(checkLinkExist == true)
    {
        for(int i = 0 ; i < m_nodes.size() ; i++)
        {
            if(m_nodes.at(i).GetNodeID() == fromNodeID)
            {
                for(auto it = m_nodes.at(i).m_linkList.begin() ; it != m_nodes.at(i).m_linkList.end() ; it++)
                {
                    if(it->GetDestinationNodeID() == toNodeID)
                    {
                        it->SetCost(cost);
                        break;
                    }
                }
            }
            else if(m_nodes.at(i).GetNodeID() == toNodeID)
            {
                for(auto it = m_nodes.at(i).m_linkList.begin() ; it != m_nodes.at(i).m_linkList.end() ; it++)
                {
                    if(it->GetDestinationNodeID() == fromNodeID)
                    {
                        it->SetCost(cost);
                        break;
                    }
                }
            }
        }
        //cout << "Link Cost Updated Successfully." << endl;
    }
    else
    {
        //cout << "Link Between " << fromNodeID << " and" << toNodeID << " Does Not Exist. " << endl;
    }
}



void Network::DeleteLink(int fromNodeID, int toNodeID)
{
    bool checkLinkExist = CheckLinkExist(fromNodeID, toNodeID);
    if(checkLinkExist == true)
    {
        for(int i = 0 ; i < m_nodes.size() ; i++)
        {
            if(m_nodes.at(i).GetNodeID() == fromNodeID)
            {
                for(auto it = m_nodes.at(i).m_linkList.begin() ; it != m_nodes.at(i).m_linkList.end() ; it++)
                {
                    if(it->GetDestinationNodeID() == toNodeID)
                    {
                        m_nodes.at(i).m_linkList.erase(it);
                        break;
                    }
                }
            }
            else if(m_nodes.at(i).GetNodeID() == toNodeID)
            {
                for(auto it = m_nodes.at(i).m_linkList.begin() ; it != m_nodes.at(i).m_linkList.end() ; it++)
                {
                    if(it -> GetDestinationNodeID() == fromNodeID)
                    {
                        m_nodes.at(i).m_linkList.erase(it);
                        break;
                    }
                }
            }
        }
        //cout << "Link Between" << fromNodeID << " and "<< toNodeID << " Deleted Successfully." << endl;
    }
    else
    {
        //cout << "Link Between " << fromNodeID << " and" << toNodeID << " Does Not Exist. " << endl;
    }
}


void Network::DeleteNode(int nodeID)
{
    int nodeIndex = 0;
    for(int i = 0 ; i < m_nodes.size() ; i++)
    {
        if(m_nodes.at(i).GetNodeID() == nodeID)
        {
            nodeIndex = i;
        }
    }

    for(auto it = m_nodes.at(nodeIndex).m_linkList.begin() ; it != m_nodes.at(nodeIndex).m_linkList.end() ; it++)
    {
        DeleteLink(it->GetDestinationNodeID(), nodeID);
    }
    m_nodes.erase(m_nodes.begin() + nodeIndex);
    //cout << "Node Deleted Successfully." << endl;
}




void Network::PrintNetwork()
{
    cout << "Network has "<< GetNetworkSize() << " nodes" << endl;
    cout << "Network topology represented by adjacency list:" << endl;
    for(int i = 0 ; i < m_nodes.size() ; i++)
    {
        Node emptyNode;
        emptyNode = m_nodes.at(i);
        cout << emptyNode.GetNodeID() << "-->" ;
        emptyNode.PrintLinkList();
    }
}

// End of the code from youtube

// Begin Network Node ID and Name Get and Print





void Network::PrintSortedNodeIDs(vector<int> nodeIDList)
{
    sort(nodeIDList.begin(), nodeIDList.end());
    cout <<"{ ";
    for(int i = 0 ; i < nodeIDList.size() ; i++)
    {
                cout << nodeIDList[i] << " " ;
    }
    cout << "}" << endl;
}

void Network::PrintUnsortedNodeIDs(vector<int> nodeIDList)
{
    cout <<"{ ";
    for(int i = 0 ; i < nodeIDList.size() ; i++)
    {
                cout << nodeIDList[i] << " " ;
    }
    cout << "}" << endl;
}


vector<int> Network::GetNodeIDOfNetwork()
{
    vector<int> nodeIDList;
    for(int i = 0 ; i < m_nodes.size() ; i++)
    {
        Node emptyNode;
        emptyNode = m_nodes.at(i);
        nodeIDList.push_back(emptyNode.GetNodeID());
    }
    return nodeIDList;
}
// End Network Node ID and Name Get and Print


//Begin Neighbor nodes calculation





vector<int> Network::GetOneHopNeighborNodeIDListWithoutSourceNode(int nodeID)
{
    vector<int> nodeIDList;
    for(int i = 0 ; i < m_nodes.size() ; i++)
    {
        if(m_nodes.at(i).GetNodeID() == nodeID)
        {
            for(auto it = m_nodes.at(i).m_linkList.begin() ; it != m_nodes.at(i).m_linkList.end() ; it++)
            {
                nodeIDList.push_back(it->GetDestinationNodeID());
            }
        }
    }
    return nodeIDList;
}

vector<int> Network::GetWithinTwoHopNeighborNodeIDListWithoutSourceNode(int nodeID)
{
    Set emptySet;
    vector<int> oneHopNeighborList;
    vector<int> withinTwoHopNeighborList;
    vector<int> emptyNodeNeighborList;
    vector<int> sourceNodeID;
    sourceNodeID.push_back(nodeID);

    oneHopNeighborList = GetOneHopNeighborNodeIDListWithoutSourceNode(nodeID);
    for( int i = 0 ; i < oneHopNeighborList.size() ; i++)
    {
        emptyNodeNeighborList = GetOneHopNeighborNodeIDListWithoutSourceNode(oneHopNeighborList[i]);
        withinTwoHopNeighborList = emptySet.SetUnion(withinTwoHopNeighborList, emptyNodeNeighborList);
    }
    withinTwoHopNeighborList = emptySet.SetDifference(withinTwoHopNeighborList,sourceNodeID);
    withinTwoHopNeighborList = emptySet.SetUnion(withinTwoHopNeighborList, oneHopNeighborList);
    return withinTwoHopNeighborList;
}

vector<int> Network::GetExactlyTwoHopNeighbors(int nodeID)
{
    Set emptySet;
    vector<int> oneHopNeighborList;
    vector<int> withinTwoHopNeighborList;
    vector<int> exactlyTwoHopNeighborList;
    vector<int> sourceNodeID;
    sourceNodeID.push_back(nodeID);

    oneHopNeighborList = GetOneHopNeighborNodeIDListWithoutSourceNode(nodeID);
    withinTwoHopNeighborList = GetWithinTwoHopNeighborNodeIDListWithoutSourceNode(nodeID);

    exactlyTwoHopNeighborList = emptySet.SetDifference(withinTwoHopNeighborList,oneHopNeighborList);
    exactlyTwoHopNeighborList = emptySet.SetDifference(exactlyTwoHopNeighborList,sourceNodeID);

    return exactlyTwoHopNeighborList;
}

//End Neighbor nodes calculation

// Begin connection check and repair

void Network::AddNodeIDToConnectionCheckMap(int nodeID)
{
    m_connectionCheckMap.insert({ nodeID, 0 });
    //cout << "Node " << nodeID << " is added Successfully into Connection Check Map." << endl;
}



void Network::UpdateFlagOfConnectionCheckMap(int nodeID)
{
    map<int, int>::iterator it;

    it = m_connectionCheckMap.find(nodeID);

          if (it != m_connectionCheckMap.end() == true)
          {
            it->second = 1;
            //cout << "Flag value of Node " << nodeID << " Update Successfully." << endl;
          }
          else
          {
            //cout << "Node" << nodeID << " is not Found." << endl;
          }
}




void Network::PrintMap(map<int, int> connectionCheckMap)
{

    map<int, int>::iterator it;

    cout << endl;
    for( it = connectionCheckMap.begin(); it != connectionCheckMap.end(); ++it)
    {
        cout << "Node " << it->first << " | Flag " << it->second << endl;
    }
    cout << endl;
}

void Network::PrintMapWithFloatValue(map<int, float> connectionCheckMap)
{
    map<int, float>::iterator it;

    cout << endl;
    for( it = connectionCheckMap.begin(); it != connectionCheckMap.end(); ++it)
    {
        cout << "Node " << it->first << " | Flag " << it->second << endl;
    }
    cout << endl;
}

void Network::PrintFloatNumberList(vector<float> floatNumberList)
{
    cout <<"{ ";
    for(int i = 0 ; i < floatNumberList.size() ; i++)
    {
        cout << floatNumberList[i] << " " ;
    }
    cout << "}" << endl;
}

void Network::PrintMapWithVector(map<int, vector<int>> mapWithVector)
{

    map<int, vector<int>>::iterator it;

    cout << endl;
    for( it = mapWithVector.begin(); it != mapWithVector.end(); ++it)
    {
        cout << "Node " << it->first << " | Neighbors: " ;
        PrintUnsortedNodeIDs(it->second);
    }
    cout << endl;
}



void Network::DepthFirstSearchInNetwork(int nodeID)
{
    map<int, int>::iterator it;
    vector<int> oneHopNeighborList;


    UpdateFlagOfConnectionCheckMap(nodeID);

    oneHopNeighborList = GetOneHopNeighborNodeIDListWithoutSourceNode(nodeID);

    //cout << "One-hop Neighbors of Node of " << nodeID << " are : ";

    //PrintUnsortedNodeIDs(oneHopNeighborList);

    for(int i = 0 ; i < oneHopNeighborList.size() ; i++)
    {
        it = m_connectionCheckMap.find(oneHopNeighborList[i]);
        if(it!=m_connectionCheckMap.end() == false )
        {
            AddNodeIDToConnectionCheckMap(oneHopNeighborList[i]);
        }
        else
        {
            //cout << oneHopNeighborList[i] << " Already Exists in Connection Check Map." << endl;
        }
    }

    //cout << "Map After Inserting Neighbors of Node " << nodeID << "."<< endl;

    //PrintMap(m_connectionCheckMap);


    for (it = m_connectionCheckMap.begin(); it != m_connectionCheckMap.end(); it++)
    {
        if(it->second == 0)
        {
            DepthFirstSearchInNetwork(it->first);
        }
    }
}




bool Network::IsNetworkConnected()
{
    map<int, int>::iterator it;
    vector<int> allNodeIDList;
    vector<int> connectedNodeIDList;
    vector<int> disconnectedNodeIDList;

    Set emptySet;


    int nodeIDIndex;
    int nodeID;
    bool checkNetworkConnection;

    allNodeIDList = GetNodeIDOfNetwork();

    //cout << "Nodes of the Network are: ";
    //PrintUnsortedNodeIDs(allNodeIDList);

    //srand(time(0));
    srand(3);
    //srand(0); //default
    nodeIDIndex = rand() % allNodeIDList.size() + 0;
    nodeID = allNodeIDList[nodeIDIndex];
   // nodeID = 5; //DFS is searching from 5 node

    //cout << "Connectivity of the Network check from Node " << nodeID << endl << endl;

    AddNodeIDToConnectionCheckMap(nodeID);
    //cout << "Initial Node and Flag value in Connection Check Map: " << endl;

    //PrintMap(m_connectionCheckMap);


    DepthFirstSearchInNetwork(nodeID);


    for (it = m_connectionCheckMap.begin(); it != m_connectionCheckMap.end(); it++)
    {
            if(it->second == 1)
            {
                connectedNodeIDList.push_back(it->first);
            }
    }

    //cout << "Connected Nodes with Node " << nodeID << " are :" << endl;
    //PrintUnsortedNodeIDs(connectedNodeIDList);

    disconnectedNodeIDList = emptySet.SetDifference(allNodeIDList, connectedNodeIDList);

    if(disconnectedNodeIDList.empty() == true )
    {
        //cout << "No Node is Disconnected from Node " << nodeID << "."<<endl;
    }

    else
    {
        //cout << "Disconnected Nodes with Node " << nodeID << " are :" << endl;
        //PrintUnsortedNodeIDs(disconnectedNodeIDList);
    }


    if(disconnectedNodeIDList.empty() == true)
    {
        checkNetworkConnection = true;
    }
    else
    {
        checkNetworkConnection = false;
    }


    return checkNetworkConnection;

}

// End Connection check and repair


int Network::GetNetworkSize()
{

    return m_nodes.size();

}



