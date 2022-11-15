#include "Simulation.h"
#include <Agent.h>
#include <iostream>
#include <vector>
#include <Coalition.h>
#include <Graph.h>

using namespace std;


Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) 
{
    // You can change the implementation of the constructor, but not the signature!
}

void Simulation::step()
{
    if(!isInitialized){
        // creating coalition from the list of agents
        for(int i=0; i < mAgents.size(); i++){
            Coalition *newCoalition = new Coalition(mGraph , mAgents[i]);  // saves at heap
            addCoalition(newCoalition);
            mAgents[i].setCoalition(newCoalition);
        }

        isInitialized = true;
    }
    // making step for each party in the Graph.vertics
    for(int i=0; i < mGraph.getNumVertices(); i++){
        Party *curr = mGraph.getParty(i);
        (*curr).step(*this);
    }


    //making step for each agent in mAgents
    for(int i=0; i < mAgents.size(); i++){
        Agent curr = mAgents[i];
        curr.step(*this);
    }


}

bool Simulation::shouldTerminate() const
{
    
    return ((maxMandates>=61) | (numOfJoinedPartys == mGraph.getNumVertices()));
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

//added methods
//**
//**

void Simulation::addDuplicate(Agent *duplicate){
    mAgents.push_back((*duplicate));
}

void Simulation::addCoalition(Coalition *coalition){
    allCoalition.push_back(coalition);
}

void Simulation::setMaxMandates(int _maxMandates){
    if(maxMandates<_maxMandates)
        maxMandates = _maxMandates;
}

void Simulation::setNumOfJoinedPartys(){
    numOfJoinedPartys++;
}

/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId(),], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> ans;
    //iterates all coalitions
    for(int i = 0; i<allCoalition.size(); i++){
        vector<int> addToAns;
        Coalition *currCoalition = allCoalition[i];
        vector<Party*> *coalitionPartys = (*currCoalition).getMpartys();

        //creates the coalition to add 
        for(int j = 0; j<(*coalitionPartys).size(); i++){
            addToAns.push_back((*(*coalitionPartys)[j]).getId());
        }

        //adds the coalition
        ans.push_back(addToAns);


    }
    return ans;
}
