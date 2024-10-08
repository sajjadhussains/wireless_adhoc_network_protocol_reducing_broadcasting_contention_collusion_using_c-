#include "otdp.h"

OTDP::OTDP()
{
    // Original Total Dominant Pruning
}

void OTDP::DoDispose()
{
    m_nodeTransmitterStatus.clear();
    m_nodeReceiverStatus.clear();
    m_nodePriorities.clear();
    m_nodeStatus.clear();
}

vector<int> OTDP::RunOTDP(int sourceNodeID, Network network)
{
    map<int, vector<int>> forwardListOfNodes;
    vector<int> forwardList;
    vector<int> forwardListOfOTDP;
    vector<int> sourceList;
    map<int, vector<int>>::iterator it, it1;
    map<int, int>::iterator itr, it2;

// Inserting nodes into m_nodeReceiverStatus

    m_nodeReceiverStatus.insert({sourceNodeID, messageReceivedSuccessfully});
    vector<int> nodeIDList = network.GetNodeIDOfNetwork();
    nodeIDList = emptySet.SetDifference(nodeIDList, emptySet.IntegerToVector(sourceNodeID));

    for(int i = 0 ; i < nodeIDList.size() ; i++)
    {
        m_nodeReceiverStatus.insert({nodeIDList[i], messageNotReceived});
    }

    cout << "Initial m_nodeReceiverStatus";
    network.PrintMap(m_nodeReceiverStatus);

// Message broadcast from source node

    cout << "Node " << sourceNodeID << " is the source node of the network that generates the broadcast message " << endl;

// Source node is added into source list
    sourceList.push_back(sourceNodeID);

// Source node is added m_nodeTransmitterStatus
    cout << "Node " << sourceNodeID << " is inserted to m_nodeTransmitterStatus" << endl;
    m_nodeTransmitterStatus.insert({sourceNodeID, messageReceivedFlag});
    cout << "m_nodeTransmitterStatus";
    network.PrintMap(m_nodeTransmitterStatus);

// Set priority of source node
    cout << "Node " << sourceNodeID << " is inserted to m_nodePriorities with flag "<< priorityFlagOfSourceNode << endl;
    m_nodePriorities.insert({sourceNodeID, priorityFlagOfSourceNode});
    cout << "m_nodePriorities";
    network.PrintMap(m_nodePriorities);

// Source node broadcast the message
    forwardList = RunOTDPForSourceNode(sourceNodeID, network);

// Set priority and serialized forward list

    SetPriority(forwardList, network);
    cout << "m_nodePriorities";
    network.PrintMap(m_nodePriorities);

    vector<int> prioritizedForwardList = GetPrioritizedForwardList(forwardList);
    cout <<"prioritizedForwardList ";
    network.PrintUnsortedNodeIDs(prioritizedForwardList);

// Store forwarding list of each forward node to forwardListOfNodes
    cout << "Forward list of node " << sourceNodeID << " is added to forwardListOfNodes" << endl;
    forwardListOfNodes.insert({sourceNodeID, prioritizedForwardList});
    cout << "forwardListOfNodes";
    network.PrintMapWithVector(forwardListOfNodes);

    cout <<"m_nodeTransmitterStatus";
    network.PrintMap(m_nodeTransmitterStatus);

    while(CheckForwardNodeStatus() == true)
    {
        rebroadcastFlag = GetMaximumFlag(m_nodeTransmitterStatus);

        vector<int> tempSourceList;
        vector<int> forwardListOfSource;
        tempSourceList = sourceList;
        sourceList.clear();

    vector<int> u;
    vector<int> v;
    int priority = 1;
    int maximumFlag = GetMaximumFlag(m_nodePriorities);

    while(maximumFlag != 0)
    {
        for(int i = 0; i < tempSourceList.size(); i++)
        {
            it = forwardListOfNodes.find(tempSourceList[i]);
            if(it != forwardListOfNodes.end() == true)
            {
                forwardListOfSource = it->second;
                for(int j = 0 ; j < forwardListOfSource.size(); j++)
                {
                    it2 = m_nodePriorities.find(forwardListOfSource[j]);
                    if(it2 != m_nodePriorities.end() == true)
                    {
                        if(it2->second == priority)
                        {
                            u.push_back(tempSourceList[i]);
                            v.push_back(it2->first);
                        }
                    }

                }
            }
        }
    priority = priority + 1;
    maximumFlag  = maximumFlag - 1;
    }

    cout << "Element of u ";
    network.PrintUnsortedNodeIDs(u);
    cout << "Element of v ";
    network.PrintUnsortedNodeIDs(v);

    for(int i = 0; i < v.size(); i++)
    {
        itr = m_nodeTransmitterStatus.find(v[i]);
        if(itr != m_nodeTransmitterStatus.end() == true)
        {
            if(itr->second == messageReceivedFlag)
            {
                it1 = forwardListOfNodes.find(v[i]);
                if(it1 != forwardListOfNodes.end() == true )
                {
                    cout << "Node "<< v[i] << " already created forward list and rebroadcast the message" << endl;
                }
                else
                {
                    sourceList.push_back(v[i]);

                    forwardList = RunOTDPForSourceDestinationNode(u[i], v[i], network);

                    SetPriority(forwardList, network);
                    cout << "m_nodePriorities";
                    network.PrintMap(m_nodePriorities);

                    vector<int> prioritizedForwardList = GetPrioritizedForwardList(forwardList);
                    cout <<"prioritizedForwardList ";
                    network.PrintUnsortedNodeIDs(prioritizedForwardList);

                    cout << "Forward list of node " << v[i] << " is added to forwardListOfNodes" << endl;
                    forwardListOfNodes.insert({v[i], prioritizedForwardList});

                    cout << "forwardListOfNodes";
                    network.PrintMapWithVector(forwardListOfNodes);

                    cout << "m_nodeTransmitterStatus";
                    network.PrintMap(m_nodeTransmitterStatus);

                }

            }
            else
            {
                cout << "Node " << v[i] << " already received the message and does not rebroadcast the message" << endl;
            }

        }

    }

        cout << "m_nodeTransmitterStatus after complete a rebroadcast cycle";
        network.PrintMap(m_nodeTransmitterStatus);
        cout << "forwardListOfNodes after complete a rebroadcast cycle";
        network.PrintMapWithVector(forwardListOfNodes);
    }
    cout << "Final m_nodeTransmitterStatus";
    network.PrintMap(m_nodeTransmitterStatus);

    cout << "Final forwardListOfNodes";
    network.PrintMapWithVector(forwardListOfNodes);

// Extracting Forward List
    for( itr = m_nodeTransmitterStatus.begin(); itr != m_nodeTransmitterStatus.end(); itr++)
    {
        if(itr->second >= broadcastFlag)
        forwardListOfOTDP.push_back(itr->first);
    }

// Updating receiver status
    UpdateReceiverStatus(sourceNodeID, forwardListOfOTDP, network);
    cout << "Final m_nodeReceiverStatus";
    network.PrintMap(m_nodeReceiverStatus);

////Calculation of number of contention
//    float numberOfContention = GetNumberOfContention(network);
//    cout << "Number of contention is " << numberOfContention << endl;
//
////Calculation of number of collision
//    float numberOfCollision = GetNumberOfCollision(network);
//    cout << "Number of collision is " << numberOfCollision << endl;

    return forwardListOfOTDP;
}

