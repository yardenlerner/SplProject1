#pragma once

#include <vector>

#include "Graph.h"
#include "Agent.h"

using std::string;
using std::vector;


class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;

    const Graph &getGraph() const;
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    const vector<vector<int>> getPartiesByCoalitions() const;
    //added methods
    void addDuplicate(Agent *duplicate); 
    void addCoalition(Coalition *coalition); // adds the coalition to the simulation
    void setMaxMandates(int _maxMandates);//changes the maxMandates if needed
    void setNumOfJoinedPartys();// adds ++ to numOfJoinedPartys 
  

        

private:
    Graph mGraph;
    vector<Agent> mAgents;

    //add fields 
    bool isInitialized; // deafault value false 
    vector<Coalition*> allCoalition;
    int maxMandates; //default value 0
    int numOfJoinedPartys; //deafault value 0
};
