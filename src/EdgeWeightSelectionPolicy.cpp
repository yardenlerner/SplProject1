#include "SelectionPolicy.h"
#include <Party.h>
#include <vector>

using std::vector;

EdgeWeightSelectionPolicy:: EdgeWeightSelectionPolicy(){
    // empty constructor
}

void EdgeWeightSelectionPolicy:: choose(Agent *agent,Simulation& s){

    Graph g = s.getGraph();

    vector<Party*> optionalPartys = (*agent).getOptionalPartys();
    int maxWeigt=0;
    int idx;

    // finding the max weight
    for(int i = 0; i<optionalPartys.size(); i++){

        int currEdge = g.getEdgeWeight((*optionalPartys[i]).getId(), (*agent).getPartyId());
        if( currEdge >= maxWeigt){
            // checking by id
            if(currEdge == maxWeigt){

                if((*optionalPartys[i]).getId()< (*optionalPartys[idx]).getId())
                    idx = i;
                
            }
    
            // found a new max 
            else{
                idx = i;
                maxWeigt = currEdge;
            }
        }
    }

    Party selectedParty= (*optionalPartys[idx]);
    selectedParty.addAgent(agent, (*agent).getId()); // adds the agent to the party's offers
    (*agent).getCoalition()->addOffer(selectedParty.getId()); // make party unavailable to select 
    optionalPartys.erase(optionalPartys.begin() + idx); // need to check if its a copy or a pointer !!!!!!!!!!!!

}