float OTDP::GetNumberOfContention(Network network)
{
    map<int, int>::iterator it;
    int maximumFlag = GetMaximumFlag(m_nodeTransmitterStatus);
    float numberOfContention = 0;

    for(int i = broadcastFlag + 1 ; i <= maximumFlag ; i++)
    {
        vector<int> nodeIDListWithCommonTransmitterStatus;
        for(it = m_nodeTransmitterStatus.begin(); it != m_nodeTransmitterStatus.end(); ++it)
        {
            if(it->second == i)
            {
                nodeIDListWithCommonTransmitterStatus.push_back(it->first);
            }
        }
        cout << "Nodes with broadcast status flag " << i << " are" << endl;
        network.PrintUnsortedNodeIDs(nodeIDListWithCommonTransmitterStatus);
        vector<int> tempNodeIDListWithCommonTransmitterStatus = nodeIDListWithCommonTransmitterStatus;

        if(nodeIDListWithCommonTransmitterStatus.size() > 1)
        {
            bool areNodesNeighbor = false;
            for(int j = 0 ; j < nodeIDListWithCommonTransmitterStatus.size() ; j++)
            {
                for(int k = 0 ; k < tempNodeIDListWithCommonTransmitterStatus.size() ; k++)
                {
                    if(j != k)
                    {
                        areNodesNeighbor = AreNodesNeighbor(nodeIDListWithCommonTransmitterStatus[j], tempNodeIDListWithCommonTransmitterStatus[k], network);
                        if(areNodesNeighbor == true)
                        {
                            cout << "Nodes " << nodeIDListWithCommonTransmitterStatus[j] << " and " << tempNodeIDListWithCommonTransmitterStatus[k] << " are neighbor" << endl;
                            numberOfContention = numberOfContention + 1;
                        }
                        else
                        {
                            cout << "Nodes " << nodeIDListWithCommonTransmitterStatus[j] << " and " << tempNodeIDListWithCommonTransmitterStatus[k] << " are not neighbor" << endl;
                        }

                    }

                }
            }

        }
        else
        {
            cout << "Node with " << i << " flag has no contending neighbor" << endl;
        }
    }
    numberOfContention = numberOfContention / 2;
    return numberOfContention;
}

float OTDP::GetNumberOfCollision(Network network)
{
    map<int, int>::iterator it;
    int maximumFlag = GetMaximumFlag(m_nodeTransmitterStatus);
    vector<int> commonNeighborIDList;
    float numberOfCollision = 0;
    vector<int> oneHopNeighborNodeIDList;
    vector<int> nodeIDList;

    for(it = m_nodeTransmitterStatus.begin(); it != m_nodeTransmitterStatus.end(); ++it)
    {
        if(it->second == broadcastFlag)
        {
            cout << "Node " << it->first << " is the source node of the network" << endl;
            cout << "Node " << it->first << " is inserted to m_nodeStatus" << endl;
            m_nodeStatus.insert({it->first, nodeConsiderationFlag});
            cout << "m_nodeStatus";
            network.PrintMap(m_nodeStatus);
            oneHopNeighborNodeIDList = network.GetOneHopNeighborNodeIDListWithoutSourceNode(it->first);
        }
    }

    for(int i = 0 ; i < oneHopNeighborNodeIDList.size() ; i++)
    {
        cout << "Node " << oneHopNeighborNodeIDList[i] << " is inserted to m_nodeStatus" << endl;
        m_nodeStatus.insert({oneHopNeighborNodeIDList[i], nodeConsiderationFlag});
    }
    cout << "m_nodeStatus";
    network.PrintMap(m_nodeStatus);
    nodeIDList.clear();
    oneHopNeighborNodeIDList.clear();



    for(int i = broadcastFlag + 1 ; i <= maximumFlag ; i++)
    {
        vector<int> nodeIDListWithCommonTransmitterStatus;
        for(it = m_nodeTransmitterStatus.begin(); it != m_nodeTransmitterStatus.end(); ++it)
        {
            if(it->second == i)
            {
                nodeIDListWithCommonTransmitterStatus.push_back(it->first);
            }
        }
        cout << "Nodes with broadcast status flag " << i << " are" << endl;
        network.PrintUnsortedNodeIDs(nodeIDListWithCommonTransmitterStatus);
        vector<int> tempNodeIDListWithCommonTransmitterStatus = nodeIDListWithCommonTransmitterStatus;

        if(nodeIDListWithCommonTransmitterStatus.size() > 1)
        {
            bool areNodesNeighbor = false;
            bool hasCommonNeighbors = true;
            for(int j = 0 ; j < nodeIDListWithCommonTransmitterStatus.size() ; j++)
            {
                for(int k = 0 ; k < tempNodeIDListWithCommonTransmitterStatus.size() ; k++)
                {
                    if(j != k)
                    {
                        areNodesNeighbor = AreNodesNeighbor(nodeIDListWithCommonTransmitterStatus[j], tempNodeIDListWithCommonTransmitterStatus[k], network);
                        if(areNodesNeighbor == true)
                        {
                            cout << "Nodes " << nodeIDListWithCommonTransmitterStatus[j] << " and " << tempNodeIDListWithCommonTransmitterStatus[k] << " are neighbor" << endl;
                        }
                        else
                        {
                            cout << "Nodes " << nodeIDListWithCommonTransmitterStatus[j] << " and " << tempNodeIDListWithCommonTransmitterStatus[k] << " are not neighbor" << endl;
                            hasCommonNeighbors = HasCommonNeighbors(nodeIDListWithCommonTransmitterStatus[j], tempNodeIDListWithCommonTransmitterStatus[k], network);
                            if(hasCommonNeighbors == false)
                            {
                                cout << "Nodes " << nodeIDListWithCommonTransmitterStatus[j] << " and " << tempNodeIDListWithCommonTransmitterStatus[k] << " have no common neighbor" << endl;
                            }
                            else
                            {
                                cout << "Nodes " << nodeIDListWithCommonTransmitterStatus[j] << " and " << tempNodeIDListWithCommonTransmitterStatus[k] << " have common neighbor" << endl;
                                vector<int> commonNeighbor = GetCommonNeighbors(nodeIDListWithCommonTransmitterStatus[j], tempNodeIDListWithCommonTransmitterStatus[k], network);
                                cout << "Common neighbors are" << endl;
                                network.PrintUnsortedNodeIDs(commonNeighbor);


                                for(int l = 0 ; l < commonNeighbor.size() ; l++)
                                {
                                        it = m_nodeStatus.find(commonNeighbor[l]);
                                        if(it != m_nodeStatus.end() == true)
                                        {
                                            cout << "Node " << commonNeighbor[l] << " already is in m_nodeStatus" << endl;
                                        }
                                        else
                                        {
                                            cout << "Node " << commonNeighbor[l] << " is added to m_nodeStatus" << endl;
                                            commonNeighborIDList.push_back(commonNeighbor[l]);
                                        }
                                }
                                cout << "Filtered Common neighbors are" << endl;
                                network.PrintUnsortedNodeIDs(commonNeighborIDList);

                            }

                        }

                    }

                }
            }

        }
        else
        {
            cout << "Node with " << i << " flag has no neighbor that will cause collisions" << endl;
        }

        for(int j = 0 ; j < nodeIDListWithCommonTransmitterStatus.size() ; j++)
        {
            vector<int> oneHopNeighbor = network.GetOneHopNeighborNodeIDListWithoutSourceNode(nodeIDListWithCommonTransmitterStatus[j]);
            for(int k = 0 ; k < oneHopNeighbor.size() ; k++)
            {
                it = m_nodeStatus.find(oneHopNeighbor[k]);
                if(it != m_nodeStatus.end() == true)
                {
                    cout << "Node " << oneHopNeighbor[k] << " already is in m_nodeStatus" << endl;
                }
                else
                {
                    cout << "Node " << oneHopNeighbor[k] << " is added to m_nodeStatus" << endl;
                    m_nodeStatus.insert({oneHopNeighbor[k], nodeConsiderationFlag});
                }
            }

        }
    }
    cout << "commonNeighborIDList" << endl;
    network.PrintUnsortedNodeIDs(commonNeighborIDList);
    vector<int> uniqueCommonNeighborIDList = emptySet.CreateUniqueVector(commonNeighborIDList);
    cout << "uniqueCommonNeighborIDList" << endl;
    network.PrintUnsortedNodeIDs(uniqueCommonNeighborIDList);
    numberOfCollision = uniqueCommonNeighborIDList.size();
    return numberOfCollision;
}

