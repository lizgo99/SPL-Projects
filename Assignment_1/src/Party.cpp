#include "Party.h"
#include "../include/Simulation.h"

//Constructor
Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting), mTime(0), mOffers()
{
    
}

//Copy constructor
Party::Party(const Party &other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates),  mJoinPolicy(other.mJoinPolicy->clone()), mState(other.mState), mTime(other.mTime), mOffers(other.mOffers)
{
    
}

//Move Constructor
Party::Party(Party&& other) : mId(other.mId), mName(other.mName), mMandates(other.mMandates), mJoinPolicy(other.mJoinPolicy), mState(other.mState), mTime(other.mTime), mOffers(other.mOffers)
{
    other.mJoinPolicy=nullptr;
}

//Assignment operator
Party& Party::operator=(const Party & other)
{
    if(this!= &other)
    {
        delete mJoinPolicy;
        mJoinPolicy=other.mJoinPolicy->clone();
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;  
        mState = other.mState;
        mTime = other.mTime;
        mOffers = other.mOffers;
    }
    return *this;
}

//Move assignment operator
Party& Party::operator=(Party&& other)
{
    if(mJoinPolicy)
    {
        delete mJoinPolicy;
    }
    mJoinPolicy=other.mJoinPolicy;
    mId = other.mId;
    mName = other.mName;
    mMandates = other.mMandates;  
    mState = other.mState;
    mTime = other.mTime;
    mOffers = other.mOffers;

    other.mJoinPolicy=nullptr;
    return *this;
}

//Destructor
Party::~Party()
{
    if(mJoinPolicy)
    {
        delete mJoinPolicy;
    }
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

int Party::getTime() const
{
    return mTime;
}

void Party::setTime(int time) 
{
    mTime= time;
}

vector<Agent> &Party::getOffers()
{
    return mOffers;
}

bool Party::isNotSameCoalition(int CoalId)
{
    for(Agent& agent : mOffers)  
    {
        if (agent.getCoalId() == CoalId) 
        {
            return false;  // other agent from the same coallition select this party already.  
        }
        
    }
    return true; //there is NOT an agent of the same coalition so the agent can offer this party to join.
}


void Party::step(Simulation &s)
{
    if(mState == CollectingOffers) 
    {
        mTime += 1;  
        if(mTime == 3)
        {
            //clone the Agent
           Agent copyAgent((*mJoinPolicy).join(mOffers, s));    //the join function returns the agent that needs to be copied and than we create a copy by copy constructor
           copyAgent.setPartyId(mId);                           //updating the ParyId field of the copied Agent
           copyAgent.setId(s.getNonConstAgents().size());       //updating the ID field of the copied Agent
           copyAgent.setStatus(false);                          //making sure that the copy Agent is not Idle
           s.getNonConstAgents().push_back(copyAgent);          //adding the copied agent to the list of agents

           //updating the status of the party to "Joined" 
           setState(Joined);                             

           //updating the Coalition      
           int nCoalMandates = s.getVecCoalitions().at(copyAgent.getCoalId()).getNumOfMandates();
           s.getVecCoalitions().at(copyAgent.getCoalId()).setNumOfMandates(nCoalMandates + mMandates); //updating Coalition's number of mandates
           s.getVecCoalitions().at(copyAgent.getCoalId()).getCoalParties().push_back(mId); // adding the partyId to the Coalition. 
        }
    }
}
