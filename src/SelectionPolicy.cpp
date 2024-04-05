#include "SelectionPolicy.h"
#include "Party.h"
#include "Graph.h"
#include <vector>
using  std::vector;

SelectionPolicy::SelectionPolicy() : myAgentPartyID(-1) {
}
SelectionPolicy::~SelectionPolicy() {}

SelectionPolicy::SelectionPolicy(int id) : myAgentPartyID(id) {
}
void SelectionPolicy::setPartyID(int id) {
    myAgentPartyID = id;
}
int SelectionPolicy::getPartyID(){
    return myAgentPartyID;
}
void SelectionPolicy::select(vector<Party*>& neigs, const Graph& g) { //sorts the list of nominees by the relevant category (mandates\edges) and returns it
    int size = neigs.size();
    for (int j=0; j<size; j++) {
        int maxIndex = maxIndexFinder(neigs, g, j);
        Party* key = neigs[maxIndex];
        while (maxIndex > j){ //in place sorting
            neigs[maxIndex] = neigs[maxIndex-1];
            maxIndex--;
        }
        neigs[j] = key;

    }
}

EdgeWeightSelectionPolicy::EdgeWeightSelectionPolicy() {}
EdgeWeightSelectionPolicy::EdgeWeightSelectionPolicy(int id) : SelectionPolicy(id) {}


int EdgeWeightSelectionPolicy::maxIndexFinder (vector<Party*>& nominees, const Graph& g, int start) {
    int maxIndex=start;
    int size = nominees.size();
    for (int i=start; i<size; i++) {
        int wMaxIndex = g.getEdgeWeight(this->getPartyID(), nominees[maxIndex]->getPartyID()); //current max weight index
        int wi = g.getEdgeWeight(this->getPartyID(), nominees[i]->getPartyID()); //current weight index
        if (wi > wMaxIndex) {
            maxIndex=i;
        }
    }
    return maxIndex;
}

SelectionPolicy* EdgeWeightSelectionPolicy::clonePolicy() {
    EdgeWeightSelectionPolicy* x = new EdgeWeightSelectionPolicy (this->getPartyID());
    return x;
}

MandatesSelectionPolicy::MandatesSelectionPolicy() {}

MandatesSelectionPolicy::MandatesSelectionPolicy(int id) : SelectionPolicy(id) {}

SelectionPolicy* MandatesSelectionPolicy::clonePolicy() {

    MandatesSelectionPolicy* x = new MandatesSelectionPolicy(this->getPartyID());
    return x;
}


int MandatesSelectionPolicy::maxIndexFinder (vector<Party*>& nominees, const Graph& g, int start) {
    int maxIndex=start;
    int size = nominees.size();
    for (int i=start; i<size; i++) {
        int mi = nominees[i]->getMandates(); //current mandates index
        int mMaxIndex = nominees[maxIndex]->getMandates(); //current max mandates index
        if (mi > mMaxIndex) {
            maxIndex=i;
        }
    }
    return maxIndex;
}








