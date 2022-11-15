#pragma once

#include "Simulation.h"
#include "Agent.h"

class SelectionPolicy {
    public:
        virtual void choose(Agent *agent,Simulation& s)=0;
 };

class MandatesSelectionPolicy: public SelectionPolicy{
    public:
        MandatesSelectionPolicy();
        virtual void choose(Agent *agent,Simulation& s);
 };

class EdgeWeightSelectionPolicy: public SelectionPolicy{ 
    public:
        EdgeWeightSelectionPolicy();
        virtual void choose(Agent *agent,Simulation& s);
};