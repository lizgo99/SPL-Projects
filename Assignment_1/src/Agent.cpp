#include "Agent.h"
#include "SelectionPolicy.h"
#include "../include/Simulation.h"

//Constructor
Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy), mCoalId(-1), isIdle(false) 
{
    
}

//Copy constructor
Agent::Agent(const Agent &other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy->clone()), mCoalId(other.mCoalId), isIdle(other.isIdle)
{
   
}

//Move Constructor
Agent::Agent(Agent&& other) : mAgentId(other.mAgentId), mPartyId(other.mPartyId), mSelectionPolicy(other.mSelectionPolicy), mCoalId(other.mCoalId), isIdle(other.isIdle)
{
    other.mSelectionPolicy=nullptr;
}

//Assignment operator
Agent& Agent::operator=(const Agent& other)
{
    if(this != &other)
    {
        delete mSelectionPolicy;
        mSelectionPolicy = other.mSelectionPolicy->clone(); 
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        mCoalId = other.mCoalId;
        isIdle = other.isIdle;

    }
    return *this;
}

//Move assignment operator
Agent& Agent::operator=(Agent&& other)
{
    if(mSelectionPolicy)
    {
        delete mSelectionPolicy;
    }
    mSelectionPolicy = other.mSelectionPolicy; 
    mAgentId = other.mAgentId;
    mPartyId = other.mPartyId;
    mCoalId = other.mCoalId;
    isIdle = other.isIdle;
    
    other.mSelectionPolicy=nullptr;
    return *this;
}

//Destructor
Agent:: ~Agent()
{
    if(mSelectionPolicy){
        delete mSelectionPolicy;
    }
}


int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::setPartyId(int partyId)
{
    mPartyId = partyId;
}

int Agent::getId() const
{
    return mAgentId;
}

void Agent::setId(int AgentId)
{
    mAgentId = AgentId;
}

bool Agent::getStatus() const
{
    return isIdle;
}

void Agent::setStatus(bool status)
{
    isIdle=status;
}

int Agent::getCoalId() const
{
    return mCoalId;
}

void Agent::setCoalId(int coalId)
{
    mCoalId = coalId;
}

void Agent::step(Simulation &sim)   
{
    if (isIdle == false) 
    {
        int selectedPartyId = (*mSelectionPolicy).select(sim, mPartyId, mCoalId); // Activating select. returns the partyId of the party the agent selected

        if (selectedPartyId == -1)   //there are no more parties to the agent can ask to join to his coalition
        {
            isIdle = true;
        }
        else{
            if (sim.getParty(selectedPartyId).getState() == Waiting) // if the state of the selected party was Waiting -> change it to Collecting Offers
            {
                sim.getNonConstParty(selectedPartyId).setState(CollectingOffers);  
            }
        
            sim.getNonConstParty(selectedPartyId).getOffers().push_back(*this); // Adding the agent to the vector of offers of the party
            
        }
    }
}