void OTDP::UpdateReceiverStatus(int sourceNodeID, vector<int> forwardListOfOTDP, Network network)
{
    map<int, int>::iterator it, it2;
    vector<int> nodeIDList = network.GetNodeIDOfNetwork();
    nodeIDList = emptySet.SetDifference(nodeIDList, emptySet.IntegerToVector(sourceNodeID));

    for(int i = 0 ; i < nodeIDList.size() ; i++)
    {
        bool received;
        vector<int> broadcastFlags;
        vector<int> oneHopNeighborNodeIDList = network.GetOneHopNeighborNodeIDListWithoutSourceNode(nodeIDList[i]);
        vector<int> receivedFrom = emptySet.SetIntersection(oneHopNeighborNodeIDList, forwardListOfOTDP);

        if(receivedFrom.size() == 1)
        {
            for( it = m_nodeReceiverStatus.begin() ; it != m_nodeReceiverStatus.end() ; it++)
            {
                if(it->first == nodeIDList[i])
                {
                    cout << "Node " << nodeIDList[i] << " is updated for one" << endl;
                    it->second = messageReceivedSuccessfully;
                    break;
                }
            }
        }
        else
        {
            for(int j = 0 ; j < receivedFrom.size() ; j++)
            {
                it = m_nodeTransmitterStatus.find(receivedFrom[j]);
                if(it != m_nodeTransmitterStatus.end() == true)
                {
                    broadcastFlags.push_back(it->second);
                }
            }

            vector<int> uniquebroadcastFlags = broadcastFlags;

            sort(uniquebroadcastFlags.begin(), uniquebroadcastFlags.end());
            auto it = unique(uniquebroadcastFlags.begin(), uniquebroadcastFlags.end());
            uniquebroadcastFlags.resize(distance(uniquebroadcastFlags.begin(), it));

            bool received = false;

            for (int k = 0; k < uniquebroadcastFlags.size(); k++)
            {
                int counter = 0;
                for (int l = 0; l < broadcastFlags.size(); l++)
                {
                    if(uniquebroadcastFlags[k] == broadcastFlags[l])
                    {
                        counter++;
                    }
                }
                if(counter == 1)
                {
                    received = true;
                    break;
                }
            }

            if(received == true)
            {
                for( it2 = m_nodeReceiverStatus.begin() ; it2 != m_nodeReceiverStatus.end() ; it2++)
                {
                    if(it2->first == nodeIDList[i])
                    {
                        cout << "Node " << nodeIDList[i] << " is updated for multiple" << endl;
                        it2->second = messageReceivedSuccessfully;
                        break;
                    }
                }
            }
            else
            {
              cout << "Node " << nodeIDList[i] << " is not updated for multiple" << endl;
            }
        }
    }
}

int OTDP::GetMaximumFlag(map<int, int> m_nodeTransmitterStatus)
{
    int maximumFlag = 0;
    map<int, int>::iterator it;
    for(it = m_nodeTransmitterStatus.begin(); it != m_nodeTransmitterStatus.end(); ++it)
    {
        if(it->second > maximumFlag)
        {
            maximumFlag = it->second;
        }
    }
    return maximumFlag;
}


