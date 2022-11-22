#pragma once

#include "Simulation.h"
#include "Agent.h"

class SelectionPolicy {
    public:
      virtual ~SelectionPolicy()= default;
      virtual SelectionPolicy *clone() const= 0;
      virtual void choose(Agent *agent,Simulation& s)=0;
 };

class MandatesSelectionPolicy: public SelectionPolicy{
    public:
      ~MandatesSelectionPolicy() = default;
      virtual MandatesSelectionPolicy *clone() const;
      virtual void choose(Agent *agent,Simulation& s);
 };

class EdgeWeightSelectionPolicy: public SelectionPolicy{ 
    public:
      ~EdgeWeightSelectionPolicy()= default;
      virtual EdgeWeightSelectionPolicy *clone() const;
      virtual void choose(Agent *agent,Simulation& s);        
};