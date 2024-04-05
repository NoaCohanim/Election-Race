#pragma once

#include <vector>
#include <string>
#include "Agent.h"
#include "Graph.h"
#include "Party.h"
#include "Coalition.h"


using std::string;
using std::vector;




class Simulation
{
public:
    vector<Coalition> mCoalitions;
    Simulation(Graph g, vector<Agent> agents);
    void step();
    bool shouldTerminate() const;
    void inc();
    bool checkUnavailableNominees(int PartyID) ;
    void addUnavailableNominees(int PartyID) ;
    void updateMaxMandates(int mandates);

    //getters
    const Graph &getGraph() const;
    Graph &getGraphM();
    const vector<Agent> &getAgents() const;
    vector<Agent> &getAgentsM();
    const Party &getParty(int partyId) const;
    Party &getPartyM(int partyId);
    const vector<vector<int>> getPartiesByCoalitions() const;


private:
    Graph mGraph;
    vector<Agent> mAgents;
    int joinedCounter;
    int CoalMaxMandates;
    int parties;
    vector<bool> unavailableNominees{};
    
};