vector<int> OTDP::RunOTDPForSourceNode(int sourceNodeID, Network network)
{
    vector<int> oneHopNeighborNodeIDList; // N(v)
    vector<int> withinTwoHopNeighborNodeIDList; // N(N(v))
    vector<int> uncoveredNeighborNodeIDList; // U(v)
    vector<int> eligibleOneHopNeighborNodeIDList;  // B(v)
    vector<int> ineligibleOneHopNeighborNodeIDList;  // N(v) - F
    vector<int> eligibleOneHopNeighborNodeIDSubList; // S1, S2
    vector<int> coveredNeighborNodeIDListByEligibleNode; // S1={a, b, c}
    vector<int> coveredNeighborNodeIDList; // Z
    vector<int> forwardList; // F
    map<int, vector<int>> eligibleOneHopNeighborNodeIDMapK; // K
    map<int, int>::iterator it;

    cout << "Node " << sourceNodeID << " is creating forward list and broadcasting the message ->->->->->->->->->->" << endl;
    oneHopNeighborNodeIDList = network.GetOneHopNeighborNodeIDListWithoutSourceNode(sourceNodeID); // N(u)
    withinTwoHopNeighborNodeIDList = network.GetWithinTwoHopNeighborNodeIDListWithoutSourceNode(sourceNodeID); // N(N(u))
    eligibleOneHopNeighborNodeIDList = network.GetOneHopNeighborNodeIDListWithoutSourceNode(sourceNodeID); // B =  N(u)
    uncoveredNeighborNodeIDList = emptySet.SetDifference(withinTwoHopNeighborNodeIDList, oneHopNeighborNodeIDList); // U = N(N(u)) - N(u)

    cout << "One-hop neighbors of source node " << sourceNodeID << " are : ";
    network.PrintSortedNodeIDs(oneHopNeighborNodeIDList);
    cout << "Within two-hop neighbor of destination node " << sourceNodeID << " are : ";
    network.PrintSortedNodeIDs(withinTwoHopNeighborNodeIDList);
    cout << "Element of B : ";
    network.PrintSortedNodeIDs(eligibleOneHopNeighborNodeIDList);
    cout << "Element of U : ";
    network.PrintSortedNodeIDs(uncoveredNeighborNodeIDList);
    cout << "Element of F : ";
    network.PrintUnsortedNodeIDs(forwardList);
    cout << "Element of Z : ";
    network.PrintSortedNodeIDs(coveredNeighborNodeIDList);

    for(int i = 0 ; i < eligibleOneHopNeighborNodeIDList.size() ; i++)
    {
        coveredNeighborNodeIDListByEligibleNode = emptySet.SetIntersection(network.GetOneHopNeighborNodeIDListWithoutSourceNode(eligibleOneHopNeighborNodeIDList[i]), uncoveredNeighborNodeIDList); // S = N(w) intersection U
        eligibleOneHopNeighborNodeIDMapK.insert({eligibleOneHopNeighborNodeIDList[i], coveredNeighborNodeIDListByEligibleNode});
        cout << "Node " << eligibleOneHopNeighborNodeIDList[i] << " is inserted to K" << endl;
    }
    cout << "Element of K : ";
    network.PrintMapWithVector(eligibleOneHopNeighborNodeIDMapK);

    forwardList = CreateForwardList(eligibleOneHopNeighborNodeIDMapK, uncoveredNeighborNodeIDList, coveredNeighborNodeIDList, forwardList, network);

    for( it = m_nodeTransmitterStatus.begin() ; it != m_nodeTransmitterStatus.end() ; it++)
    {
        if(it->first == sourceNodeID)
        {
            cout << "Node " << sourceNodeID << " is updated in m_nodeTransmitterStatus with flag " << broadcastFlag << endl;
            it->second = broadcastFlag;
            break;
        }
    }

    for(int i = 0 ; i < forwardList.size() ; i++)
    {
        cout << "Node " << forwardList[i] << " is inserted to m_nodeTransmitterStatus with flag "<< messageReceivedFlag << endl;
        m_nodeTransmitterStatus.insert({forwardList[i], messageReceivedFlag});
    }

    ineligibleOneHopNeighborNodeIDList = emptySet.SetDifference(oneHopNeighborNodeIDList, forwardList);

    for(int i = 0 ; i < ineligibleOneHopNeighborNodeIDList.size() ; i++)
    {
        cout << "Node " << ineligibleOneHopNeighborNodeIDList[i] << " is inserted to m_nodeTransmitterStatus with flag "<< broadcastCancelFlagForOTDP << endl;
        m_nodeTransmitterStatus.insert({ineligibleOneHopNeighborNodeIDList[i], broadcastCancelFlagForOTDP});
    }

    return forwardList;
}

void OTDP::SetPriority(vector<int> forwardList, Network network)
{
    map<int, int>::iterator it;
    bool check1, check2, matchcheck = false;
    int flag = 1;
    int maximumFlag = 0;

    if(forwardList.size() >= 2)
    {
        cout << "Node " << forwardList[0] << " is inserted to m_nodePriorities with flag "<< flag << endl;
        m_nodePriorities.insert({forwardList[0], flag});

        for(int i = 1 ; i < forwardList.size(); i++)
        {
            for(it = m_nodePriorities.begin(); it != m_nodePriorities.end(); ++it)
            {
                if(it->second > maximumFlag)
                {
                    maximumFlag = it->second;
                }
            }

            for(int j = 1 ; j <= maximumFlag ; j++)
            {
                for(it = m_nodePriorities.begin(); it != m_nodePriorities.end(); ++it)
                {
                    if(it->second == j)
                    {
                        check1 = HaveCommonNeighbors(it->first, forwardList[i], network);
                        check2 = IsNeighbor(it->first, forwardList[i], network);
                        if(check1 == false && check2 == false)
                        {
                            matchcheck = false;
                        }
                        else
                        {
                            matchcheck = true;
                            break;
                        }
                    }
                }
                if(matchcheck == false)
                {
                    flag = j ;
                    cout << "Node " << forwardList[i] << " is inserted to m_nodePriorities with flag "<< flag << endl;
                    m_nodePriorities.insert({forwardList[i], flag});
                    break;
                }
            }
            if(matchcheck == true)
            {
                flag = maximumFlag + 1 ;
                cout << "Node " << forwardList[i] << " is inserted to m_nodePriorities with flag "<< flag << endl;
                m_nodePriorities.insert({forwardList[i], flag});
            }
        }
    }
    else if(forwardList.size() == 1)
    {
        m_nodePriorities.insert({forwardList[0], flag});
    }
    else
    {
        cout << "No node is selected in forward list" << endl;
    }
}

int OTDP::GetPriority(int NodeID)
{
    map<int, int>::iterator it;
    int priority;

    for( it = m_nodePriorities.begin(); it != m_nodePriorities.end(); it++)
    {
        if(it->first == NodeID)
        {
            priority = it->second;
            break;
        }
    }
    return priority;
}

vector<int> OTDP::GetPrioritizedForwardList(vector<int> forwardList)
{
    map<int, int>::iterator it;
    vector<int> prioritizedForwardList;
    vector<int> sortPriorities;
    map<int, int> tempNodePriorities;

    for(int i = 0 ; i < forwardList.size() ; i++)
    {
        for( it = m_nodePriorities.begin(); it != m_nodePriorities.end(); it++)
        {
            if(it->first == forwardList[i])
            {
                tempNodePriorities.insert({forwardList[i], it->second});
                sortPriorities.push_back(it->second);
            }
        }
    }

    sort(sortPriorities.begin(), sortPriorities.end());

    for(int i = 0 ; i < sortPriorities.size() ; i++)
    {
        for( it = tempNodePriorities.begin(); it != tempNodePriorities.end(); it++)
        {
            if(it->second == sortPriorities[i])
            {
                prioritizedForwardList.push_back(it->first);
                tempNodePriorities.erase(it->first);
                break;
            }
        }
    }

    return prioritizedForwardList;
}

bool OTDP::CheckForwardNodeStatus()
{
    map<int, int>::iterator it;
    bool check;
    for( it = m_nodeTransmitterStatus.begin(); it != m_nodeTransmitterStatus.end(); it++)
    {
        if(it->second == messageReceivedFlag)
        {
            check = true;
            break;
        }
        else
        {
            check = false;
        }
    }
    return check;
}

