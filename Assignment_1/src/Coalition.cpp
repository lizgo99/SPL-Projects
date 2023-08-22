#include "Coalition.h"

Coalition::Coalition(int id, int numOfMandates, int partyId) : mId(id), mNumOfMandates(numOfMandates), mCoalParties()
{
    mCoalParties.push_back(partyId);
}

int Coalition::getNumOfMandates() const
{
    return mNumOfMandates;
}

void Coalition::setNumOfMandates( int numOfMandates)
{
    mNumOfMandates = numOfMandates;
} 

vector<int> &Coalition::getCoalParties()
{
    return mCoalParties;
}

