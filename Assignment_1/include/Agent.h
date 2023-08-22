#pragma once

#include <vector>
#include "Coalition.h"

class Simulation;
class SelectionPolicy;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    Agent(const Agent &other);
    Agent(Agent&& other);
    Agent& operator=(const Agent &other);
    Agent& operator=(Agent&& other);
    virtual ~Agent();

    int getPartyId() const;
    void setPartyId(int partyId);
    int getId() const;
    void setId(int AgentId);
    bool getStatus() const;
    void setStatus(bool status);
    int getCoalId() const;
    void setCoalId(int coalId);
    void step(Simulation &);


private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    int mCoalId;
    bool isIdle;
    
};
