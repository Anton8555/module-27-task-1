#pragma once

#include <string>
#include <vector>
using namespace std;

// branch class
class Branch {
    // fields
    string name;  // name of the elf living on the current branch
    Branch* parent;  // parent branch
    vector<Branch*> branch;  // child branches

    // helper method
    void namingWithControl(string inName);
public:
    // setters
    void setName(string inName);

    // getters
    string getName();
    int getBranchCount();
    Branch* getBranchAt(int index);

    // methods

    // constructors
    Branch();
    Branch(string inName);
    // Data management
    void Clear();
    void add(Branch* inBranch);
    // recursive functions
    Branch* getTopBranch();
    Branch* find(string inName);
    int numberOfNeighbors();
};
