#pragma once
#include <vector>
#include <string>
#include "Agent.h"

using std::string;
using std::vector;

class JoinPolicy 
{ 
    public:
        virtual const Agent& join(const vector<Agent>& offers, Simulation& sim) =0;
        virtual JoinPolicy* clone()=0;
        virtual ~JoinPolicy() {};
};

class MandatesJoinPolicy : virtual public JoinPolicy 
{
    public:
        const Agent& join(const vector<Agent>& offers, Simulation& sim);
        JoinPolicy* clone();
        ~MandatesJoinPolicy() {};
};

class LastOfferJoinPolicy : virtual public JoinPolicy 
{
    public:
        const Agent& join(const vector<Agent>& offers, Simulation& sim);
        JoinPolicy* clone();
        ~LastOfferJoinPolicy() {};

};