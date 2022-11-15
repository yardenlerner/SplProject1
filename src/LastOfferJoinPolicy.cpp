#include "JoinPolicy.h"
#include <Party.h>
#include <vector>


using std::vector;

LastOfferJoinPolicy:: LastOfferJoinPolicy(){
    //empty constructor
}

Agent* LastOfferJoinPolicy::choose(Party &party , int agetId){

    //accessing the last agent 
    Agent *lastAgent = party.getmOffers().back();
    Agent *newAgent = new Agent(agetId , party.getId() ,(*lastAgent).getSelectionPolicy() , (*lastAgent).getCoalition());//save on heap

    //add party and agent to the coalition
     (*lastAgent).getCoalition()->addParty(&party);
     (*lastAgent).getCoalition()->addAgent(newAgent);

    return newAgent;
}