#include "branch.h"

// helper method

/*!
 * @brief Subroutine to convert name to lower case if equal to 'none'.
 * @param inName - elf name.
 */
void Branch::namingWithControl(string inName) {
    // convert string characters to lower case
    for(char &ch: inName)
        ch = (char)tolower((int)ch);

    // if the new value is 'none' then change the field.
    if( inName == "none" )
        name = inName;
}

// setters
void Branch::setName(const string &inName) {
    name = inName;
    namingWithControl(name);
}

// getters
string Branch::getName() const { return name; }
// get the number of branches outgoing from the current branch.
int Branch::getBranchCount() const { return (int)branch.size(); }
// get branch address by index
Branch* Branch::getBranchAt(int index) const {
    // index control
    if( index < 0 ) return nullptr;
    if( index >= branch.size() ) return nullptr;

    // return result
    return branch[index];
}

// methods

// constructors
Branch::Branch() { Clear(); }
Branch::Branch(string &inName): name(inName) {
    namingWithControl(name);
    parent = nullptr;
}

// Data management

/*!
 * @brief Subroutine clearing a branch from data.
 */
void Branch::Clear() {
    for(auto &br: branch) {
        if( br != nullptr ) {
            br->Clear();
            delete br;
            br = nullptr;
        }
    }
    branch.clear();
    parent = nullptr;
    name = "none";
}

/*!
 * @brief Subroutine for adding a small branch to the current one.
 * @param inBranch - small branch.
 */
void Branch::add(Branch* inBranch) {
    // setting to parent branch
    inBranch->parent = this;
    // adding a branch
    branch.push_back(inBranch);
}

/*!
 * @brief Recursive subroutine for getting the address of a big branch.
 * @return Returns a pointer to the larger branch, or 'nullptr' if it fails to evaluate.
 */
const Branch* Branch::getTopBranch() const {
    // If this is a tree
    if (parent == nullptr)
        // then no result
        return nullptr;

    // If it's a big thread
    if (parent->parent == nullptr)
        // then return the address to the big branch
        return this;

    // otherwise, these are smaller branches
    return parent->getTopBranch();
}

/*!
 * @brief Recursive subroutine for finding a large branch of the tree on which the elf lives with the name 'inName'.
 * @param inName - elf name.
 * @return If successful, returns a pointer to the big branch, otherwise 'nullptr'.
 */
const Branch* Branch::find(const string &inName) const {
    // if found then success
    if (inName == name)
        return getTopBranch();

    // otherwise iterate over child branches recursively
    for(const auto &br: branch) {
        const Branch *br1 = br->find(inName);
        if (br1 != nullptr)
            return br1;
    }

    // if the execution of the subprogram reached here, then it was not found on this branch.
    return nullptr;
}

/*!
 * @brief Recursive subroutine for calculating the number of neighbors on the current branch, excluding branches labeled
 * 'none'.
 * @return Returns the number of neighbors.
 */
int Branch::numberOfNeighbors() const {
    // counter reset
    int count = 0;

    // count if a branch is populated
    if ( name != "none" )
        count++;

    // walk through child branches
    for(const auto &br: branch)
        count += br->numberOfNeighbors();

    // return result
    return count;
}