vector<int> OTDP::CreateForwardList(map<int, vector<int>> eligibleOneHopNeighborNodeIDMapK, vector<int> uncoveredNeighborNodeIDList, vector<int> coveredNeighborNodeIDList, vector<int> forwardList, Network network)
{
    int eligibleOneHopNeighborNodeIDCoveredMaximumNodeIDs;
    vector<int> coveredMaximumNodeIDs;
    vector<int> previousCoveredNeighborNodeIDList;
    map<int , vector<int>>::iterator it;

    previousCoveredNeighborNodeIDList = coveredNeighborNodeIDList;

    eligibleOneHopNeighborNodeIDCoveredMaximumNodeIDs = GetEligibleOneHopNeighborNodeIDCoveredMaximumNodeIDs(eligibleOneHopNeighborNodeIDMapK, network);
    cout << "Node " << eligibleOneHopNeighborNodeIDCoveredMaximumNodeIDs << " covered maximum uncovered nodes." << endl;


    // F = F U maximumcoverdnodeID
    it = eligibleOneHopNeighborNodeIDMapK.find(eligibleOneHopNeighborNodeIDCoveredMaximumNodeIDs);
    if(it != eligibleOneHopNeighborNodeIDMapK.end() == true )
    {
        if(it->second.size() == 0)
        {
            cout << "Node " << eligibleOneHopNeighborNodeIDCoveredMaximumNodeIDs << " is not included into Forward List because it does not cover any uncover nodes" << endl;
        }
        else
        {
            forwardList = emptySet.SetUnion(forwardList, emptySet.IntegerToVector(eligibleOneHopNeighborNodeIDCoveredMaximumNodeIDs));
            cout << "Node " << eligibleOneHopNeighborNodeIDCoveredMaximumNodeIDs << " is included into Forward List" << endl;
        }
    }
    cout << "Element of F : ";
    network.PrintUnsortedNodeIDs(forwardList); // F=

    cout << "Element of U : ";
    network.PrintSortedNodeIDs(uncoveredNeighborNodeIDList);


    // Z = Z U coveredMaximumNodeIDs
    it = eligibleOneHopNeighborNodeIDMapK.find(eligibleOneHopNeighborNodeIDCoveredMaximumNodeIDs);
    if(it!=eligibleOneHopNeighborNodeIDMapK.end() == true )
    {
        coveredMaximumNodeIDs = it->second;
    }
    coveredNeighborNodeIDList = emptySet.SetUnion(coveredNeighborNodeIDList, coveredMaximumNodeIDs);
    cout << "Element of Z : ";
    network.PrintSortedNodeIDs(coveredNeighborNodeIDList); // Z=


    // Update K
    it = eligibleOneHopNeighborNodeIDMapK.find(eligibleOneHopNeighborNodeIDCoveredMaximumNodeIDs);
    if(it != eligibleOneHopNeighborNodeIDMapK.end() == true )
    {
        eligibleOneHopNeighborNodeIDMapK.erase(it->first);
        cout << "Node " << it->first << " is deleted from K" << endl;
    }

    for( it = eligibleOneHopNeighborNodeIDMapK.begin(); it != eligibleOneHopNeighborNodeIDMapK.end(); ++it)
    {
        it->second = emptySet.SetDifference(it->second, coveredMaximumNodeIDs);
        cout << "Node " << it->first << " is updated to K" << endl;
    }

    bool IsKEmpty;
    cout << "Element of K : " ;
    if(eligibleOneHopNeighborNodeIDMapK.empty())
    {
        IsKEmpty = true;
        cout <<  endl << "Node _ | Neighbors: { }" << endl;
    }
    else
    {
        network.PrintMapWithVector(eligibleOneHopNeighborNodeIDMapK);
    }


    bool IsZUSimilar = emptySet.SetIdenticalTest(coveredNeighborNodeIDList, uncoveredNeighborNodeIDList);
    bool IsZUnchanged = emptySet.SetIdenticalTest(coveredNeighborNodeIDList, previousCoveredNeighborNodeIDList);


    if(IsZUSimilar || IsZUnchanged || IsKEmpty)
    {
        if(IsZUSimilar)
        {
            cout << "Program exit because Z = U" << endl;
        }
        else if(IsZUnchanged)
        {
            cout << "Program exit because Z is unchanged" << endl;
        }
        else
        {
            cout << "Program exit because K is empty" << endl;
        }

    }
    else
    {
       forwardList = CreateForwardList(eligibleOneHopNeighborNodeIDMapK, uncoveredNeighborNodeIDList, coveredNeighborNodeIDList, forwardList, network);
    }

    return forwardList;
}

