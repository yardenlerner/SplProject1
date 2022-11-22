#include "SelectionPolicy.h"
#include "Party.h"
#include <vector>

using std::vector;

MandatesSelectionPolicy *MandatesSelectionPolicy::clone() const{
    return new MandatesSelectionPolicy(*this);
}

void MandatesSelectionPolicy:: choose(Agent *agent,Simulation& s){

    int maxMandates= 0;
    int idx= 0;
    vector <int> *optionalPartys = (*agent).getOptionalPartys();

    // finding the max mandates party
    int sizeOfoptionalPartys= (*optionalPartys).size();
    Graph *graph = s.getGraph();
    for(int i=0; i<sizeOfoptionalPartys; i++){
        
        Party *currParty = (*graph).getParty((*optionalPartys)[i]);
        int currMandates= (*currParty).getMandates();

        if(currMandates>= maxMandates){
            // checking by id 
                        
            if(currMandates== maxMandates){
                if((*optionalPartys)[idx]>(*currParty).getId()){
                    idx=i;
                }
            }
            // found a new max
            else{
                idx=i;
                maxMandates= currMandates;

            }
            
        }
    }

    Party *maxParty = (*graph).getParty((*optionalPartys)[idx]);
   
    (*maxParty).addAgent((*agent).getId()); // adds the agent to the party's offers
    
    s.getCoalition((*agent).getCoalitionId())->addOffer((*maxParty).getId()); // make party unavailable to select 
    (*optionalPartys).erase((*optionalPartys).begin() + idx); // removes the party ID from optional


}
