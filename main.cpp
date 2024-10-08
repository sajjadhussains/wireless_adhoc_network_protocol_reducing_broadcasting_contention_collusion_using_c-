#include "set.h"
#include "node.h"
#include "network.h"
#include "networktopology.h"

#include "odp.h"  // Original Dominant Pruning
#include "opdp.h"  // Original Partial Dominant Pruning
#include "otdp.h"  // Original Total Dominant Pruning

#include "ccadp.h" // Contention and Collision Aware Dominant Pruning
#include "ccapdp.h" // Contention and Collision Aware Partial Dominant Pruning
#include "ccatdp.h" // Contention and Collision Aware Total Dominant Pruning


using namespace std;

int main()
{

// Begin Network configuration by manual input

// Network-1
/*
    Node node;
    Network network;
    int cost = 1;

    node.SetNodeID(1);
    network.AddNode(node);

    node.SetNodeID(2);
    network.AddNode(node);

    node.SetNodeID(3);
    network.AddNode(node);

    node.SetNodeID(4);
    network.AddNode(node);

    node.SetNodeID(5);
    network.AddNode(node);

    node.SetNodeID(6);
    network.AddNode(node);

    node.SetNodeID(7);
    network.AddNode(node);

    node.SetNodeID(8);
    network.AddNode(node);

    node.SetNodeID(9);
    network.AddNode(node);

    node.SetNodeID(10);
    network.AddNode(node);

    node.SetNodeID(11);
    network.AddNode(node);

    node.SetNodeID(12);
    network.AddNode(node);

    network.AddLink(1, 2, cost);
    network.AddLink(1, 5, cost);

    network.AddLink(2, 3, cost);
    network.AddLink(2, 6, cost);
    network.AddLink(2, 7, cost);

    network.AddLink(3, 4, cost);

    network.AddLink(4, 7, cost);
    network.AddLink(4, 8, cost);

    network.AddLink(5, 6, cost);
    network.AddLink(5, 9, cost);

    network.AddLink(6, 7, cost);
    network.AddLink(6, 9, cost);

    network.AddLink(7, 8, cost);
    network.AddLink(7, 11, cost);

    network.AddLink(8, 12, cost);

    network.AddLink(9, 10, cost);

    network.AddLink(10, 11, cost);

    network.AddLink(11, 12, cost);

    network.PrintNetwork();

    if(network.IsNetworkConnected() == true)
    {
        cout << "Network is connected" << endl;
    }
    else
    {
      cout << "Network is not connected" << endl;
    }
    int sourceNodeID = 6;
*/
//    ODP odp;
//    vector<int> forwardNodeListOfODP = odp.RunODP(sourceNodeID, network);
//
//    cout << "Sequence of forward list of ODP is " << endl;
//    network.PrintUnsortedNodeIDs(forwardNodeListOfODP);
//    cout << "Number of forwarding stations of ODP is " << forwardNodeListOfODP.size() <<  endl;

//    CCADP ccadp;
//    vector<int> forwardNodeListOfCCADP = ccadp.RunCCADP(sourceNodeID, network);
//
//    cout << "Sequence of forward list of CCADP is " << endl;
//    network.PrintUnsortedNodeIDs(forwardNodeListOfCCADP);
//    cout << "Number of forwarding stations of CCADP is " << forwardNodeListOfCCADP.size() <<  endl;

 // Network-2 (Thesis Paper of Mamataj, BUET)

    Node node;
    Network network;
    int cost = 1;

    node.SetNodeID(0);
    network.AddNode(node);

    node.SetNodeID(1);
    network.AddNode(node);

    node.SetNodeID(2);
    network.AddNode(node);

    node.SetNodeID(3);
    network.AddNode(node);

    node.SetNodeID(4);
    network.AddNode(node);

    node.SetNodeID(5);
    network.AddNode(node);

    node.SetNodeID(6);
    network.AddNode(node);

    node.SetNodeID(7);
    network.AddNode(node);

    node.SetNodeID(8);
    network.AddNode(node);

    node.SetNodeID(9);
    network.AddNode(node);

    node.SetNodeID(10);
    network.AddNode(node);

    node.SetNodeID(11);
    network.AddNode(node);

    node.SetNodeID(12);
    network.AddNode(node);

    node.SetNodeID(13);
    network.AddNode(node);

    node.SetNodeID(14);
    network.AddNode(node);

    node.SetNodeID(15);
    network.AddNode(node);

    node.SetNodeID(16);
    network.AddNode(node);

    node.SetNodeID(17);
    network.AddNode(node);

    node.SetNodeID(18);
    network.AddNode(node);

    node.SetNodeID(19);
    network.AddNode(node);

    node.SetNodeID(20);
    network.AddNode(node);

    node.SetNodeID(21);
    network.AddNode(node);

    node.SetNodeID(22);
    network.AddNode(node);

    node.SetNodeID(23);
    network.AddNode(node);

    node.SetNodeID(24);
    network.AddNode(node);

    network.AddLink(0, 1, cost);
    network.AddLink(0, 4, cost);
    network.AddLink(0, 5, cost);
    network.AddLink(0, 6, cost);
    network.AddLink(0, 9, cost);
    network.AddLink(0, 10, cost);
    network.AddLink(0, 14, cost);
    network.AddLink(0, 17, cost);
    network.AddLink(0, 19, cost);
    network.AddLink(0, 20, cost);
    network.AddLink(0, 21, cost);
    network.AddLink(0, 22, cost);

    network.AddLink(1, 4, cost);
    network.AddLink(1, 5, cost);
    network.AddLink(1, 6, cost);
    network.AddLink(1, 9, cost);
    network.AddLink(1, 10, cost);
    network.AddLink(1, 11, cost);
    network.AddLink(1, 14, cost);
    network.AddLink(1, 17, cost);
    network.AddLink(1, 18, cost);
    network.AddLink(1, 19, cost);
    network.AddLink(1, 20, cost);
    network.AddLink(1, 21, cost);
    network.AddLink(1, 22, cost);

    network.AddLink(2, 3, cost);
    network.AddLink(2, 6, cost);
    network.AddLink(2, 17, cost);
    network.AddLink(2, 20, cost);
    network.AddLink(2, 23, cost);

    network.AddLink(3, 4, cost);
    network.AddLink(3, 6, cost);
    network.AddLink(3, 9, cost);
    network.AddLink(3, 10, cost);
    network.AddLink(3, 13, cost);
    network.AddLink(3, 19, cost);
    network.AddLink(3, 20, cost);
    network.AddLink(3, 23, cost);
    network.AddLink(3, 24, cost);

    network.AddLink(4, 5, cost);
    network.AddLink(4, 8, cost);
    network.AddLink(4, 9, cost);
    network.AddLink(4, 10, cost);
    network.AddLink(4, 19, cost);
    network.AddLink(4, 20, cost);
    network.AddLink(4, 21, cost);
    network.AddLink(4, 23, cost);
    network.AddLink(4, 24, cost);

    network.AddLink(5, 8, cost);
    network.AddLink(5, 9, cost);
    network.AddLink(5, 10, cost);
    network.AddLink(5, 16, cost);
    network.AddLink(5, 18, cost);
    network.AddLink(5, 19, cost);
    network.AddLink(5, 21, cost);


    network.AddLink(6, 12, cost);
    network.AddLink(6, 17, cost);
    network.AddLink(6, 20, cost);
    network.AddLink(6, 21, cost);
    network.AddLink(6, 23, cost);

    network.AddLink(7, 11, cost);
    network.AddLink(7, 14, cost);
    network.AddLink(7, 15, cost);
    network.AddLink(7, 18, cost);
    network.AddLink(7, 22, cost);

    network.AddLink(8, 9, cost);
    network.AddLink(8, 10, cost);
    network.AddLink(8, 16, cost);
    network.AddLink(8, 19, cost);
    network.AddLink(8, 24, cost);

    network.AddLink(9, 10, cost);
    network.AddLink(9, 16, cost);
    network.AddLink(9, 17, cost);
    network.AddLink(9, 19, cost);
    network.AddLink(9, 20, cost);
    network.AddLink(9, 21, cost);

    network.AddLink(10, 16, cost);
    network.AddLink(10, 19, cost);
    network.AddLink(10, 21, cost);
    network.AddLink(10, 23, cost);
    network.AddLink(10, 24, cost);

    network.AddLink(11, 14, cost);
    network.AddLink(11, 15, cost);
    network.AddLink(11, 22, cost);

    network.AddLink(12, 17, cost);
    network.AddLink(12, 20, cost);

    network.AddLink(13, 23, cost);

    network.AddLink(14, 15, cost);
    network.AddLink(14, 18, cost);
    network.AddLink(14, 21, cost);
    network.AddLink(14, 22, cost);

    network.AddLink(15, 18, cost);
    network.AddLink(15, 22, cost);

    network.AddLink(16, 18, cost);
    network.AddLink(16, 19, cost);
    network.AddLink(16, 21, cost);

    network.AddLink(17, 20, cost);
    network.AddLink(17, 21, cost);
    network.AddLink(17, 23, cost);

    network.AddLink(18, 21, cost);
    network.AddLink(18, 22, cost);

    network.AddLink(19, 21, cost);
    network.AddLink(19, 24, cost);

    network.AddLink(20, 21, cost);
    network.AddLink(20, 23, cost);

    network.AddLink(21, 22, cost);

    network.PrintNetwork();
    if(network.IsNetworkConnected() == true)
    {
        cout << "Network is connected" << endl;
    }
    else
    {
      cout << "Network is not connected" << endl;
    }

/*
    string outputFilename = "test.csv";
    std::ofstream outputStream (outputFilename.c_str (), ios::app);
    outputStream << "sourceNodeID" << ",";
    outputStream << "contentionODP" << ",";
    outputStream << "collisionODP" << ",";
    outputStream << "contentionCCADP" << ",";
    outputStream << "collisionCCADP" << endl;

    int sourceNodeID = 0;

    for (int r = 1 ; r <= 25; r++)
    {

        ODP odp;
        vector<int> forwardNodeListOfODP = odp.RunODP(sourceNodeID, network);
        float numberOfContentionOfODP = odp.GetNumberOfContention(network);
        float numberOfCollisionOfODP = odp.GetNumberOfCollision(network);

        CCADP ccadp;
        vector<int> forwardNodeListOfCCADP = ccadp.RunCCADP(sourceNodeID, network);
        float numberOfContentionOfCCADP = ccadp.GetNumberOfContention(network);
        float numberOfCollisionOfCCADP = ccadp.GetNumberOfCollision(network);

        outputStream << sourceNodeID << ",";
        outputStream << numberOfContentionOfODP << ",";
        outputStream << numberOfCollisionOfODP << ",";
        outputStream << numberOfContentionOfCCADP << ",";
        outputStream << numberOfCollisionOfCCADP << endl;

        sourceNodeID = sourceNodeID + 1;

    }
        outputStream.close ();
*/

    int sourceNodeID = 8;

//    ODP odp;
//    vector<int> forwardNodeListOfODP = odp.RunODP(sourceNodeID, network);
//    float numberOfCollisionOfODP = odp.GetNumberOfCollision(network);
//    float numberOfContentionOfODP = odp.GetNumberOfContention(network);

//    OPDP opdp;
//    vector<int> forwardNodeListOfOPDP = opdp.RunOPDP(sourceNodeID, network);
//
//    OTDP otdp;
//    vector<int> forwardNodeListOfOTDP = otdp.RunOTDP(sourceNodeID, network);
//
    CCADP ccadp;
    vector<int> forwardNodeListOfCCADP = ccadp.RunCCADP(sourceNodeID, network);
    float numberOfCollisionOfCCADP = ccadp.GetNumberOfCollision(network);
    float numberOfContentionOfCCADP = ccadp.GetNumberOfContention(network);
//
//    CCAPDP ccapdp;
//    vector<int> forwardNodeListOfCCAPDP = ccapdp.RunCCAPDP(sourceNodeID, network);
//
//    CCATDP ccatdp;
//    vector<int> forwardNodeListOfCCATDP = ccatdp.RunCCATDP(sourceNodeID, network);
//
//    cout << "Sequence of forward list of ODP is " << endl;
//    network.PrintUnsortedNodeIDs(forwardNodeListOfODP);
//    cout << "Number of forwarding stations of ODP is " << forwardNodeListOfODP.size() <<  endl;
//    cout << "Number of collision is " << numberOfCollisionOfODP <<  endl;
//    cout << "Number of contention is " << numberOfContentionOfODP <<  endl;
//
//    cout << "Sequence of forward list of OPDP is " << endl;
//    network.PrintUnsortedNodeIDs(forwardNodeListOfOPDP);
//    cout << "Number of forwarding stations of OPDP is " << forwardNodeListOfOPDP.size() <<  endl;
//
//    cout << "Sequence of forward list of OTDP is " << endl;
//    network.PrintUnsortedNodeIDs(forwardNodeListOfOTDP);
//    cout << "Number of forwarding stations of OTDP is " << forwardNodeListOfOTDP.size() <<  endl;

    cout << "Sequence of forward list of CCADP is " << endl;
    network.PrintUnsortedNodeIDs(forwardNodeListOfCCADP);
    cout << "Number of forwarding stations of CCADP is " << forwardNodeListOfCCADP.size() <<  endl;
    cout << "Number of collision is " << numberOfCollisionOfCCADP <<  endl;
    cout << "Number of contention is " << numberOfContentionOfCCADP <<  endl;
//
//    cout << "Sequence of forward list of CCAPDP is " << endl;
//    network.PrintUnsortedNodeIDs(forwardNodeListOfCCAPDP);
//    cout << "Number of forwarding stations of CCAPDP is " << forwardNodeListOfCCAPDP.size() <<  endl;
//
//    cout << "Sequence of forward list of CCATDP is " << endl;
//    network.PrintUnsortedNodeIDs(forwardNodeListOfCCATDP);
//    cout << "Number of forwarding stations of CCATDP is " << forwardNodeListOfCCATDP.size() <<  endl;

// End Network configuration by manual input

// ********************** Run proactive protocols ****************************//
/*
    int minNodeNumber = 50;
    int maxNodeNumber = 250;
    int nodeInterval = 25;
    int runNumber = ((maxNodeNumber -  minNodeNumber) / nodeInterval) + 1;
    int nodeNumber = minNodeNumber;

    int networkLength = 1000;
    int networkWidth = 1000;
    int txRange = 250;

    int sourceNodeID = 1;

    ODP odp;
    odp.DataSheetOfODP();

//    OPDP opdp;
//    opdp.DataSheetOfOPDP();
//
//    OTDP otdp;
//    otdp.DataSheetOfOTDP();
//
//    CCADP ccadp;
//    ccadp.DataSheetOfCCADP();
//
//    CCAPDP ccapdp;
//    ccapdp.DataSheetOfCCAPDP();
//
//    CCATDP ccatdp;
//    ccatdp.DataSheetOfCCATDP();

    for (int r = 1 ; r <= runNumber; r++)
    {
        NetworkTopology networkTopology;
        Network network = networkTopology.TopologyConfigurationForNetwork(networkLength, networkWidth, nodeNumber, txRange);
        network.PrintNetwork();

        if(network.IsNetworkConnected() == true)
       {
            cout << "Result: Network is connected." << endl;

            vector<int> forwardNodeListOfODP = odp.RunODP(sourceNodeID, network);
            cout << "Sequence of forward list of ODP is " << endl;
            network.PrintUnsortedNodeIDs(forwardNodeListOfODP);
            cout << "Number of forwarding stations of ODP is " << forwardNodeListOfODP.size() <<  endl;
            odp.PerformanceMeasure(network);
            odp.DoDispose();

//            vector<int> forwardNodeListOfOPDP = opdp.RunOPDP(sourceNodeID, network);
//            cout << "Sequence of forward list of OPDP is " << endl;
//            network.PrintUnsortedNodeIDs(forwardNodeListOfOPDP);
//            cout << "Number of forwarding stations of OPDP is " << forwardNodeListOfOPDP.size() <<  endl;
//            opdp.PerformanceMeasure(network);
//            opdp.DoDispose();
//
//            vector<int> forwardNodeListOfOTDP = otdp.RunOTDP(sourceNodeID, network);
//            cout << "Sequence of forward list of OTDP is " << endl;
//            network.PrintUnsortedNodeIDs(forwardNodeListOfOTDP);
//            cout << "Number of forwarding stations of OTDP is " << forwardNodeListOfOTDP.size() <<  endl;
//            otdp.PerformanceMeasure(network);
//            otdp.DoDispose();
//
//            vector<int> forwardNodeListOfCCADP = ccadp.RunCCADP(sourceNodeID, network);
//            cout << "Sequence of forward list of CCADP is " << endl;
//            network.PrintUnsortedNodeIDs(forwardNodeListOfCCADP);
//            cout << "Number of forwarding stations of CCADP is " << forwardNodeListOfCCADP.size() <<  endl;
//            ccadp.PerformanceMeasure(network);
//            ccadp.DoDispose();
//
//            vector<int> forwardNodeListOfCCAPDP = ccapdp.RunCCAPDP(sourceNodeID, network);
//            cout << "Sequence of forward list of CCAPDP is " << endl;
//            network.PrintUnsortedNodeIDs(forwardNodeListOfCCAPDP);
//            cout << "Number of forwarding stations of CCAPDP is " << forwardNodeListOfCCAPDP.size() <<  endl;
//            ccapdp.PerformanceMeasure(network);
//            ccapdp.DoDispose();
//
//            vector<int> forwardNodeListOfCCATDP = ccatdp.RunCCATDP(sourceNodeID, network);
//            cout << "Sequence of forward list of CCATDP is " << endl;
//            network.PrintUnsortedNodeIDs(forwardNodeListOfCCATDP);
//            cout << "Number of forwarding stations of CCATDP is " << forwardNodeListOfCCATDP.size() <<  endl;
//            ccatdp.PerformanceMeasure(network);
//            ccatdp.DoDispose();
       }
        else
        {
          cout << "Result: Network is not connected." << endl;
        }
        nodeNumber = nodeNumber + nodeInterval;
    }
*/

    return 0;
}
