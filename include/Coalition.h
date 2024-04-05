#pragma once
#include <vector>

using std::vector;
class Party;
class Agent;

class Coalition
{
public:
    Coalition (Party* party, int parties);
    Coalition ();
    int getMandates() const;
    void joinMandates(int mandates);
    void addParty(Party* party);
    vector<Party*>* getParties();
    void setOfferMade(int partyID);
    bool checkOfferMade(int partyID);


private:
    vector<bool> offersMade{};
    vector<Party*> parties{};
    int mandates;
};