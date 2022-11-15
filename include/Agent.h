#pragma once

#include <vector>
#include "Coalition.h"


class SelectionPolicy;
class Coalition;
class Simulation;

class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    // added constrctor
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy, Coalition *coalition);

    int getPartyId() const;
    int getId() const;
    void step(Simulation &);
    //added methods
    Coalition* getCoalition(); 
    void setCoalition(Coalition *coalition); 
    vector <Party*> getOptionalPartys(); 
    SelectionPolicy* getSelectionPolicy();


private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    // added fields
    Coalition *mCoalition; 
    vector <Party*> optionalPartys; 

};
