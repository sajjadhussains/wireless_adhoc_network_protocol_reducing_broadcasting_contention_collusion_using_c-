#ifndef LINK_H
#define LINK_H

using namespace std;

class Link
{
    public:

        int m_destinationNodeID;
        int m_cost;

        Link();
        Link(int destinationNodeID, int cost);
        void SetLinkCost(int destinationNodeID, int cost);
        void SetCost(int cost);
        int GetDestinationNodeID();
        int GetCost();

    protected:

    private:
};

#endif // LINK_H

