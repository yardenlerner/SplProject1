#pragma once
#include <string>
#include <vector>
#include "Agent.h"

using std::string;
using std::vector;

class JoinPolicy;
class Simulation;
class Agent;


enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    // added methods
    void addAgent(Agent *agent, int agentId);
    int getId () const; 
    Agent* getMaxAgent(); // returns the agent with maxMandate offerd
    vector<Agent*> getmOffers();


private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;
    //added fields
    int mTimer; 
    vector<Agent*> mOffers;
    int maxMandetsForChoosingAgent;
    Agent* maxMandetAgent;
};
