#pragma once
#include "Simulation.h"

class Party;
class Agent;

class JoinPolicy {
    public:
        virtual ~JoinPolicy()=default;
        virtual JoinPolicy* clone() const = 0;
        virtual int choose(Party *party , Simulation &s) = 0;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
        ~MandatesJoinPolicy() override = default;
        virtual MandatesJoinPolicy* clone() const;
        virtual int choose(Party *party , Simulation &s);
    
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        ~LastOfferJoinPolicy() override = default;
        virtual LastOfferJoinPolicy* clone() const;
        virtual int choose(Party *party , Simulation &s);

        
};