
#include "Coalition.h"
#include "Party.h"
#include "Agent.h"

Coalition::Coalition() : mandates(-1)  {
}
Coalition::Coalition(Party* party, int partiesSum) :  mandates(party->getMandates())
{
    for (int i=0; i<partiesSum; i++) {
        offersMade.push_back(false);
    }
    this->addParty(party); //adds the first party to the coalition
}

int Coalition::getMandates() const
{
    return mandates;
}

void Coalition::joinMandates(int toAddMandates)
{
    mandates = mandates+ toAddMandates;
}
void Coalition::addParty(Party* party) {
    parties.push_back(party);

}
vector<Party*>* Coalition::getParties() {
    return &parties;

}

void Coalition::setOfferMade(int partyID){
    offersMade[partyID] = true;
}

bool Coalition::checkOfferMade(int partyID){
    return offersMade[partyID];
}