#include "JoinPolicy.h"
#include <Party.h>
#include <vector>
#include <Simulation.h>


using std::vector;

LastOfferJoinPolicy* LastOfferJoinPolicy::clone()const{
    return new LastOfferJoinPolicy(*this);
}

int LastOfferJoinPolicy::choose(Party *party , Simulation &s){

    //accessing the last agent 
    int lastAgentId = (*(*party).getmOffers()).back();
    vector<Agent> *allAgents = s.getAgents();
    Agent lastAgent = (*allAgents)[lastAgentId];

    //add party and agent to the coalition
    Coalition *coalition = s.getCoalition(lastAgent.getCoalitionId());
     (*coalition).addParty(party->getId(), party->getMandates());
     
    return lastAgentId;
}