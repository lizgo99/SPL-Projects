#pragma once

#include <vector>

using std::vector;

class Coalition{
    public:
        Coalition(int id, int numOfMandates, int partyId);
        int getNumOfMandates() const;
        void setNumOfMandates(int numOfMandates);
        vector<int> &getCoalParties(); 
    
    private:
        int mId;
        int mNumOfMandates;
        vector<int> mCoalParties;
};
