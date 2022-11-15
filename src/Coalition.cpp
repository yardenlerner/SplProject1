#include "Coalition.h"
#include <Graph.h>

#include <vector>

using std::vector;

Coalition :: Coalition(){
}

Coalition :: Coalition(Graph graph, Agent agent){
    
    *didOffer  = new bool [graph.getNumVertices()];
    mAgents.push_back(&agent);
    numOfMandates= graph.getParty(agent.getPartyId())->getMandates();

}

vector<Party*> *Coalition::getMpartys(){
    return &mPartys;
}
vector<Agent*> *Coalition::getMagents(){
    return &mAgents;
    
}


bool *Coalition::getDidOffer (){
    return didOffer;
}

void Coalition::addParty(Party* newParty){
    mPartys.push_back(newParty);
    numOfMandates = numOfMandates + (*newParty).getMandates();
}

void Coalition::addAgent(Agent* newAgent){
    mAgents.push_back(newAgent);
}

void Coalition::addOffer(int paryId){
    didOffer[paryId] = true;
}


