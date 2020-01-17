/// @author Janiel Venice C. Abad
/// @brief Implementation file for the class mazeGenerator
/// @file mazeGenerator.cpp
/// @date 2018-11-07

#include "disjointSets.h"
#include "mazeGenerator.h"

#include <iostream>
#include <fstream>

mazeGenerator::mazeGenerator() {
    rows = 0;
    cols = 0;
    intWalls = 0;
    walls = nullptr;
}

/// ----------------------------------------------------------------------------

mazeGenerator::~mazeGenerator() {    
    delete [] walls[0];
    walls[0] = nullptr;
    
    delete [] walls[1];
    walls[1] = nullptr;

    delete [] walls;
    walls = nullptr;
}

/// ----------------------------------------------------------------------------

void mazeGenerator::getSize(int &r, int &c) const {
    r = rows;
    c = cols;
}

/// ----------------------------------------------------------------------------

bool mazeGenerator::setSize(int r, int c) {
    bool valid = true;
    
    if(r < MIN_ROWS || c < MIN_COLS || r > MAX_ROWS || c > MAX_COLS) {
        valid = false;
    } else {
        rows = r;
        cols = c;
        
        // get number of interior walls
        intWalls = ( rows * (cols - 1) ) + ( cols * (rows - 1) ); 
        
        // dynamically allocate memory for walls array
        walls = new int*[intWalls];
        for(int i = 0; i < intWalls; i++) {
            walls[i] = new int[2];
        }
    }
    
    return valid;
}

/// ----------------------------------------------------------------------------

void mazeGenerator::generate() {    
    
    using namespace std;
    
    // fill walls array with valid walls
    // vertical walls
    for(int i = 0, j = 0; i < rows * (cols - 1); i++, j++) {
        if( ( (j + 1) % cols) == 0) {
            j++;
        }
        
        walls[i][0] = j;
        walls[i][1] = j + 1;        
    }
    
    // horizontal walls
    for(int j = 0, i = rows * (cols - 1); i < intWalls; i++, j++) {
        walls[i][0] = j;
        walls[i][1] = j + cols;
    }
    
    // randomize
    randomize();

    // union sets
    int s1 = 0;
    int s2 = 0;
    disjointSets sets(rows * cols);
    
    for(int i = 0; i < intWalls; i++) {
        s1 = sets.setFind(walls[i][0]);
        s2 = sets.setFind(walls[i][1]);
        
        if(s1 != s2) {
            sets.setUnion(s1, s2);
            
            walls[i][0] = -1;
            walls[i][1] = -1;
        }
    }
}

/// ----------------------------------------------------------------------------

void mazeGenerator::randomize() {
    for(int i = intWalls - 1, j = 0, tempLeft = 0, tempRight = 0; i > 0; i--) {
        j = std::rand() % i + 1;
    
        // swap
        tempLeft = walls[i][0];
        tempRight = walls[i][1];
        
        walls[i][0] = walls[j][0];
        walls[i][1] = walls[j][1];
        
        walls[j][0] = tempLeft;
        walls[j][1] = tempRight;
        
    }
}

/// ----------------------------------------------------------------------------

