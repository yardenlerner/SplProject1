#include "Agent.h"
#include <Party.h>
#include <Coalition.h>
#include <SelectionPolicy.h>

class Coalition;


Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy)
{
   
}

//added constructor
Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy, Coalition* coalition) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy) , mCoalition(coalition)
{
   
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

void Agent::step(Simulation &sim)
{
    // remove the already offerd party from the list
    bool *canOffer = (*mCoalition).getDidOffer();
    for(int i = optionalPartys.size() - 1; i>= 0; i--){
        if(canOffer[i]){
            optionalPartys.erase(optionalPartys.begin() + i);
        }
    }
    


    mSelectionPolicy->choose(this , sim);
}


// added methods
//**
//**

Coalition* Agent::getCoalition(){
    return mCoalition;
}

void  Agent::setCoalition(Coalition *coalition){
    mCoalition = coalition;
}

vector <Party*> Agent::getOptionalPartys(){
    return optionalPartys;
}

SelectionPolicy* Agent::getSelectionPolicy(){
    return mSelectionPolicy;
}


