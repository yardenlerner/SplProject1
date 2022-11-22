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
    //rule of 5
    Party(const Party &other);// copy constructor
    ~Party(); // destructor
    Party& operator=(const Party &other);// copy assigment operator
    Party (Party &&other); // move constructor
    Party& operator=(Party &&other); // move assigment operator

    State getState() const;
    void setState(State state);
    int getMandates() const;
    void step(Simulation &s);
    const string &getName() const;
    // added methods
    void addAgent( int agentId);
    int getId () const; 
    //int getMaxAgentId(); // returns the agent with maxMandate offerd
    vector<int> *getmOffers();
    //void reserveMoffers(int numOfPartys);


private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy; //delete in destructor 
    State mState;
    //added fields
    int mTimer; // default 0
    vector<int> mOffers; 
};
