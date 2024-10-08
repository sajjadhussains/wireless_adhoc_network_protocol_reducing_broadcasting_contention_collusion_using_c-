#ifndef CCAPDP_H
#define CCAPDP_H

#include "set.h"
#include "network.h"

#include<vector>

class CCAPDP
{
    public:

        map<int, int> m_nodeTransmitterStatus;
        map<int, int> m_nodeReceiverStatus;
        map<int, int> m_nodePriorities;
        map<int, int> m_nodeStatus;

        Set emptySet;

        // m_nodePriorities (1, 2,3, .........)
        int priorityFlagOfSourceNode = 1;

        // m_nodeReceiverStatus
        int messageReceivedSuccessfully = 1;
        int messageNotReceived = 0;

        // m_nodeTransmitterStatus
        int messageReceivedFlag = 0;
        int broadcastCancelFlagForCCAPDP = 8;
        int broadcastFlag = 11;
        int rebroadcastFlag; // 12, 13, 14, .........

        int nodeConsiderationFlag = 7;

        CCAPDP();
        void DoDispose();

        int GetEligibleOneHopNeighborNodeIDCoveredMaximumNodeIDs(map<int, vector<int>> eligibleOneHopNeighborNodeIDMapK, Network network);
        //int GetEligibleOneHopNeighborNodeIDCoveredMaximumNodeIDs(K, network);
        vector<int> RunCCAPDPForSourceNode(int sourceNodeID, Network network);
        vector<int> RunCCAPDP(int sourceNodeID, Network network);
        vector<int> CreateForwardList(map<int, vector<int>> eligibleOneHopNeighborNodeIDMap, vector<int> uncoveredNeighborNodeIDList, vector<int> coveredNeighborNodeIDList, vector<int> forwardList, Network network);
        //vector<int> CreateForwardList(K, S, U, Z, F, network);
        vector<int> RunCCAPDPForSourceDestinationNode(int sourceNodeID, int destinationNodeID, Network network);
        bool CheckForwardNodeStatus();

        int GetNodeIDFromMessageReceived(int nodeID, Network network);
        bool IsNeighbor(int nodeID1, int nodeID2, Network network);
        bool HaveCommonNeighbors(int nodeID1, int nodeID2, Network network);
        void SetPriority(vector<int> forwardlist, Network network);
        int GetPriority(int NodeID);
        vector<int> GetPrioritizedForwardList(vector<int> forwardList);
        int GetMaximumFlag(map<int, int> m_nodeTransmitterStatus);
        void UpdateReceiverStatus(int sourceNodeID, vector<int> forwardListOfCCAPDP, Network network);
        float GetNumberOfContention(Network network);
        float GetNumberOfCollision(Network network);
        bool AreNodesNeighbor(int nodeID1, int nodeID2, Network network);
        bool HasCommonNeighbors(int nodeID1, int nodeID2, Network network);
        vector<int> GetCommonNeighbors(int nodeID1, int nodeID2, Network network);

        void DataSheetOfCCAPDP();
        void PerformanceMeasure(Network network);


    protected:

    private:
};

#endif // CCAPDP_H

