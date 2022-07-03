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
    void setName(const string &inName);

    // getters
    string getName() const;
    int getBranchCount() const;
    Branch* getBranchAt(int index) const;

    // methods

    // constructors
    Branch();
    Branch(string &inName);
    // Data management
    void Clear();
    void add(Branch* inBranch);
    // recursive functions
    const Branch* getTopBranch() const;
    const Branch* find(const string &inName) const;
    int numberOfNeighbors() const;
};
