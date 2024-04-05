
#include "Simulation.h"
#include "SelectionPolicy.h"
//class Party;
//class Agent;


Simulation::Simulation(Graph graph, vector <Agent> agents) : mCoalitions(vector<Coalition>{}),mGraph(graph), mAgents(agents),joinedCounter(0),CoalMaxMandates(0),parties(0) {
    parties = mGraph.getNumVertices();
    for (int i = 0; i < parties; i++) //inits unavailable nominees
        unavailableNominees.push_back(false);
    for (Agent &a: mAgents) {
        unavailableNominees[a.getPartyId()] = true; //1. filling unavailable nominees
        a.setNominees(mGraph.getNeigs(a.getPartyId())); //2.completing init of agents and their selection policy
        mGraph.getPartyM(a.getPartyId())->setAgentId(a.getId()); //sets agent id for the relevant parties
        a.getSP()->setPartyID(a.getPartyId());
        a.getSP()->select(*(a.getNominees()), mGraph); //sorting nominees of each agent
        mCoalitions.push_back(Coalition(mGraph.getPartyM(a.getPartyId()), parties));
        a.setCoalitionID(a.getId());
        joinedCounter++;
        int curMand = mGraph.getParty(a.getPartyId()).getMandates();
        if (curMand>=CoalMaxMandates) {
            CoalMaxMandates = curMand;
        }
    }
}


void Simulation::step() {

    //applying party step
    for (int i = 0; i < parties; i++) {
        mGraph.getPartyM(i)->step(*this);
    }

    //applying agent step
    int size = mAgents.size();
    for (int i=0; i<size;i++) {
        (mAgents[i]).step(*this);
    }

}

bool Simulation::checkUnavailableNominees(int PartyID) {
    return unavailableNominees[PartyID];

}

void Simulation::addUnavailableNominees(int PartyID) {
    unavailableNominees[PartyID] = true;
}

bool Simulation::shouldTerminate() const {
    if (((parties>0)&(joinedCounter == parties)) || (CoalMaxMandates > 60))
        return true;
    return false;


}

const Graph &Simulation::getGraph() const {
    return mGraph;
}

Graph &Simulation::getGraphM()  {
    return mGraph;
}

const vector <Agent> &Simulation::getAgents() const {
    return mAgents;
}

vector <Agent>& Simulation::getAgentsM() {
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const {
    return mGraph.getParty(partyId);
}

Party& Simulation::getPartyM(int partyId) {
    return *(mGraph.getPartyM(partyId));
}

void Simulation::updateMaxMandates(int mandates) {
    if (CoalMaxMandates < mandates) {
        CoalMaxMandates = mandates;
    }
}


/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector <vector<int>> Simulation::getPartiesByCoalitions() const {
    vector <vector<int>> output{};
    for (Coalition c: mCoalitions) { //iterating through the coalitions
        vector<int> x;
        for (Party *p: *(c.getParties())) { //adds the parties to the coalition's vector
            x.push_back(p->getPartyID());
        }
        output.push_back(x);
    }
    return output;
}

void Simulation::inc() {
    joinedCounter++;
}

