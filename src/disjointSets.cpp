/// @author Janiel Venice C. Abad
/// @brief Implementation file for the class disjointSets
/// @file disjointSets.cpp
/// @date 2018-11-07

#include "disjointSets.h"

#include <iostream>
#include <iomanip>

disjointSets::disjointSets(int size) {
    setSize = size;
    if(setSize < MIN_SIZE) {
        setSize = MIN_SIZE;
    }
    
    links = new int[setSize]{};
    ranks = new int[setSize]{};
    
    for(int i = 0; i < setSize; i++) {
        links[i] = -1;
        ranks[i] = 1;
    }
}

/// ----------------------------------------------------------------------------

disjointSets::~disjointSets() {
    delete [] links;
    links = nullptr;

    delete [] ranks;    
    ranks = nullptr;
}

/// ----------------------------------------------------------------------------

int disjointSets::entries() const {
    return setSize;
}

/// ----------------------------------------------------------------------------

void disjointSets::printSets() const {
    using namespace std;

    // print indexes
    cout << "  index:";
    for(int i = 0; i < setSize; i++) {
        cout << "  " << i;
    }
    
    // print links
    cout << "\n  links:";
    for(int i = 0; i < setSize; i++) {
        cout << setw(3) << links[i];
    }
    
    // print ranks
    cout << "\n  ranks:";
    for(int i = 0; i < setSize; i++) {
        cout << setw(3) << ranks[i];
    }
    
    cout << endl;
}

/// ----------------------------------------------------------------------------

int disjointSets::setUnion(int r1, int r2) {
    // range check
    if(r1 < 0 || r2 < 0 || r1 >= setSize || r2 >= setSize) {
        return -1;
    }
    
    int p = 0;    // parent
    int c = 0;    // child
    
    // make sure r1 and r2 are roots
    if(setFind(r1) != -1) {
        r1 = setFind(r1);
    }
    
    if(setFind(r2) != -1) {
        r2 = setFind(r2);
    }
    
    // decide which will be the new root
    if(ranks[r1] <= ranks[r2]) {
        p = r2;
        c = r1;
    } else {
        p = r1;
        c = r2;
    }
    
    // union
    links[c] = p;
    
    // update rank if needed
    if(ranks[r1] == ranks[r2]) {
        ranks[p]++;
    }
    
    return p;
}

/// ----------------------------------------------------------------------------

int disjointSets::setFind(int x) {
    // range check
    if(x < 0 || x >= setSize) {
        return -1;
    }
    
    if(links[x] < 0) {
        return x;
    } else {
        return links[x] = setFind(links[x]);
    }
}
