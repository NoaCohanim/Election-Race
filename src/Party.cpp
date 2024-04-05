
#include "Party.h"
#include "Simulation.h"

class Agent;

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting) ,timer(0),agentID(-1)
{

}

//rule of 5 
Party::~Party(){ //destructor
    if (mJoinPolicy) delete (mJoinPolicy);
}
//CopyConstructor
Party::Party(const Party & other):mId(other.mId), mName(other.mName),mMandates(other.mMandates),mJoinPolicy(other.mJoinPolicy->clonePolicy()), mState(other.mState),timer(other.timer),agentID(other.agentID) {}

//CopyOperator
Party& Party::operator=(const Party & other) {
    if (this != &other){
        mName = other.mName ;
        mMandates = other.mMandates ;
        mJoinPolicy = other.mJoinPolicy->clonePolicy();
        mState = other.mState;
        timer = other.timer;
        agentID = other.agentID;

    }
    return *this;
}

//MoveConstructor
Party::Party(Party && other):mId(other.mId), mName(other.mName),mMandates(other.mMandates),mJoinPolicy(other.mJoinPolicy), mState(other.mState),timer(other.timer),agentID(other.agentID)
{
other.mJoinPolicy = nullptr;
}

Party & Party::operator=(Party && other) //MoveOperator
{
mId = other.mId;
mName = other.mName;
mMandates = other.mMandates;
if (mJoinPolicy) delete mJoinPolicy;
mJoinPolicy = other.mJoinPolicy;
other.mJoinPolicy = nullptr;
mState = other.mState;
timer = other.timer;
agentID = other.agentID;

return *this;
}



State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string & Party::getName() const
{
    return mName;
}

JoinPolicy* Party::getJP(){
    return mJoinPolicy;
}

void Party::step(Simulation &s)
{
    if (mState == CollectingOffers)
    {
        timer++;
        if (timer == 3)
        {
            int joinTo = (*mJoinPolicy).chooseOffer(s);
            int coal = (s.getAgentsM())[joinTo].getCoalitionID();
            //int coal = (*s.getAgentsM())[joinTo].getCoalitionID();
            (s.getAgentsM())[joinTo].CloneNewAgent(s,mId);
            s.mCoalitions[coal].joinMandates(mMandates);//adds mandates to the coalition
            mState = Joined;
            s.addUnavailableNominees(mId);
            s.updateMaxMandates(s.mCoalitions[coal].getMandates());
            s.mCoalitions[coal].addParty(this);//adds party to the parties list of the coalition
            s.inc();
        }
    }
}
int Party::getPartyID() const {
    return mId;
}

int Party::getAgentId(){
    return agentID;
}

void Party::setAgentId(int id){
    agentID = id;
}

