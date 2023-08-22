#pragma once
#include <string>
#include <vector>
#include "Agent.h"
#include "JoinPolicy.h"

using std::string;
using std::vector;


class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 
    Party(const Party &other);
    Party(Party&& other);
    Party& operator=(const Party & other);
    Party& operator=(Party&& other);
    virtual ~Party();
    

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    int getTime() const;
    void setTime(int time); 
    vector<Agent> &getOffers();
    const string &getName() const;
    bool isNotSameCoalition(int CoalId); 
    

private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    int mTime;
    vector<Agent> mOffers;
};
