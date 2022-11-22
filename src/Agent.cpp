#include "Agent.h"
#include <iostream>
#include <SelectionPolicy.h>
using std::vector;

class Coalition;


Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy) , coalitionId(0) , optionalPartys()
{
   
}

//added constructor
Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy, int _coalitionId) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy) , coalitionId(_coalitionId) , optionalPartys()
{
   
}

// copy constructor
Agent::Agent(const Agent &other): mAgentId(other.getId()) ,mPartyId(other.getPartyId()), mSelectionPolicy(other.mSelectionPolicy->clone()), coalitionId(other.coalitionId), optionalPartys() {
    int sizeOfOptionalPartys= other.optionalPartys.size();
    for(int i=sizeOfOptionalPartys-1; i>=0; i--)
        optionalPartys.push_back(other.optionalPartys[i]);
}

 // copy assingment operator
Agent& Agent::operator=(const Agent &other){
    if(this != &other){
        optionalPartys.clear();

        mAgentId= other.getId();
        mPartyId= other.getPartyId();
        *mSelectionPolicy= *other.mSelectionPolicy;
        coalitionId= other.coalitionId;

        int sizeOfOptionalPartys= other.optionalPartys.size();

        for(int i= sizeOfOptionalPartys-1; i>=0; i--)
            optionalPartys.push_back(other.optionalPartys[i]);
    }
    return *this;
} 

Agent:: ~Agent(){ // destructor
    if (mSelectionPolicy) delete mSelectionPolicy;
} 

// move constructor
Agent :: Agent(Agent&& other) : mAgentId(other.getId()) ,mPartyId(other.getPartyId()), mSelectionPolicy(other.mSelectionPolicy->clone()), coalitionId(other.coalitionId), optionalPartys() {// move constructor
    
    int sizeOfOptionalPartys= other.optionalPartys.size();
    for(int i=sizeOfOptionalPartys-1; i>=0; i--)
        optionalPartys.push_back(other.optionalPartys[i]);
    
    other.optionalPartys.clear();
    other.mSelectionPolicy=nullptr;

}

Agent& Agent::operator=(Agent&& other){ // move assingment operator 

    optionalPartys.clear();

    mAgentId= other.getId();
    mPartyId= other.getPartyId();
    coalitionId= other.coalitionId;
    int sizeOfOptionalPartys= other.optionalPartys.size();

    if(mSelectionPolicy) delete mSelectionPolicy;
    mSelectionPolicy= other.mSelectionPolicy;
    other.mSelectionPolicy=nullptr;

    for(int i= sizeOfOptionalPartys-1; i>=0; i--)
        optionalPartys.push_back(other.optionalPartys[i]);
    
    // deleting other resources
    other.optionalPartys.clear();

    return *this;

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
    Coalition *mCoalition = sim.getCoalition(coalitionId); 
    bool *canOffer = (*mCoalition).getDidOffer();
    int optionalPartysSize = optionalPartys.size() - 1;
    for(int i = optionalPartysSize; i>= 0; i--){
        bool a = (&canOffer)[i];
        if(a!=true){
            optionalPartys.erase(optionalPartys.begin() + i);
        }
    }
    
    if(optionalPartys.size() > 0)
        mSelectionPolicy->choose(this , sim);
}


// added methods
//**
//**

int Agent::getCoalitionId(){
    return coalitionId;
}

void  Agent::setCoalition(int _coalitionId){
    coalitionId = _coalitionId;
}


vector <int> *Agent::getOptionalPartys(){
    return &optionalPartys;
}

SelectionPolicy* Agent::getSelectionPolicy(){
    return mSelectionPolicy;
}

 void Agent::initializingOptionalPartys(Graph &g){
    int numVertices = g.getNumVertices();
        for(int i=0; i<numVertices; i++){
            if(g.getEdgeWeight(mPartyId,i)>0){
                Party *newOptionalParty = g.getParty(i);
                if((*newOptionalParty).getState() != Joined){
                    int partyId = (*newOptionalParty).getId();
                    optionalPartys.push_back(partyId);
                }
            }
        }
 }


