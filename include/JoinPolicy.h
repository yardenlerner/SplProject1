#pragma once
 

class Party;

class JoinPolicy {
    public:
        virtual Agent* choose(Party &party , int agentId) = 0;
};

class MandatesJoinPolicy : public JoinPolicy {
    public:
        MandatesJoinPolicy();
        virtual Agent* choose(Party &party , int agentId);
};

class LastOfferJoinPolicy : public JoinPolicy {
    public:
        LastOfferJoinPolicy();
        virtual Agent* choose(Party &party , int agentId);
};