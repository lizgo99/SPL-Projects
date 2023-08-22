#include "JoinPolicy.h"
#include "../include/Simulation.h"
#include <vector>

using std::vector;

const Agent& MandatesJoinPolicy::join(const vector<Agent>& offers, Simulation& sim)
{
    // decide the agent in the coalition with the most mandates
    int maxMandates = 0;
    int AgentIndex = -1;
    for (uint i = 0; i < offers.size(); i++) // iterate over the offers
    {   
        int numOfMandatesInCoalition = sim.getVecCoalitions().at(offers.at(i).getCoalId()).getNumOfMandates(); 
        if(numOfMandatesInCoalition > maxMandates)
        {
            maxMandates = numOfMandatesInCoalition;
            AgentIndex = i;
        }
    }
    return offers.at(AgentIndex); 
}

//clone function for the rule of 5
JoinPolicy* MandatesJoinPolicy::clone()
{
    return new MandatesJoinPolicy(*this);
}

const Agent& LastOfferJoinPolicy::join(const vector<Agent>& offers, Simulation& sim) 
{
    return offers.back(); 
}

//clone function for the rule of 5
JoinPolicy* LastOfferJoinPolicy::clone(){
    return new LastOfferJoinPolicy(*this);
}
