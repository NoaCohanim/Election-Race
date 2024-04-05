#pragma once

#include <vector>
#include "Coalition.h"
#include "SelectionPolicy.h"

using std::vector;
class Simulation;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    void step(Simulation &);
    void CloneNewAgent(Simulation& s,int party);
    //vector<Party*> cloneNominees() const;


    //ruleOf5
    virtual ~ Agent(); //Destructor
    Agent(const Agent & other); //CopyConstructor
    Agent(Agent && other); //MoveConstructor
    Agent & operator=(const Agent & other);///CopyAssignment
    Agent & operator=(Agent && other);//MoveAssignment

    //getters
    int getPartyId() const;
    int getId() const;
    vector<Party*>* getNominees();
    SelectionPolicy* getSP();
    int getCoalitionID();


    //setters
    void setNominees(vector<Party*> nomi);
    void setCoalitionID(int id); //check if needed



private:
    int coalition;
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    vector<Party*> nominees;
    
};
