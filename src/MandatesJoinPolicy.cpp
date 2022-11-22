#include "JoinPolicy.h"
#include <Agent.h>

#include <vector>
#include <Party.h>
#include <Simulation.h>

using std::vector;

MandatesJoinPolicy* MandatesJoinPolicy::clone()const{
    return new MandatesJoinPolicy(*this);
}


int MandatesJoinPolicy::choose(Party *party , Simulation &s){
    //finding the maxMandate Agent
    int maxMandates=0;
    int maxIndx=0;
    vector<int> *mOffers = (*party).getmOffers();
    int mOffersSize = (*mOffers).size();
    vector<Agent> *agents = s.getAgents();
    for(int i = 0; i<mOffersSize; i++){
        Agent currAgent = (*agents)[i];
        Coalition *coalition = s.getCoalition(currAgent.getCoalitionId());
        int currMandates = coalition->getMandetes();
        if(currMandates>= maxMandates){
            if(currMandates == maxMandates ){//needs to check by party id
                int maxAgentId = (*mOffers)[maxIndx];
                Agent maxAgent = (*agents)[maxAgentId];
                if(maxAgent.getPartyId()>currAgent.getPartyId()){
                    maxIndx = i;
                }
            }

            else{ // regular state
                maxMandates = currMandates;
                maxIndx = i;
            }
        }
    }

    int maxAgentId = (*mOffers)[maxIndx];
    Agent maxAgent = (*agents)[maxAgentId];

    //add party  to the coalition
    Coalition *coalition = s.getCoalition(maxAgent.getCoalitionId());
    (*coalition).addParty(party->getId(), party->getMandates());
        
    return maxAgentId;
}

