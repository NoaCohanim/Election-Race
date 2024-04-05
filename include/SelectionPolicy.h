#pragma once
#include<vector>


using std::vector;
class Graph;
class Party;

class SelectionPolicy { 
public:

    SelectionPolicy();

    SelectionPolicy(int id);
    virtual SelectionPolicy* clonePolicy() = 0;
    void select(vector<Party*>& neigs, const Graph& g);
    void setPartyID(int id);
    int getPartyID ();
    virtual ~ SelectionPolicy(); //Destructor
    virtual int maxIndexFinder(vector<Party*>& nominees, const Graph& g, int start) = 0;
    private:
    int myAgentPartyID;
};



class MandatesSelectionPolicy: public SelectionPolicy{
    public:
    MandatesSelectionPolicy();
    MandatesSelectionPolicy (int id);
    virtual SelectionPolicy* clonePolicy();
    virtual int maxIndexFinder(vector<Party*>& nominees, const Graph& g, int start);
 };

class EdgeWeightSelectionPolicy: public SelectionPolicy{
    public:
    EdgeWeightSelectionPolicy();
    EdgeWeightSelectionPolicy (int id);
    virtual SelectionPolicy* clonePolicy();
    virtual int maxIndexFinder(vector<Party*>& nominees, const Graph& g, int start);

 };