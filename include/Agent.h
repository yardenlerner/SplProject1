
#pragma once

#include <vector>
#include "Coalition.h"

using std::vector;
class SelectionPolicy;
class Coalition;
class Simulation;
class Party;
class Graph;


class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);
    // added constrctor
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy, int _coalitionId);
    //rule of five
    Agent(const Agent &other); // copy constructor 
    virtual ~Agent(); // destructor 
    Agent& operator=(const Agent &other); // copy assingment operator
    Agent(Agent&& other); // move constructor
    Agent& operator=(Agent&& other); // move assingment operator 

    int getPartyId() const;
    int getId() const;
    void step(Simulation &);

    //added methods

    int getCoalitionId();
    vector<int> *getOptionalPartys();
    SelectionPolicy* getSelectionPolicy();
    void initializingOptionalPartys(Graph &g);
    void setCoalition(int _coalitionId); 


private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy; 
    
    // added fields
 
    int coalitionId;
    vector<int> optionalPartys;

};
