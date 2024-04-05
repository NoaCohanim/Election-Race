
#include "JoinPolicy.h"
#include "Simulation.h"

JoinPolicy::JoinPolicy(){}
JoinPolicy::~JoinPolicy(){}
MandatesJoinPolicy::MandatesJoinPolicy() : myOffers(vector<int>{})
{
}
LastOfferJoinPolicy::LastOfferJoinPolicy() : lastAgent(-1)
{}


int MandatesJoinPolicy::chooseOffer(Simulation &sim)
{

    int chosen = myOffers[0];

    int maxMandates =sim.mCoalitions[sim.getAgentsM()[myOffers[0]].getCoalitionID()].getMandates();;
    int size = myOffers.size();
    for (int i = 1; i < size; i++)
    {
        int currMandates= sim.mCoalitions[sim.getAgentsM()[myOffers[i]].getCoalitionID()].getMandates();;
        if (currMandates > maxMandates)
        {
            chosen=myOffers[i];
            maxMandates = currMandates;
        }
    }
    return chosen;
}



JoinPolicy* MandatesJoinPolicy::clonePolicy()
{
    MandatesJoinPolicy* x = new MandatesJoinPolicy();
    x->myOffers = this->myOffers;
    return x;
}

JoinPolicy* LastOfferJoinPolicy::clonePolicy()
{
    LastOfferJoinPolicy* x = new LastOfferJoinPolicy();
    x->lastAgent = this->lastAgent;
    return x;
}


void MandatesJoinPolicy::setOffer(int agentOfferd){
    myOffers.push_back(agentOfferd);
}

int LastOfferJoinPolicy::chooseOffer(Simulation&) {
    return lastAgent;
}

void LastOfferJoinPolicy::setOffer(int agentOfferd){
    lastAgent = agentOfferd;
}
