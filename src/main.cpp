#include <iostream>
#include <string>
#include <ctime>
#include "branch.h"
using namespace std;





// maximum number of trees
const int treeMax = 1;





// maximum number of branch levels
const int rangeMax = 2;
// data about the ranges ([min; max]) of the number of branches at the corresponding branch level.
const int ranges[rangeMax][2] = {
        {2,3},  // medium branches
        {3,5}   // big branches
};




/*!
 * @brief Recursive subroutine for entering the names of elves living on branches.
 * @param branch - address to the created tree/branch;
 * @param level - number of branch levels.
 */
void branchInit(Branch* branch, int level) {
    // calculation of a new level number and exit in case of exhaustion of levels.
    if( (--level) < 0 )
        return;

    // loop for creating 'level' branches.
    int
        min = ranges[level][0],
        max = ranges[level][1],
        count = rand() % (max-min+1) + min,
        level1 = rangeMax-level;
    cout << "Enter the names of " << count << " elves living on the " << level1 << "nd level of branches.\n";
    for (int i = 0; i < count; i++) {
        // local variables
        string name;
        Branch* branch1;

        // elf name input
        cout << "Enter the name of the branch level elf #" << level1 << ":";
        cin >> name;

        // creating a branch and adding to the root branch.
        branch1 = new Branch(name);
        branch->add(branch1);

        // creating branches on branch 'branch1'.
        branchInit(branch1, level);
    }
}

/*!
 * @brief A recursive subroutine that displays the contents of a tree in a tree structure.
 * @param br - address per tree/branch;
 * @param indent - indentation on the previous branch.
 */
void branchPrint(Branch* br, string indent) {
    // indent calculation for current level
    indent += "  ";

    // branch cycle
    for(int i=0; i<br->getBranchCount(); i++) {
        // getting a pointer to a branch
        Branch *br1 = br->getBranchAt(i);

        // elf name output
        cout << indent << "Elf name: " << br1->getName() << endl;

        // print the branches of the current branch
        branchPrint(br1, "  ");
    }
}






int main() {
    //---------------------------------------------------------------------------------
    // RNG initialization
    srand(time(nullptr));

    //---------------------------------------------------------------------------------
    // data
    Branch* trees[treeMax];  // array of trees
    bool find;  // search result flag

    //---------------------------------------------------------------------------------
    // tree initialization
    // tree creation cycle
    cout << "Enter the names of the elves living in the " << treeMax << " trees.\n";
    for (int i = 0; i < treeMax; i++) {
        // tree number output
        cout << "Tree #" << (i + 1) << ".\n";

        // tree creation
        trees[i] = new Branch();

        // making branches on a tree
        branchInit(trees[i], rangeMax);
    }
    cout
            << "-----------------------------------------------------------------------\n"
            << "End of naming.\n";

    //---------------------------------------------------------------------------------
    // output the contents of the trees to the console
    cout << "\nThe result of the initialization.\n";
    for (int i = 0; i < treeMax; i++) {
        cout << "\nTree #" << (i+1) << ".\n";
        branchPrint(trees[i], "");
    }
    cout << "-----------------------------------------------------------------------\n";

    //---------------------------------------------------------------------------------
    // work
    while(true) {
        string name;

        // data input
        cout << "\nEnter elf name or 'exit' command:";
        cin >> name;

        // data analyzer
        if( name == "exit" )
            break;

        cout << "Result:\n";
        find = false;  // let's say no elf named 'name' is found
        for (int i = 0; i < treeMax; i++) {
            Branch *br = (trees[i]->find(name));
            if (br != nullptr) {
                find = true;  // elf found
                int count = br->numberOfNeighbors();
                cout
                        << "Elf named '" << name << "' found on tree #" << i << ".\n"
                        << "The number of neighbors with him is " << count << endl;
                break;
            }// end of if()
        }// end of for() on trees
        if (!find)
            cout << "Elf named '" << name << "' was not found anywhere.\n";
    }

    //---------------------------------------------------------------------------------
    // destructor
    for(int i=0; i<treeMax; i++) {
        int count1 = trees[i]->getBranchCount();
        for(int i1=0; i1<count1; i1++)
            trees[i]->getBranchAt(i1)->Clear();
        trees[i]->Clear();
        delete trees[i];
    }

    return 0;
}// end of main()
