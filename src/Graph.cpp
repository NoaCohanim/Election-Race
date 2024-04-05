
#include "Graph.h"
#include <vector>
using namespace std;

Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges) 
{
    // You can change the implementation of the constructor, but not the signature!
}

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}

int Graph::getNumVertices() const
{
    return mVertices.size();
}

const Party &Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}


Party* Graph::getPartyM(int partyId)
{
    return &mVertices[partyId];
}   

vector<Party*> Graph:: getNeigs(int partyID)
{
    vector<Party*> neighs;
    int size = mEdges[partyID].size();
    for (int i=0; i<size; i++) {
        if (mEdges[partyID][i] >0)
            neighs.push_back(getPartyM(i));
        }
        
    return neighs;
}
