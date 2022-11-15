#include "Party.h"
#include <Agent.h>
#include <Simulation.h>
#include <JoinPolicy.h>
#include <vector>
using std::vector;

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting)  , maxMandetAgent(nullptr)
{
    // You can change the implementation of the constructor, but not the signature!

    // mTimer , mOffers , maxMandetsForChoosingAgent initialize with deffault values
}

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

const string& Party::getName() const
{
    return mName;
}




void Party::step(Simulation &s)
{
    switch (mState)
    {
    case Waiting:
        break;
    
    case Joined:
        break;

    case CollectingOffers:
        mTimer++;
    }

    if(mTimer==3){
        //adds the duplicate to the list of agents
        Agent *duplicate = (*mJoinPolicy).choose(*this , s.getAgents().size());
        
        int newAgentPartyId = (*duplicate).getId();
        Graph graph = s.getGraph();
        vector<Party*> newAgentOptionalPartys = (*duplicate).getOptionalPartys();
        //adding optional partys to new agent ++ not sure that vector object is a pointer
        for(int i=0; i<graph.getNumVertices(); i++){
            if(graph.getEdgeWeight(newAgentPartyId,i)>0){
                Party *newOptionalParty = graph.getParty(i);
                newAgentOptionalPartys.push_back(newOptionalParty);
            }
        }

        //adds agent and changes the num of joiend partys and maxMandates if needed
        s.addDuplicate(duplicate);
        s.setMaxMandates((*duplicate).getCoalition()->getMandetes());
        s.setNumOfJoinedPartys();

        mState = Joined;


    }

    

    
}

//added methods
//**
//**

//adds an agent to the list of agents offering the party
void Party::addAgent(Agent *agent, int agentId)
{
   if (mState == Waiting){
        mState = CollectingOffers;
   }
    mOffers.push_back(agent);
}


int Party::getId () const{
    return mId;
}

Agent* Party::getMaxAgent() {
    int maxMandates=0;
    int maxIndx=0;
    for(int i = 0; i<mOffers.size(); i++){
        int currMandates = mOffers[i]->getCoalition()->getMandetes();
        if(currMandates>= maxMandates){
            if(currMandates == maxMandates ){//not sure if the condition is right by definition of work
                if(mOffers[maxIndx]->getPartyId()>mOffers[i]->getPartyId()){
                    maxIndx = i;
                }
            }

            else{
                maxMandates = currMandates;
                maxIndx = i;
            }
        }
    }

    return mOffers[maxIndx];
}