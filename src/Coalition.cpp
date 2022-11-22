#include "Coalition.h"
#include <vector>

using std::vector;

Coalition :: Coalition():mPartys(), mAgents(), didOffer(0), numOfMandates(0), mId(0) {}

Coalition :: Coalition(Graph graph, Agent agent,int id): mPartys(), mAgents(), didOffer(new bool [graph.getNumVertices()]) , numOfMandates(graph.getParty(agent.getPartyId())->getMandates()) , mId(id){
    
    
    mAgents.push_back(agent.getId());
    Party *addParty = graph.getParty(agent.getPartyId());
    mPartys.push_back((*addParty).getId());

}

Coalition :: Coalition(const Coalition &other) : mPartys(), mAgents(), didOffer(new bool[sizeof(other.didOffer)]), numOfMandates(0), mId(other.mId){
    int mPartySize = other.mPartys.size();
    int mAgentSize = other.mAgents.size();

    for(int i = mAgentSize - 1; i>= 0; i--)
        mAgents.push_back(other.mAgents[i]);

    for (int i=mPartySize- 1; i>=0; i--){
        mPartys.push_back(other.mPartys[i]);
    }

    int sizeOfArray = sizeof(other.didOffer);
    for(int i = 0; i<sizeOfArray; i++)
        didOffer[i] = other.didOffer[i];
    
    numOfMandates = other.numOfMandates;
}

Coalition::~Coalition(){
    if(didOffer) delete didOffer;
}

Coalition& Coalition::operator= (const Coalition& other){ //copy assingment operator 

    if(this != &other){

        if(didOffer) delete [] didOffer;
        mAgents.clear();
        mPartys.clear();

        int mPartySize = other.mPartys.size();
        int mAgentSize = other.mAgents.size();

        mId = other.mId;

        for(int i = mAgentSize - 1; i>= 0; i--)
            mAgents.push_back(other.mAgents[i]);
    
        for (int i=mPartySize- 1; i>=0; i--)
            mPartys.push_back(other.mPartys[i]);

        int sizeOfArray = sizeof(other.didOffer);
        didOffer = new bool [sizeOfArray];
        for(int i = 0; i<sizeOfArray; i++)
            didOffer[i] = other.didOffer[i];
    
        numOfMandates = other.numOfMandates;
    }

    return *this;
}

Coalition :: Coalition (Coalition&& other) :mPartys(), mAgents(), didOffer(0), numOfMandates(other.numOfMandates) , mId(other.mId){ // move constructor

    int mPartySize = other.mPartys.size();
    int mAgentSize = other.mAgents.size();

    for(int i = mAgentSize - 1; i>= 0; i--)
        mAgents.push_back(other.mAgents[i]);
    
    for (int i=mPartySize- 1; i>=0; i--)
        mPartys.push_back(other.mPartys[i]);

    int sizeOfArray = sizeof(other.didOffer);
    didOffer = new bool [sizeOfArray];
    for(int i = 0; i<sizeOfArray; i++)
        didOffer[i] = other.didOffer[i];

    //deleting other resources
    other.didOffer = nullptr;
    other.mAgents.clear();
    other.mPartys.clear();
}

Coalition& Coalition:: operator= (Coalition&& other){ // move assingment operator
    
    if(didOffer) delete [] didOffer;
    mAgents.clear();
    mPartys.clear();

    int mPartySize = other.mPartys.size();
    int mAgentSize = other.mAgents.size();

    mId = other.mId;

    for(int i = mAgentSize - 1; i>= 0; i--)
        mAgents.push_back(other.mAgents[i]);
    
    for (int i=mPartySize- 1; i>=0; i--)
        mPartys.push_back(other.mPartys[i]);

    int sizeOfArray = sizeof(other.didOffer);
    didOffer = new bool [sizeOfArray];
    for(int i = 0; i<sizeOfArray; i++)
        didOffer[i] = other.didOffer[i];
    
    numOfMandates = other.numOfMandates;


    other.didOffer = nullptr;
    other.mAgents.clear();
    other.mPartys.clear();
    

    return *this;
}

vector<int> *Coalition::getMpartys(){
    return &mPartys;
}
vector<int> *Coalition::getMagents(){
    return &mAgents;
    
}


bool *Coalition::getDidOffer (){
    return didOffer;
}

void Coalition::addParty(int newPartyId, int mandates){
    mPartys.push_back(newPartyId);
    numOfMandates = numOfMandates + mandates;
}

void Coalition::addAgent(int newAgentId){
    mAgents.push_back(newAgentId);
}

void Coalition::addOffer(int paryId){
    didOffer[paryId] = true;
}

int  Coalition::getMandetes(){
    return numOfMandates;
}

int Coalition::getId(){
    return mId;
}

