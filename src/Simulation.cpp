#include "Simulation.h"
#include "SelectionPolicy.h"
#include <iostream>
#include <vector>

using namespace std;


Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents) , isInitialized(false) , allCoalition() , maxMandates(0), numOfJoinedPartys(0)
{
    if(!isInitialized){
   // creating coalition from the list of agents
        int sizeOfmAgents = mAgents.size();
        for(int i=0; i < sizeOfmAgents; i++){
            
            Coalition newCoalition(mGraph , mAgents[i],i);  
            addCoalition(newCoalition);
            mAgents[i].setCoalition(i);
        }
    }
}

void Simulation::step()
{
    if(!isInitialized){
       
        int sizeOfmAgents = mAgents.size();
        for(int i=0; i < sizeOfmAgents; i++){

            // adding partys to the optional Partys of the agent
            mAgents[i].initializingOptionalPartys(mGraph);

        }


        isInitialized = true;
    }
    // making step for each party in the Graph.vertics
    int numOfVertices = mGraph.getNumVertices();
    for(int i=0; i < numOfVertices ; i++){
        Party *curr = mGraph.getParty(i);
        (*curr).step(*this);
    }


    //making step for each agent in mAgents
    int mAgnetsSize = mAgents.size();
    for(int i=0; i < mAgnetsSize; i++){
        Agent *curr = &mAgents[i];
        (*curr).step(*this);
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

vector<Agent>* Simulation::getAgents(){
    return &mAgents;
}

Coalition* Simulation::getCoalition(int coalitionId){
    return &allCoalition[coalitionId];
}

Graph* Simulation::getGraph(){
    return &mGraph;
}

Agent* Simulation::addDuplicate(int AgentDuplicateId, Party *party){
    vector<Agent> *allAgents = (*this).getAgents();
    //Agent lastAgent = ((*allAgents)[AgentDuplicateId]);
    Agent duplicate(allAgents->back().getId()+1 , (*party).getId() ,((*allAgents)[AgentDuplicateId]).getSelectionPolicy()->clone() , (*allAgents)[AgentDuplicateId].getCoalitionId()); //duplicate agent
    //adding optional partys to new agent 
    vector<int> *newAgentOptionalPartys = duplicate.getOptionalPartys();
    int numVertices = mGraph.getNumVertices();
    for(int i=0; i<numVertices; i++){
        if(mGraph.getEdgeWeight(AgentDuplicateId,i)>0){
            Party *newOptionalParty = mGraph.getParty(i);
            if((*newOptionalParty).getState()!= Joined)
                (*newAgentOptionalPartys).push_back(newOptionalParty->getId());
            }
        }
    mAgents.push_back(duplicate);
    return &mAgents.back();
}

void Simulation::addCoalition(Coalition coalition){
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

    ans.reserve(mGraph.getNumVertices());

    //iterates all coalitions
    int coalitionsSize = allCoalition.size();
    for(int i = 0; i<coalitionsSize; i++){
        vector<int> addToAns;
        addToAns.reserve(mGraph.getNumVertices());
        Coalition currCoalition = allCoalition[i];

        vector<int> *coalitionPartys = currCoalition.getMpartys();

        //creates the coalition to add 
        int coalitionPartysSize = (*coalitionPartys).size();
        for(int j = 0; j<coalitionPartysSize; j++){
            int id = (*coalitionPartys)[coalitionPartysSize-1-j];
            addToAns.push_back(id);
        }

        //adds the coalition
        ans.push_back(addToAns);


    }
    return ans;
}
