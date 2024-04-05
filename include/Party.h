#pragma once
#include <string>
#include <JoinPolicy.h>


using std::string;
class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 

    //rule of 5
    virtual ~ Party(); //Destructor
    Party(const Party & other); //CopyConstructor
    Party(Party && other) ; //MoveConstructor
    Party & operator=(const Party & other);///CopyAssignment
    Party & operator=(Party && other) ;//MoveAssignment

    void step(Simulation &s);

    //setters
    void setAgentId(int id);

    //getters
    const string &getName() const;
    JoinPolicy* getJP();
    int getAgentId();
    State getState() const;
    int getPartyID() const;
    void setState(State state);
    int getMandates() const;


private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int timer;
    int agentID;
};