vector<int> OTDP::RunOTDPForSourceDestinationNode(int sourceNodeID, int destinationNodeID, Network network)
{
    vector<int> oneHopNeighborNodeIDListOfSource; // N(u)
    vector<int> oneHopNeighborNodeIDListOfDestination; // N(v)
    vector<int> withinTwoHopNeighborNodeIDListOfSource; // N(N(u))
    vector<int> withinTwoHopNeighborNodeIDListOfDestination; // N(N(v))
    vector<int> uncoveredNeighborNodeIDList; // U(v)
    vector<int> eligibleOneHopNeighborNodeIDList;  // B(v)
    vector<int> ineligibleOneHopNeighborNodeIDList;  // N(v)-F
    vector<int> eligibleOneHopNeighborNodeIDSubList; // S
    vector<int> coveredNeighborNodeIDList; // Z
    vector<int> forwardList; // F
    map<int, vector<int>> eligibleOneHopNeighborNodeIDMapK; // K
    map<int, int>::iterator it;

    cout << "Node " << destinationNodeID << " received message from node " << sourceNodeID << endl;
    cout << "Node " << destinationNodeID << " is creating forward list and rebroadcasting the message ->->->->->" << endl;
    oneHopNeighborNodeIDListOfSource =  network.GetOneHopNeighborNodeIDListWithoutSourceNode(sourceNodeID); // N(u)
    oneHopNeighborNodeIDListOfDestination = network.GetOneHopNeighborNodeIDListWithoutSourceNode(destinationNodeID); // N(v)
    withinTwoHopNeighborNodeIDListOfSource = network.GetWithinTwoHopNeighborNodeIDListWithoutSourceNode(sourceNodeID);  //N(N(u))
    withinTwoHopNeighborNodeIDListOfDestination = network.GetWithinTwoHopNeighborNodeIDListWithoutSourceNode(destinationNodeID);  //N(N(v))
    eligibleOneHopNeighborNodeIDList = emptySet.SetDifference(oneHopNeighborNodeIDListOfDestination, oneHopNeighborNodeIDListOfSource, emptySet.IntegerToVector(sourceNodeID)); // B(v) = N(v) - N(u)
    uncoveredNeighborNodeIDList = emptySet.SetDifference(withinTwoHopNeighborNodeIDListOfDestination, withinTwoHopNeighborNodeIDListOfSource); // U(v) = N(N(v)) - N(N(u))

    cout << "One-hop neighbors of source node " << sourceNodeID << " are : ";
    network.PrintSortedNodeIDs(oneHopNeighborNodeIDListOfSource);
    cout << "One-hop neighbors of destination node " << destinationNodeID << " are : ";
    network.PrintSortedNodeIDs(oneHopNeighborNodeIDListOfDestination);
    cout << "Within Two-hop Neighbor of Source Node " << sourceNodeID << " are : ";
    network.PrintSortedNodeIDs(withinTwoHopNeighborNodeIDListOfSource);
    cout << "Within Two-hop Neighbor of Destination Node " << destinationNodeID << " are : ";
    network.PrintSortedNodeIDs(withinTwoHopNeighborNodeIDListOfDestination);
    cout << "Element of B : ";
    network.PrintSortedNodeIDs(eligibleOneHopNeighborNodeIDList);
    cout << "Element of U : ";
    network.PrintSortedNodeIDs(uncoveredNeighborNodeIDList);
    cout << "Element of F : ";
    network.PrintUnsortedNodeIDs(forwardList);
    cout << "Element of Z : ";
    network.PrintSortedNodeIDs(coveredNeighborNodeIDList);

    for(int i = 0 ; i < eligibleOneHopNeighborNodeIDList.size() ; i++)
    {
        eligibleOneHopNeighborNodeIDSubList = emptySet.SetIntersection(network.GetOneHopNeighborNodeIDListWithoutSourceNode(eligibleOneHopNeighborNodeIDList[i]), uncoveredNeighborNodeIDList);
        eligibleOneHopNeighborNodeIDMapK.insert({eligibleOneHopNeighborNodeIDList[i], eligibleOneHopNeighborNodeIDSubList});
        cout << "Node " << eligibleOneHopNeighborNodeIDList[i] << " is inserted to K" << endl;
    }
    cout << "Element of K : ";
    network.PrintMapWithVector(eligibleOneHopNeighborNodeIDMapK);

    forwardList = CreateForwardList(eligibleOneHopNeighborNodeIDMapK, uncoveredNeighborNodeIDList, coveredNeighborNodeIDList, forwardList, network);

    for( it = m_nodeTransmitterStatus.begin() ; it != m_nodeTransmitterStatus.end() ; it++)
    {
        if(it->first == destinationNodeID)
        {
            //int priority = GetPriority(destinationNodeID);   // CCATDP
            int priority = 1;                                  //OTDP
            it->second = rebroadcastFlag + priority;
            break;
        }
    }

    for(int i = 0 ; i < forwardList.size() ; i++)
    {
        it = m_nodeTransmitterStatus.find(forwardList[i]);
        if(it != m_nodeTransmitterStatus.end() == true )
        {
            cout << "Node " << forwardList[i] << " already received the message" << endl;
        }
        else
        {
            m_nodeTransmitterStatus.insert({forwardList[i], messageReceivedFlag});
            cout << "Node " << forwardList[i] << " is inserted to m_nodeTransmitterStatus with flag "<< messageReceivedFlag << endl;
        }
    }

    ineligibleOneHopNeighborNodeIDList = emptySet.SetDifference(oneHopNeighborNodeIDListOfDestination, forwardList);

    for(int i = 0 ; i < ineligibleOneHopNeighborNodeIDList.size() ; i++)
    {
        it = m_nodeTransmitterStatus.find(ineligibleOneHopNeighborNodeIDList[i]);
        if(it!=m_nodeTransmitterStatus.end() == true )
        {
            cout << "Node " << ineligibleOneHopNeighborNodeIDList[i] << " already receive the message" << endl;
        }
        else
        {
            m_nodeTransmitterStatus.insert({ineligibleOneHopNeighborNodeIDList[i], broadcastCancelFlagForOTDP});
            cout << "Node " << ineligibleOneHopNeighborNodeIDList[i] << " is inserted to m_nodeTransmitterStatus with flag " << broadcastCancelFlagForOTDP << endl;
        }
    }
    return forwardList;
}
/*
// Selection process use minimum neighbors

int OTDP::GetEligibleOneHopNeighborNodeIDCoveredMaximumNodeIDs(map<int, vector<int>> eligibleOneHopNeighborNodeIDMapK, Network network)
{
    vector<int> NodesCoveredMaximumNodeIDs;
    int NodeIDCoveredMaximumNodeIDs;
    int maximumSizeOfS = 0;

    for( auto it = eligibleOneHopNeighborNodeIDMapK.begin(); it != eligibleOneHopNeighborNodeIDMapK.end(); ++it)
    {
        if(maximumSizeOfS < it->second.size())
        {
          maximumSizeOfS =   it->second.size();
        }
    }

    for( auto it = eligibleOneHopNeighborNodeIDMapK.begin(); it != eligibleOneHopNeighborNodeIDMapK.end(); ++it)
    {
         if(it->second.size() == maximumSizeOfS)
         {
           NodesCoveredMaximumNodeIDs.push_back(it->first);
         }
    }
    if(NodesCoveredMaximumNodeIDs.size() == 1)
    {
      NodeIDCoveredMaximumNodeIDs = NodesCoveredMaximumNodeIDs[0];
    }
    else
    {
        map<int, vector<int>> nodeWithOneHopNeibor;
        int minimumSizeOfOneHopNeibor = network.GetNetworkSize();
        for(int i = 0 ; i < NodesCoveredMaximumNodeIDs.size() ; i++)
        {
            vector<int> oneHopNeighborList = network.GetOneHopNeighborNodeIDListWithoutSourceNode(NodesCoveredMaximumNodeIDs[i]);
            nodeWithOneHopNeibor.insert({NodesCoveredMaximumNodeIDs[i], oneHopNeighborList});
        }
        for( auto it = nodeWithOneHopNeibor.begin(); it != nodeWithOneHopNeibor.end(); ++it)
        {
            if(minimumSizeOfOneHopNeibor > it->second.size())
            {
              minimumSizeOfOneHopNeibor =   it->second.size();
            }
        }

        for( auto it = nodeWithOneHopNeibor.begin(); it != nodeWithOneHopNeibor.end(); ++it)
        {
             if(it->second.size() == minimumSizeOfOneHopNeibor)
             {
               NodeIDCoveredMaximumNodeIDs =  it->first;
               break;
             }
        }

    }

    return NodeIDCoveredMaximumNodeIDs;
}

*/


// Selection process use minimum ID

int OTDP::GetEligibleOneHopNeighborNodeIDCoveredMaximumNodeIDs(map<int, vector<int>> eligibleOneHopNeighborNodeIDMapK, Network network)
{

    int NodeIDCoveredMaximumNodeIDs;
    int maximumSizeOfS = 0;

    for( auto it = eligibleOneHopNeighborNodeIDMapK.begin(); it != eligibleOneHopNeighborNodeIDMapK.end(); ++it)
    {
        if(maximumSizeOfS < it->second.size())
        {
          maximumSizeOfS =   it->second.size();
        }
    }

    for( auto it = eligibleOneHopNeighborNodeIDMapK.begin(); it != eligibleOneHopNeighborNodeIDMapK.end(); ++it)
    {
         if(it->second.size() == maximumSizeOfS)
         {
           NodeIDCoveredMaximumNodeIDs =  it->first;
           break;
         }
    }
    return NodeIDCoveredMaximumNodeIDs;
}



