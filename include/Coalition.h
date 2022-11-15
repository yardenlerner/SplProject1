#pragma once

#include <vector>
#include "Graph.h"
using std::vector;


class Agent;
class Party;
class Graph;

class Coalition
{
    public:
        Coalition();
        Coalition(Graph graph, Agent agent); 
        vector<Party*> *getMpartys();
        vector<Agent*> *getMagents();
        bool * getDidOffer ();

        void addParty(Party* newParty); 
        void addAgent(Agent* newAgent); 
        void addOffer(int paryId); 
        int getMandetes();// not implemented
             
        
    private:
        vector<Party*> mPartys;
        vector<Agent*> mAgents;
        bool *didOffer;
        int numOfMandates; 
        

};