/// @author Janiel Venice C. Abad
/// @brief Header file for the class disjointSets
/// @file disjointSets.h
/// @date 2018-11-07

#ifndef H_DISJOINTSETS
#define H_DISJOINTSETS

class disjointSets {
private:
    int setSize;
    int *links;
    int *ranks;
    static constexpr int MIN_SIZE = 10;
    
public:
    /// ------------------------------------------------------------------------
    /// (Constructor) Initializes setSize to valid size and allocates memory
    /// for links and ranks arrays.
    /// ------------------------------------------------------------------------
    disjointSets(int size = MIN_SIZE);
    
    /// ------------------------------------------------------------------------
    /// (Destructor) Deallocates links and ranks arrays.
    /// ------------------------------------------------------------------------
    ~disjointSets();
    
    /// ------------------------------------------------------------------------
    /// @return setSize
    /// ------------------------------------------------------------------------
    int entries() const;
    
    /// ------------------------------------------------------------------------
    /// Prints current disjoint set status, links and ranks, with the index.
    /// ------------------------------------------------------------------------
    void printSets() const;
    
    /// ------------------------------------------------------------------------
    /// Performs union-by-rank operation between the two passed sets and 
    /// returns the parent.
    ///
    /// @param r1 Set 1
    /// @param r2 Set 2
    ///
    /// @return parent
    /// ------------------------------------------------------------------------
    int setUnion(int r1, int r2);
    
    /// ------------------------------------------------------------------------
    /// Searches the parent of the passed set.
    ///
    /// @param x Set
    ///
    /// @return parent
    /// ------------------------------------------------------------------------
    int setFind(int x);
    
};


#endif /* H_DISJOINTSETS */
