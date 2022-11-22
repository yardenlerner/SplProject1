#include "Party.h"
#include <Agent.h>
#include <Simulation.h>
#include <JoinPolicy.h>
#include <vector>
using std::vector;


Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting) , mTimer(0) , mOffers()
{
    // You can change the implementation of the constructor, but not the signature!

    // mTimer , mOffers ,  initialize with deffault values
    
}

// rule of 5 implemantation

Party::Party(const Party &other):mId(other.getId()) , mName(other.getName()) , mMandates(other.getMandates()) , mJoinPolicy(other.mJoinPolicy->clone()),mState(other.getState()) , mTimer(other.mTimer),mOffers()
{

    int sizeOfMoffers = other.mOffers.size();
    for(int i = sizeOfMoffers - 1; i >= 0; i--)
        mOffers.push_back(other.mOffers[i]);

}

// copy assignment operator
Party& Party::operator=(const Party &other){

    if(this != &other){
        mId = other.getId();
        mName = other.getName();
        mMandates = other.getMandates();
        *mJoinPolicy = *other.mJoinPolicy;
        mState = other.getState();
        mTimer = other.mTimer;


        mOffers.clear();
        int sizeOfMoffers = other.mOffers.size();
        for(int i = sizeOfMoffers - 1; i >= 0; i--)
            mOffers.push_back(other.mOffers[i]);
    }

    return *this;


}

Party:: ~Party(){//destructor
    if (mJoinPolicy) delete mJoinPolicy;
}

//move constructor
Party:: Party(Party &&other):mId(other.getId()) , mName(other.getName()) , mMandates(other.getMandates()) , mJoinPolicy(other.mJoinPolicy->clone()),mState(other.getState()) , mTimer(other.mTimer),mOffers(){
    int sizeOfMoffers = other.mOffers.size();
    for(int i = sizeOfMoffers - 1; i >= 0; i--)
        mOffers.push_back(other.mOffers[i]);

    //deleting other resources
    other.mJoinPolicy=nullptr;
    other.mOffers.clear();
    
}

//move assigment operator
Party& Party::operator=(Party &&other){

    mOffers.clear();

    mId = other.getId();
    mName = other.getName();
    mMandates = other.getMandates();
    mState = other.getState();
    mTimer = other.mTimer;

    if(mJoinPolicy) delete mJoinPolicy;
    mJoinPolicy= other.mJoinPolicy;
    other.mJoinPolicy=nullptr;

    mOffers.clear();
    int sizeOfMoffers = other.mOffers.size();
    for(int i = sizeOfMoffers - 1; i >= 0; i--)
        mOffers.push_back(other.mOffers[i]);

    //deleting other resources
    delete other.mJoinPolicy;
    other.mOffers.clear();

    return *this;
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
        int AgentDuplicateId = (*mJoinPolicy).choose(this , s);
      
        //adds agent and changes the num of joiend partys and maxMandates if needed
        Agent *newAgent= s.addDuplicate(AgentDuplicateId, this);
        Coalition *coalition = s.getCoalition((*newAgent).getCoalitionId());
        (*coalition).addAgent((*newAgent).getId());
        s.setMaxMandates((*coalition).getMandetes());
        s.setNumOfJoinedPartys();

        mState = Joined;

    }

}

//added methods
//**
//**

//adds an agent to the list of agents offering the party
void Party::addAgent( int agentId)
{
   if (mState == Waiting){
        mState = CollectingOffers;
   }
    mOffers.push_back(agentId);
}


int Party::getId () const{
    return mId;
}



vector<int> *Party::getmOffers(){
    return &mOffers;
}

