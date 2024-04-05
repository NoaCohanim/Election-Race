
#include "Agent.h"
#include "Simulation.h"

Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : coalition(-1),mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy), nominees(vector<Party*>{})
{}

//destructor
Agent::~Agent () {
    if (mSelectionPolicy) delete mSelectionPolicy;
}

//CopyConstructor
Agent::Agent(const Agent & other) : coalition(other.coalition),mAgentId(other.mAgentId),mPartyId(other.mPartyId),mSelectionPolicy(other.mSelectionPolicy->clonePolicy()), nominees(other.nominees)
{}

//MoveConstractor
Agent::Agent (Agent && other):coalition(other.coalition),mAgentId(other.mAgentId),mPartyId(other.mPartyId),mSelectionPolicy(other.mSelectionPolicy), nominees(other.nominees) {
    other.mSelectionPolicy = nullptr;
}

//CopyAssignmentOperator
Agent& Agent::operator=(const Agent & other)
{
    if (this!=&other){
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        coalition = other.coalition;
        mSelectionPolicy = other.mSelectionPolicy->clonePolicy(); //creates a deep copy of selection policy based on it's type using polymorphism
        nominees = other.nominees;
    }
    return *this;
} 

Agent & Agent::operator=(Agent && other) {//MoveAssignmentOperator
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    nominees = other.nominees;
    coalition = other.coalition;
    if(mSelectionPolicy) delete mSelectionPolicy;
    mSelectionPolicy = other.mSelectionPolicy;//->clonePolicy();
    other.mSelectionPolicy = nullptr;
    
    return *this;
}

void Agent::CloneNewAgent(Simulation& s, int partyID){ //for new agents of new joined parties
    int newID = s.getAgentsM().size(); //the Id of an agent is it's position in the vector
    Agent newAgent (*this); //calls copy constructor
    newAgent.mAgentId = newID;
    newAgent.mPartyId = partyID;
    s.getPartyM(partyID).setAgentId(newID);
    newAgent.setNominees(s.getGraphM().getNeigs(partyID));
    newAgent.getSP()->setPartyID(partyID);
    newAgent.getSP()->select(*(newAgent.getNominees()),s.getGraph());
    s.getAgentsM().push_back(newAgent);
}


int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim)
{

    int size = nominees.size();
    while ((size > 0) && (((sim.mCoalitions[coalition].checkOfferMade(nominees[0]->getPartyID())) || (sim.checkUnavailableNominees(nominees[0]->getPartyID())))))
    //check if the party is relevant (is not in state "Joind" and didn't get an offer from my coalition yet)
    {
        nominees.erase(nominees.begin());
        size--;
    }
    if (nominees.size() > 0)
    {
        Party* chosenParty = nominees.front();
        nominees.erase(nominees.begin());
        chosenParty->setState(CollectingOffers);
        chosenParty->getJP()->setOffer(this->getId()); //adds me to the party's offers list
        sim.mCoalitions[coalition].setOfferMade(chosenParty->getPartyID());//so no agent from my coalition will offer the same party
    }
    
}

void Agent::setNominees(vector<Party*> nomi){
    nominees = nomi;
}

vector<Party*>* Agent::getNominees() {
    return &nominees;
}

 SelectionPolicy* Agent::getSP() {
    return mSelectionPolicy;
}


int Agent::getCoalitionID(){
    return coalition;
}

void Agent::setCoalitionID(int id){
    coalition = id;
}