bool mazeGenerator::getArguments(int argc, char *argv[], int &rowNum, int &colNum, 
                  std::string &fileName, bool &print) {
    using namespace std;
    
    bool rowSpec = false;
    bool rowSpec2 = false;
    bool colSpec = false;
    bool colSpec2 = false;
    bool outSpec = false;
    bool printSpec = false;
    print = false;
    string num;
    string current;
    
    // if argument count is invalid
    if(argc == 1) {
        cout << "Usage: ./maze -r <rows> -c <columns> -o <filename> [-p]\n"
             << "*Options can be in any order.\n";
        return false;
    }
    
    if(argc != 7 && argc != 8) {
        cout << "Error, invalid command line options.\n";
        return false;
    }
    
    if(argc == 8) {
        printSpec = true;
        // need to see if print specifier is correct/exists in loop
    }
    
    for(int i = 1; i < argc; i++) {
        current = string(argv[i]);
        
        // check rows specifier
        if(current == "-r") {
            if(rowSpec) {
                rowSpec2 = true;
            }
            
            rowSpec = true;
            
            if(rowSpec2) {
                cout << "Error, invalid columns specifier.\n";
                return false;
            }
            
            num = string(argv[i + 1]);
            
            if(isNumber(num)) {
                rowNum = stoi(num);
            }
        }
        
        // check columns specifier
        if(current == "-c") {
            if(colSpec) {
                colSpec2 = true;
            }
            
            colSpec = true;
            
            if(colSpec2) {
                cout << "Error, invalid rows specifier.\n";
                return false;
            }
            
            num = string(argv[i + 1]);
            
            if(isNumber(num)) {
                colNum = stoi(num);
            } else {
                cout << "Error, invalid columns value.\n";
                return false;
            }
        }
        
        // check output file specifier
        if(current == "-o") {
            outSpec = true;
            fileName = string(argv[i + 1]);
            
            size_t length = fileName.length();
            string sub = fileName.substr(length - 4, length);
            
            if(sub != ".txt" && sub != ".dat") {
                cout << "Error, invalid output file type.\n";
                return false;
            }
            
            if(length > 19) {
                cout << "Error, unable to output file.\n";
                return false;
            }
        }
        
        // check print specifier
        if(current == "-p") {
            print = true;
        }
    }
    
    if(!rowSpec || colSpec2) {
        cout << "Error, invalid rows specifier.\n";
        return false;
    }
    
    if(!colSpec || rowSpec2) {
        cout << "Error, invalid columns specifier.\n";
        return false;
    }
    
    if(!outSpec) {
        cout << "Error, invalid output file specifier.\n";
        return false;
    }
    
    if(!print && printSpec) {
        cout << "Error, invalid print specifier.\n";
        return false;
    }
    
    
    return true;
}

/// ----------------------------------------------------------------------------

bool mazeGenerator::isNumber(std::string str) {
    bool valid = true;
    char currentChar;
    
    // check if all characters in string is a digit
    for(size_t n = 0; n < str.length() && valid; n++) {
        currentChar = str.at(n);
        
        if(!isdigit(currentChar) && ( currentChar != '-' )) {
            valid = false;
        }
    }
    
    return valid;
}

/// ----------------------------------------------------------------------------

bool mazeGenerator::printMazeData(const std::string fn) const {
    bool done = false;

    std::ofstream outFile;
    outFile.open(fn);
    
    if(outFile) {
        outFile << "ROWS " << rows << " COLS " << cols << std::endl;
        
        for(int i = 0; i < intWalls; i++) {
            if(walls[i][0] != -1) {
                outFile << "WALL " << walls[i][0] << ' ' << walls[i][1]
                        << std::endl;
            }
        }
        
        outFile.close();
        done = true;
    }
    
    return done;
}

/// ----------------------------------------------------------------------------

void mazeGenerator::printMazeText() const {
    using namespace std;
        
    bool *vWalls = new bool[intWalls]{false};    // vertical walls
    bool *hWalls = new bool[intWalls]{false};    // horizontal walls
    
    // for bottom row printing
    for(int i = ( cols * (rows - 1) ); i < intWalls; i++ ) {
        vWalls[i] = true;
    }

    // get walls
    for(int i = 0; i < intWalls; i++) {
        if(walls[i][0] != -1) {

            // horizontal wall
            if(walls[i][1] - walls[i][0] != 1) {
                vWalls[walls[i][0]] = true;
                
            // vertical wall
            } else {
                // need to decrement the index by row number
                int idx = walls[i][0];
                int temp = idx;
                int z = 0;
                
                while(temp >= cols) {
                    temp -= cols;
                    z++;
                }
                
                idx -= z;
                
                hWalls[idx] = true;
                
            }
        }
    }
    
    // top border
    cout << "+  ";
    
    for(int i = 0; i < cols - 1; i++) {
        cout << "+--";
    }
    
    cout << '+' << endl;
    // ~top border
    
    // interior walls
    int v = 0;
    int h = 0;
        
    for(int r = 0; r < rows; r++) {
        
        cout << '|';
        
        for(int x = 0; x < cols - 1; h++, x++) {
            cout << "  ";
            
            if(hWalls[h]) {
                cout << '|';
            } else {
                cout << ' ';
            }
        }
        
        cout << "  |\n";
        
        
        cout << '+';
        for(int y = 0; y < cols; v++, y++) {
            if(!vWalls[v] || ( v == rows * cols - 1 )) {
                cout << "  +";
            } else {
                cout << "--+";
            }
        }
        
        
        cout << endl;
    }
    // ~interior walls
    
    delete [] vWalls;
    vWalls = nullptr;
    
    delete [] hWalls;
    hWalls = nullptr;

}

