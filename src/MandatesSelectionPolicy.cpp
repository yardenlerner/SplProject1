#include "SelectionPolicy.h"
#include "Party.h"
#include <vector>

using std::vector;

MandatesSelectionPolicy:: MandatesSelectionPolicy(){
    // empty constructor
}

void MandatesSelectionPolicy:: choose(Agent *agent,Simulation& s){

    int maxMandates= 0;
    int idx= 0;
    vector <Party*> optionalPartys = (*agent).getOptionalPartys();

    // finding the max mandates party
    for(int i=0; i< optionalPartys.size(); i++){
        int currMandates= (*optionalPartys[i]).getMandates();

        if(currMandates>= maxMandates){
            // checking by id 
            if(currMandates== maxMandates){
                if((*optionalPartys[idx]).getId()>(*optionalPartys[i]).getId()){
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

    Party selectedParty= (*optionalPartys[idx]);
    selectedParty.addAgent(agent, (*agent).getId()); // adds the agent to the party's offers
    (*agent).getCoalition()->addOffer(selectedParty.getId()); // make party unavailable to select 
    optionalPartys.erase(optionalPartys.begin() + idx); // need to check if its a copy or a pointer !!!!!!!!!!!!


}
