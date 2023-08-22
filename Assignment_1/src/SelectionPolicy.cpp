#include "SelectionPolicy.h"
#include "../include/Simulation.h"
#include <vector>

using std::vector;

int MandatesSelectionPolicy::select(Simulation& sim, int partyId, int coalId)
{
    int maxNumOfMandates = -1;
    int partyIndex = -1;

    for(int i = 0; i < sim.getGraph().getNumVertices(); i++)    // iterate over the vertecies
    {
        if (sim.getGraph().getEdgeWeight(partyId, i) > 0                      //Condition 1- if the weight > 0 means the parties are neighbors
            && (sim.getParty(i).getState() == Waiting                         //Condition 2- Checking if the status of the party is Waiting or Collecting Offers.
            || sim.getParty(i).getState() == CollectingOffers)
            && sim.getNonConstParty(i).isNotSameCoalition(coalId))      //Condition 3- Checking if the party wasn't prompted by other agent in the same coallition.
        {
            if (sim.getGraph().getMandates(i) > maxNumOfMandates)
            {
                maxNumOfMandates = sim.getGraph().getMandates(i);            // if the number of mandates is greater, save it and save the partyId of the same party
                partyIndex = i;
            }   
        }    
    } 
    return partyIndex;
}

//clone function for the rule of 5
SelectionPolicy* MandatesSelectionPolicy::clone(){
    return new MandatesSelectionPolicy(*this);
}

int EdgeWeightSelectionPolicy::select(Simulation& sim, int partyId, int coalId)
{
    int maxWeight = -1;
    int partyIndex = -1;

    for(int i = 0; i < sim.getGraph().getNumVertices(); i++) // iterate over the vertecies
    {
        int edgeWeight = sim.getGraph().getEdgeWeight(partyId, i);
        if (edgeWeight > 0                                             //Condition 1- if the weight > 0 means the parties are neighbors
            && (sim.getParty(i).getState() == Waiting                  //Condition 2- Checking if the status of the party is Waiting or Collecting Offers.
            || sim.getParty(i).getState() == CollectingOffers)
            && sim.getNonConstParty(i).isNotSameCoalition(coalId))     //Condition 3- Checking if the party wasn't prompted by other agent in the same coallition.
        {
            if (edgeWeight > maxWeight)
            {
                maxWeight = edgeWeight;
                partyIndex = i;
            }   
        } 
    }
    return partyIndex;
}

//clone function for the rule of 5
SelectionPolicy* EdgeWeightSelectionPolicy::clone(){
    return new EdgeWeightSelectionPolicy(*this);
}
