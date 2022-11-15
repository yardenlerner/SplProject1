#include "JoinPolicy.h"
#include <Agent.h>

#include <vector>
#include <Party.h>

using std::vector;

MandatesJoinPolicy:: MandatesJoinPolicy(){} // empty constructor

Agent* MandatesJoinPolicy::choose(Party &party , int agetId){
    // creates the duplicate agent for the coalitions
    Agent *maxAgnet = party.getMaxAgent();
    Agent *newAgent = new Agent(agetId , party.getId() ,(*maxAgnet).getSelectionPolicy() , (*maxAgnet).getCoalition()); // saves at heap
    
    //add party and agent to the coalition
     (*maxAgnet).getCoalition()->addParty(&party);
     (*maxAgnet).getCoalition()->addAgent(newAgent);
    

    return newAgent;
}

