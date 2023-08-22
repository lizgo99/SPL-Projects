#pragma once
#include <string>

using std::string;

class Simulation;

class SelectionPolicy 
{
    public:
        virtual int select(Simulation& sim, int partyId, int coalId) =0;
        virtual ~SelectionPolicy(){};
        virtual SelectionPolicy* clone()=0;
};

class MandatesSelectionPolicy : public SelectionPolicy
{ 
    public:
        int select(Simulation& sim, int partyId, int coalId);   
        SelectionPolicy* clone();
        ~MandatesSelectionPolicy(){};
};

class EdgeWeightSelectionPolicy : public SelectionPolicy
{ 
    public:
        int select(Simulation& sim, int partyId, int coalId); 
        SelectionPolicy* clone();
        ~EdgeWeightSelectionPolicy(){};
};