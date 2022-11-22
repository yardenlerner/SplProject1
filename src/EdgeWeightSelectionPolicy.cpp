#include "SelectionPolicy.h"
#include <Party.h>
#include <vector>

using std::vector;

EdgeWeightSelectionPolicy* EdgeWeightSelectionPolicy::clone()const{
    return new EdgeWeightSelectionPolicy(*this);
}

void EdgeWeightSelectionPolicy:: choose(Agent *agent,Simulation& s){

    Graph *g = s.getGraph();

    vector<int> *optionalPartys = (*agent).getOptionalPartys();
    int maxWeigt=0;
    int idx=0;

    // finding the max weight
    int sizeOfOptionalPartys = (*optionalPartys).size();
    for(int i = 0; i<sizeOfOptionalPartys; i++){

        Party *currParty = (*g).getParty((*optionalPartys)[i]);
        int currEdge = (*g).getEdgeWeight((*currParty).getId(), (*agent).getPartyId());
        if( currEdge >= maxWeigt){
            // checking by id
            if(currEdge == maxWeigt){
               
                if((*currParty).getId()< (*optionalPartys)[idx])
                    idx = i;
                
            }
    
            // found a new max 
            else{
                idx = i;
                maxWeigt = currEdge;
            }
        }
    }

    Party *selectedParty= (*g).getParty((*optionalPartys)[idx]);

    

    (*selectedParty).addAgent( (*agent).getId()); // adds the agent to the party's offers ++ needs to change
    int  agentCoalitionId = (*agent).getCoalitionId();
    Coalition *agetCoalition = s.getCoalition(agentCoalitionId);
    int selectedPartyId = (*selectedParty).getId();
    
    (*agetCoalition).addOffer(selectedPartyId); // make party unavailable to select 
    
    (*optionalPartys).erase((*optionalPartys).begin() + idx); // removing the party from the vetor

}
