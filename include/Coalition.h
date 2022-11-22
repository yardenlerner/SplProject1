#pragma once

#include <vector>
#include "Graph.h"
#include "Party.h"
using std::vector;

class Agent;
class Party;
class Graph;

class Coalition
{
public:
    // rule of 5
    Coalition(); // empty
    Coalition(Graph graph, Agent agent,int id);
    Coalition(const Coalition &other);            // copy constructor 
    virtual ~Coalition();                         // destructor
    Coalition &operator=(const Coalition &other); // copy assingment operator 
    Coalition(Coalition &&other);                 // move constructor
    Coalition &operator=(Coalition &&other);      // move assingment operator 

    vector<int> *getMpartys();
    vector<int> *getMagents();
    bool *getDidOffer();

    void addParty(int newPartyId, int mandates);
    void addAgent(int newAgentId);
    void addOffer(int paryId);
    int getMandetes();
    int getId();

private:
    vector<int> mPartys; 
    vector<int> mAgents; 
    bool *didOffer; 
    int numOfMandates;
    int mId;
};