int OTDP::GetNodeIDFromMessageReceived(int nodeID, Network network)
{
    map<int, int>::iterator it;
    vector<int> flagValue;
    map<int , int> receivedNodeIDListMap;
    int receivedNodeID;
    vector<int> oneHopNeighborNodeIDList;

    oneHopNeighborNodeIDList = network.GetOneHopNeighborNodeIDListWithoutSourceNode(nodeID);

    for(int i = 0 ; i < oneHopNeighborNodeIDList.size() ; i++)
    {
        it = m_nodeTransmitterStatus.find(oneHopNeighborNodeIDList[i]);
        if(it != m_nodeTransmitterStatus.end() == true)
        {
            if(it->second >= broadcastFlag)
            {
                receivedNodeIDListMap.insert({oneHopNeighborNodeIDList[i] , it->second});
                flagValue.push_back(it->second);
            }
        }
    }

    sort(flagValue.begin(), flagValue.end());

    for(it = receivedNodeIDListMap.begin(); it != receivedNodeIDListMap.end(); ++it)
    {
        if(it->second == flagValue[0])
        {
            receivedNodeID = it->first;
        }
    }
    return receivedNodeID;
}

bool OTDP::IsNeighbor(int nodeID1, int nodeID2, Network network)
{
    bool check;
    int receivedNodeID1 = GetNodeIDFromMessageReceived(nodeID1, network);
    int receivedNodeID2 = GetNodeIDFromMessageReceived(nodeID2, network);
    if(receivedNodeID1 == receivedNodeID2)
    {
        cout << "Both nodes " << nodeID1 << " and " << nodeID2 << " have received message from node " << receivedNodeID1 << endl;
        vector<int> oneHopNeighborNodeIDListOFNodeID1 = network.GetOneHopNeighborNodeIDListWithoutSourceNode(nodeID1);
        vector<int> oneHopNeighborNodeIDListOFNodeID2 = network.GetOneHopNeighborNodeIDListWithoutSourceNode(nodeID2);
        vector<int> oneHopNeighborNodeIDListOFNodeID1WithoutCommonSource = emptySet.SetDifference(oneHopNeighborNodeIDListOFNodeID1, emptySet.IntegerToVector(receivedNodeID1));
        if(emptySet.SetIntersection(oneHopNeighborNodeIDListOFNodeID1WithoutCommonSource, emptySet.IntegerToVector(nodeID2)).size() == 0)
        {
            cout << "Node " << nodeID2 << " is not the neighbor of node " << nodeID1 << endl;
            check = false;
        }
        else
        {
            cout << "Node " << nodeID2 << " is the neighbor of node " << nodeID1 << endl;
            check = true;
        }
    }
    else
    {
        cout << "Both nodes " << nodeID1 << " and " << nodeID2 << " have not received message from common node " << endl;
    }
    return check;
}

bool OTDP::HaveCommonNeighbors(int nodeID1, int nodeID2, Network network)
{
    bool check;
    int receivedNodeID1 = GetNodeIDFromMessageReceived(nodeID1, network);
    int receivedNodeID2 = GetNodeIDFromMessageReceived(nodeID2, network);
    if(receivedNodeID1 == receivedNodeID2)
    {
        cout << "Both nodes " << nodeID1 << " and " << nodeID2 << " have received message from node " << receivedNodeID1 << endl;
        vector<int> oneHopNeighborNodeIDListOFNodeID1 = network.GetOneHopNeighborNodeIDListWithoutSourceNode(nodeID1);
        vector<int> oneHopNeighborNodeIDListOFNodeID2 = network.GetOneHopNeighborNodeIDListWithoutSourceNode(nodeID2);
        vector<int> oneHopNeighborNodeIDListOFNodeID1WithoutCommonSource = emptySet.SetDifference(oneHopNeighborNodeIDListOFNodeID1, emptySet.IntegerToVector(receivedNodeID1));
        vector<int> oneHopNeighborNodeIDListOFNodeID2WithoutCommonSource = emptySet.SetDifference(oneHopNeighborNodeIDListOFNodeID2, emptySet.IntegerToVector(receivedNodeID1));
        if(emptySet.SetIntersection(oneHopNeighborNodeIDListOFNodeID1WithoutCommonSource, oneHopNeighborNodeIDListOFNodeID2WithoutCommonSource).size() == 0)
        {
            cout << "Node " << nodeID2 << " and node " << nodeID1 << " have no common neighbor" << endl;
            check = false;
        }
        else
        {
            cout << "Node " << nodeID2 << " and node " << nodeID1 << " have at least one common neighbor" << endl;
            check = true;
        }
    }
    else
    {
        cout << "Both nodes " << nodeID1 << " and " << nodeID2 << " have not received message from common node " << endl;
    }

    return check;
}


bool OTDP::AreNodesNeighbor(int nodeID1, int nodeID2, Network network)
{
    bool check;

    vector<int> oneHopNeighborNodeIDListOFNodeID1 = network.GetOneHopNeighborNodeIDListWithoutSourceNode(nodeID1);

    if(emptySet.SetIntersection(oneHopNeighborNodeIDListOFNodeID1, emptySet.IntegerToVector(nodeID2)).size() == 0)
    {
        cout << "Node " << nodeID2 << " is not the neighbor of node " << nodeID1 << endl;
        check = false;
    }
    else
    {
        cout << "Node " << nodeID2 << " is the neighbor of node " << nodeID1 << endl;
        check = true;
    }
    return check;
}

bool OTDP::HasCommonNeighbors(int nodeID1, int nodeID2, Network network)
{
    bool check;
    int receivedNodeID1 = GetNodeIDFromMessageReceived(nodeID1, network);
    int receivedNodeID2 = GetNodeIDFromMessageReceived(nodeID2, network);

    vector<int> oneHopNeighborNodeIDListOFNodeID1 = network.GetOneHopNeighborNodeIDListWithoutSourceNode(nodeID1);
    vector<int> oneHopNeighborNodeIDListOFNodeID2 = network.GetOneHopNeighborNodeIDListWithoutSourceNode(nodeID2);
    vector<int> oneHopNeighborNodeIDListOFNodeID1WithoutCommonSource = emptySet.SetDifference(oneHopNeighborNodeIDListOFNodeID1, emptySet.IntegerToVector(receivedNodeID1));
    vector<int> oneHopNeighborNodeIDListOFNodeID2WithoutCommonSource = emptySet.SetDifference(oneHopNeighborNodeIDListOFNodeID2, emptySet.IntegerToVector(receivedNodeID1));
    if(emptySet.SetIntersection(oneHopNeighborNodeIDListOFNodeID1WithoutCommonSource, oneHopNeighborNodeIDListOFNodeID2WithoutCommonSource).size() == 0)
    {
        cout << "Node " << nodeID2 << " and node " << nodeID1 << " have no common neighbor" << endl;
        check = false;
    }
    else
    {
        cout << "Node " << nodeID2 << " and node " << nodeID1 << " have at least one common neighbor" << endl;
        check = true;
    }
    return check;
}

