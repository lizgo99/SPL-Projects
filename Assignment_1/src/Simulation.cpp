#include "Simulation.h"

Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), vCoalitions()
{
   for (uint i = 0; i < agents.size(); i++)
   {
    int numOfMandates = graph.getMandates(agents.at(i).getPartyId());
    vCoalitions.push_back(Coalition(i , numOfMandates , agents.at(i).getPartyId()));
    mAgents.at(i).setCoalId(i);
   }


   
}

void Simulation::step()  
{
        for (int i = 0; i < mGraph.getNumVertices(); i++)
        {
            getNonConstParty(i).step(*this);
        }
        for (uint j = 0; j < mAgents.size(); j++)
        {
            mAgents.at(j).step(*this);
        }
    
}

bool Simulation::shouldTerminate() const
{
    int sumOfAllMandates = 0;
    for (uint i = 0; i < vCoalitions.size(); i++)
    {
        int numOfMandates = vCoalitions.at(i).getNumOfMandates();
        if (numOfMandates > 60)
        {
            return true; // one of the coalitions has more than 61 mandates 
        }
        sumOfAllMandates += numOfMandates;  
    }
    if (sumOfAllMandates == 120)
    {
        return true; // non of the coalitions has more than 61 mandates and all of the parties joined a coalition
    } 
    return false; // simulation is NOT finished
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

vector<Agent> &Simulation::getNonConstAgents()
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

Party &Simulation::getNonConstParty(int partyId)
{
    return mGraph.getNonConstParty(partyId);
}

vector<Coalition> &Simulation::getVecCoalitions()
{
    return vCoalitions;
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> output; 
    for(Coalition coalition : vCoalitions)
    {
        output.push_back(coalition.getCoalParties());
    }    
    return output;
}
