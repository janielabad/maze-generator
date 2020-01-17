/// @author Janiel Venice C. Abad
/// @brief Header file for the class mazeGenerator
/// @file mazeGenerator.h
/// @date 2018-11-07

#ifndef H_MAZEGENERATOR
#define H_MAZEGENERATOR

#include <string>

class mazeGenerator {
private:
    int rows;
    int cols;
    int intWalls;    /// number of interior walls
    int **walls;
    static constexpr int MIN_ROWS = 5;
    static constexpr int MIN_COLS = 5;
    static constexpr int MAX_ROWS = 100000;
    static constexpr int MAX_COLS = 100000;
    
public:
    /// ------------------------------------------------------------------------
    /// (Constructor) Initializes rows, cols, intWalls to 0, and walls to
    /// nullptr.
    /// ------------------------------------------------------------------------
    mazeGenerator();
    
    /// ------------------------------------------------------------------------
    /// (Destructor) Deallocates walls array.
    /// ------------------------------------------------------------------------
    ~mazeGenerator();
    
    /// ------------------------------------------------------------------------
    /// Gets rows and columns.
    ///
    /// @param r Number of rows
    /// @param c Number of columns
    /// ------------------------------------------------------------------------
    void getSize(int &r, int &c) const;
    
    /// ------------------------------------------------------------------------
    /// Allocates memory for walls array.
    ///
    /// @param r Number of rows
    /// @param c Number of columns
    ///
    /// @return True if numbers of rows and columns passed to it are valid,
    /// false if not 
    /// ------------------------------------------------------------------------
    bool setSize(int r, int c);
    
    /// ------------------------------------------------------------------------
    /// Generates a new maze based on the disjoint sets method.
    /// ------------------------------------------------------------------------
    void generate();
    
    /// ------------------------------------------------------------------------
    /// Prints maze data to a file.
    ///
    /// @param fn Filename
    ///
    /// @return True if printing was successful, false if not
    /// ------------------------------------------------------------------------
    bool printMazeData(const std::string fn) const;
    
    /// ------------------------------------------------------------------------
    /// Prints maze in textual format.
    /// ------------------------------------------------------------------------
    void printMazeText() const;
    
    /// ------------------------------------------------------------------------
    /// Checks commandline arguments.
    ///
    /// @param argc Number of arguments
    /// @param argv Vector of string arguments
    /// @param rowNum Number of rows
    /// @param colNum Number of columns
    /// @param fileName Output filename
    /// @param print Print specifier
    ///
    /// @return True if all arguments are valid, false if not
    /// ------------------------------------------------------------------------
    bool getArguments(int argc, char *argv[], int &rowNum, int &colNum, 
                      std::string &fileName, bool &print);

    /// ------------------------------------------------------------------------
    /// Checks if characters of str are digits.
    ///
    /// @param String to be checked
    ///
    /// @return True if string represents a number, false if not
    /// ------------------------------------------------------------------------
    bool isNumber(std::string str);

private:
    /// ------------------------------------------------------------------------
    /// Reorders the walls array in a random order using the permutations 
    /// method.
    /// ------------------------------------------------------------------------
    void randomize();
    
};

#endif /* H_MAZEGENERATOR */