vector<int> OTDP::GetCommonNeighbors(int nodeID1, int nodeID2, Network network)
{
    vector<int> commonNeighbors;
    int receivedNodeID1 = GetNodeIDFromMessageReceived(nodeID1, network);
    int receivedNodeID2 = GetNodeIDFromMessageReceived(nodeID2, network);

    vector<int> oneHopNeighborNodeIDListOFNodeID1 = network.GetOneHopNeighborNodeIDListWithoutSourceNode(nodeID1);
    vector<int> oneHopNeighborNodeIDListOFNodeID2 = network.GetOneHopNeighborNodeIDListWithoutSourceNode(nodeID2);
    vector<int> oneHopNeighborNodeIDListOFNodeID1WithoutCommonSource = emptySet.SetDifference(oneHopNeighborNodeIDListOFNodeID1, emptySet.IntegerToVector(receivedNodeID1));
    vector<int> oneHopNeighborNodeIDListOFNodeID2WithoutCommonSource = emptySet.SetDifference(oneHopNeighborNodeIDListOFNodeID2, emptySet.IntegerToVector(receivedNodeID1));
    commonNeighbors = emptySet.SetIntersection(oneHopNeighborNodeIDListOFNodeID1WithoutCommonSource, oneHopNeighborNodeIDListOFNodeID2WithoutCommonSource);

    return commonNeighbors;
}

void OTDP::DataSheetOfOTDP()
{
    string outputFilename = "otdp.csv";
    std::ofstream outputStream (outputFilename.c_str (), ios::app);
    outputStream << "nodenumber" << ",";
    outputStream << "txnumber" << ",";
    outputStream << "savebroadcast" << ",";
    outputStream << "redundancy" << ",";
    outputStream << "packetreceived" << ",";
    outputStream << "broadcastlatency" << ",";
    outputStream << "energyconsumption" << ",";
    outputStream << "reachability" << ",";
    outputStream << "contention" << ",";
    outputStream << "collision" << endl;

}

void OTDP::PerformanceMeasure(Network network)
{
    map<int, int>::iterator it, it2;
    vector<int> forwardListOfOTDP;


    string outputFilename = "otdp.csv";
    std::ofstream outputStream (outputFilename.c_str (), ios::app);

// Find number of nodes

    float N = network.m_nodes.size();

// Find number of forwarding nodes

    for( it = m_nodeTransmitterStatus.begin(); it != m_nodeTransmitterStatus.end(); it++)
    {
        if(it->second >= broadcastFlag)
        forwardListOfOTDP.push_back(it->first);
    }
    float Nf = forwardListOfOTDP.size();


// Saved rebroadcast

    float SRB = (N - Nf) / N;

// Redundancy

    float redundancy = Nf / N;

// Find average number of packets received

    vector<int> oneHopNeighborNodeIDList;
    vector<int> receivedFromNodeIDList;
    float Nr = 0;

    for(int i = 0 ; i < network.m_nodes.size() ; i++)
    {
        oneHopNeighborNodeIDList = network.GetOneHopNeighborNodeIDListWithoutSourceNode(network.m_nodes.at(i).GetNodeID());
        receivedFromNodeIDList = emptySet.SetIntersection(oneHopNeighborNodeIDList, forwardListOfOTDP);
        Nr = Nr + receivedFromNodeIDList.size();
    }
    float AMR = Nr / N;

// Energy consumption

    float pt = 1346.16; // mW
    float pr = 900.60; // mW
    float ps = 739.44; // mW

    float Ttimer = 5000; // microsecond
    float difs = 50; // microsecond
    float CWmin = 31;
    float Tcsmaslot = 20; // microsecond
    float Tpreamble = 144; // microsecond
    float Tphy = 48; // microsecond
    float Hmac = 28; // bytes
    float payload = 84;  // bytes
    float Rdata = 2; // Mbps


    float Tdata = Tpreamble + Tphy + (8*(Hmac + payload)) / Rdata; // microsecond
    float Tbo = (CWmin * Tcsmaslot) /2 ; // microsecond
    float Tslot = difs + Tbo + Tdata; //microsecond

    //float Et = Nf * ((difs + Tbo) * ps + Tdata * pt);
    float Er = Nr * ((difs + Tbo) * ps + Tdata * pr);
    float Et = 0;
    int priority;

    for(int i = 0; i < forwardListOfOTDP.size(); i++)
    {
        it2 = m_nodePriorities.find(forwardListOfOTDP[i]);
        if(it2 != m_nodePriorities.end() == true)
        priority = it2->second;
        Et = Et + (priority - 1) * ps * Tslot + ((difs + Tbo) * ps + Tdata * pt);
    }

    float E = (Et + Er) / 1000000000; // Jule

// Broadcast Latency

    float Tdelay;
    float m_broadcast = 1;
    float t_broadcast = difs + Tbo + Tdata; // 1000  microsecond
    float t_rebroadcast = difs + Tbo + Tdata; // 1000  microsecond


    int maximumRebroadcastFlag = 0;
    for( it = m_nodeTransmitterStatus.begin(); it != m_nodeTransmitterStatus.end(); ++it)
    {
        if(it->second > maximumRebroadcastFlag)
        {
            maximumRebroadcastFlag = it->second;
        }
    }
    float m_rebroadcastcycle = maximumRebroadcastFlag - broadcastFlag;

    cout << "Number of rebroadcast cycle of OTDP " << m_rebroadcastcycle << endl;

    Tdelay = (m_broadcast * t_broadcast + m_rebroadcastcycle * t_rebroadcast) / 1000 ; // milisecond

//Reachability

    vector<int> receivedNodeIDListOfOTDP;
    for( it = m_nodeReceiverStatus.begin(); it != m_nodeReceiverStatus.end(); it++)
    {
        if(it->second == messageReceivedSuccessfully)
        receivedNodeIDListOfOTDP.push_back(it->first);
    }
    float R = receivedNodeIDListOfOTDP.size() / N;

//Calculation of number of contention
    float Contention = GetNumberOfContention(network);

//Calculation of number of collision
    float Collision = GetNumberOfCollision(network);

    outputStream << N << ",";
    outputStream << Nf << ",";
    outputStream << SRB << ",";
    outputStream << redundancy << ",";
    outputStream << AMR << ",";
    outputStream << Tdelay << ",";
    outputStream << E << ",";
    outputStream << R << ",";
    outputStream << Contention << ",";
    outputStream << Collision << endl;

    outputStream.close ();
}

