#pragma once
#include <vector>
#include "Agent.h"
using std::vector;

class Simulation;

class JoinPolicy {
public:
    JoinPolicy(); //add arguments
    virtual ~JoinPolicy();
    virtual int chooseOffer(Simulation& sim)=0; //returns chosen agentID
    virtual void setOffer(int) = 0;//updates relevant fields when the party gets an offer
    virtual JoinPolicy* clonePolicy()=0;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
    MandatesJoinPolicy(); //add arguments
    virtual int chooseOffer(Simulation& sim); //returns chosen agentID
    virtual void setOffer(int); //updates myOffers list when the party gets an offer
    virtual JoinPolicy* clonePolicy();

    private:
        vector<int> myOffers;
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        LastOfferJoinPolicy(); //add arguments
        virtual int chooseOffer(Simulation& sim); //returns chosen agentID
        virtual void setOffer(int); //updates lastAgent when the party gets an offer
        virtual JoinPolicy* clonePolicy();


    private:
        int lastAgent; //ID of the last agent who made an offer

};