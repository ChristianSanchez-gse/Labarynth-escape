#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <sstream>
#include <set>
#include "maze.h"
#include "grid.h"
#include "EscapeTheLabyrinth.h"
#include <stdlib.h>

int getRowCopy(Grid<int> T) {
    return T.numrows();
}
int getColCopy(Grid<int> T) {
    return T.numcols(0);
}
int getSizeCopy(Grid<int> T) {
    return T.size();
}
void displayCopy(Grid<int> T) {
    cout<< "The copy:" << endl;
    T._output();
}
TEST(grid, defaultConstructor){
    //testing the default constructor
    Grid<int> T;
    ASSERT_EQ(T.numrows(),4);
    ASSERT_EQ(T.numcols(0), 4);
    ASSERT_EQ(T.numcols(1), 4);
    ASSERT_EQ(T.numcols(2), 4);
    ASSERT_EQ(T.numcols(3), 4);

    // testing the size function
    ASSERT_EQ(T.size(), 16);
}
TEST(grid, paramConstructor){
    //tests that the correct number of rows and cols are created
    //in param constructor
    for(int i = 0; i < 100; i++) {
        int colTest = rand() % 200 + 1;
        int rowTest = rand() % 200 + 1;
        Grid<int> T(rowTest,colTest);
        EXPECT_EQ(T.numcols(rowTest-1), colTest);
        EXPECT_EQ(T.numrows(), rowTest);

        //testing the size function
        ASSERT_EQ(T.size(), colTest*rowTest);
    }
    //testing for string object
    for(int i = 0; i < 100; i++) {
        int colTest = rand() % 200 + 20;
        int rowTest = rand() % 200 + 20;
        Grid<string> T(rowTest,colTest);
        EXPECT_EQ(T.numcols(rowTest-1), colTest);
        EXPECT_EQ(T.numrows(), rowTest);
    }
    //testing for char object
    for(int i = 0; i < 100; i++) {
        int colTest = rand() % 200 + 20;
        int rowTest = rand() % 200 + 20;
        Grid<char> T(rowTest,colTest);
        EXPECT_EQ(T.numcols(rowTest-1), colTest);
        EXPECT_EQ(T.numrows(), rowTest);
    }
}
TEST(grid, indexOperator){
    //creating a random grid dimensions
    int col = rand() % 50 + 1;
    int row = rand() % 50 + 1;
    //testing the index to be default value
    for(int i = 0; i < 100; i++) {
        int y = rand() % (col-1) + 1;
        int x = rand() % (row-1) + 1;
        Grid<string> T(row,col);
        ASSERT_EQ(T(x,y), "");
    }
    //testing int
    for(int i = 0; i < 100; i++) {
        int y = rand() % (col-1) + 1;
        int x = rand() % (row-1) + 1;
        Grid<int> T(row,col);
        ASSERT_EQ(T(x,y), 0);
    }
}
// Tests the copy constructor by
// checking equality with predefined values
TEST(grid, copyConstruct){
    for (int i = 0; i < 100; i++ ) {
    int col = rand() % 20 + 4;
    int row = rand() % 20 + 4;
    Grid<int> T(col,row);
    ASSERT_EQ(getRowCopy(T), col);
    ASSERT_EQ(getColCopy(T), row);
    ASSERT_EQ(getSizeCopy(T), col*row);
    }
    //outputing the Grid
    /*
    cout << "CopyConstruct the original: " << endl;
    T._output();
    displayCopy(T);
    */
}
// This test case generates random number
// it will assert depening on whether or not
// it is out of bounds

// This case fails for me and it really stumped all the 
// TA's as well as myself. 
// For some reason when I pass the x and y into T(),
// it changes the value when inside of the function.
TEST(grid, invalidIndex){
    Grid<int> T(20,20);
    for(int i = 0; i < 100; i++) {
        int y = rand() % 50 + (-20);
        int x = rand() % 50 + (-20);
        if (x <= 0 || y <= 0) {
             ASSERT_EQ(T(x,y), 0);
            cout << "first Statement" << endl;
            cout << "This was X: "<< x << endl;
            cout << "This was Y: "<< y << endl;
        } else if (x > 19 || y > 19) {
            cout << "Second statement" << endl;
            cout << "This was X: "<< x << endl;
            cout << "This was Y: "<< y << endl;
            ASSERT_EQ(T(x,y), 0);
        } else {
            cout << "This is the else" << endl;
            cout << "This was X: "<< x << endl;
            cout << "This was Y: "<< y << endl;
            ASSERT_EQ(T(x,y), 0);
        }
    }

}

TEST(grid, equalOpterator){
    Grid<int> T(4,4);
    Grid<int> G(7,5);
    cout<< "The old T" << endl;
    G._output();
    T = G;
    ASSERT_EQ(T.numrows(), 7);
    ASSERT_EQ(T.numcols(0), 5);
    ASSERT_EQ(T.size(), 7*5);
    cout<< "The new T should be the same as G:" << endl;
    T._output();
}



// ----------------------------------------
// My own test cases have been incoporated into the maze, basic TEST
// that was given as starter code


//// Provided Test: sample maze from handout, make lots more yourself!

TEST(maze, basic) {
    vector<string> textMaze;

    textMaze.push_back("* *-W *");
    textMaze.push_back("| |   |");
    textMaze.push_back("*-* * *");
    textMaze.push_back("  | | |");
    textMaze.push_back("S *-*-*");
    textMaze.push_back("|   | |");
    textMaze.push_back("*-*-* P");

    Maze m(textMaze);

    MazeCell* start = m.getStart(2, 2);
    /* These paths are the ones in the handout. They all work. */
    EXPECT_TRUE(isPathToFreedom(start, "ESNWWNNEWSSESWWN"));
    EXPECT_TRUE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES"));
    EXPECT_TRUE(isPathToFreedom(start, "WNNEWSSESWWNSEENES"));
    
    /* These paths don't work, since they don't pick up all items. */
    EXPECT_FALSE(isPathToFreedom(start, "ESNW"));
    EXPECT_FALSE(isPathToFreedom(start, "SWWN"));
    EXPECT_FALSE(isPathToFreedom(start, "WNNE"));
    //lowercase
    EXPECT_FALSE(isPathToFreedom(start, "nesw"));

    /* These paths don't work, since they aren't legal paths. */
    EXPECT_FALSE(isPathToFreedom(start, "WW"));
    EXPECT_FALSE(isPathToFreedom(start, "NN"));
    EXPECT_FALSE(isPathToFreedom(start, "EE"));
    EXPECT_FALSE(isPathToFreedom(start, "SS"));
    EXPECT_FALSE(isPathToFreedom(start, "S"));
}


//// Provided Test: don't allow going through walls
TEST(maze, tryingToGoThroughWalls) {
    vector<string> textMaze;

    textMaze.push_back("* S *");
    textMaze.push_back("     ");
    textMaze.push_back("W * P");
    textMaze.push_back( "     ");
    textMaze.push_back( "* * *");

    Maze m(textMaze);

    MazeCell* start = m.getStart(1, 1);

    EXPECT_FALSE(isPathToFreedom(start, "WNEES"));
    EXPECT_FALSE(isPathToFreedom(start, "NWSEE"));
    EXPECT_FALSE(isPathToFreedom(start, "ENWWS"));
    EXPECT_FALSE(isPathToFreedom(start, "SWNNEES"));
}

//// Provided Test: Works when starting on an item
TEST(maze, startOnItem) {
    vector<string> textMaze;

    textMaze.push_back("P-S-W");

    Maze m(textMaze);
    MazeCell* start = m.getStart(0, 0);

    EXPECT_TRUE(isPathToFreedom(start, "EE"));
    start = m.getStart(0, 1);
    EXPECT_TRUE(isPathToFreedom(start, "WEE"));
    start = m.getStart(0, 2);
    EXPECT_TRUE(isPathToFreedom(start, "WW"));

}

//// Provided Test: Reports errors if given illegal characters.
TEST(maze, invalidChar) {
    vector<string> textMaze;

    textMaze.push_back("* *-W *");
    textMaze.push_back("| |   |");
    textMaze.push_back("*-* * *");
    textMaze.push_back("  | | |");
    textMaze.push_back("S *-*-*");
    textMaze.push_back("|   | |");
    textMaze.push_back("*-*-* P");

    Maze m(textMaze);
    MazeCell* start = m.getStart(0, 0);

    /* These paths contain characters that aren't even close to permissible. */
    EXPECT_FALSE(isPathToFreedom(start, "Q"));
    EXPECT_FALSE(isPathToFreedom(start, "X"));
    EXPECT_FALSE(isPathToFreedom(start, "!"));
    EXPECT_FALSE(isPathToFreedom(start, "?"));

    EXPECT_FALSE(isPathToFreedom(start, "n"));
    EXPECT_FALSE(isPathToFreedom(start, "s"));
    EXPECT_FALSE(isPathToFreedom(start, "e"));
    EXPECT_FALSE(isPathToFreedom(start, "w"));

    ///* These are tricky - they're legal paths that happen to have an unexpected
    // * character at the end.
    start = m.getStart(2, 2);
    EXPECT_FALSE(isPathToFreedom(start, "ESNWWNNEWSSESWWNQ"));
    EXPECT_FALSE(isPathToFreedom(start, "SWWNSEENWNNEWSSEES!!!"));
    EXPECT_FALSE(isPathToFreedom(start, "WNNEWSSESWWNSEENES?"));
    //empty string
    EXPECT_FALSE(isPathToFreedom(start, ""));
    //

}

 //Provided Test: This tests your personalized regular maze to see if you were
 //able to escape.
TEST(maze, escapeRegularMaze) {
    Maze m(4, 4);
    MazeCell* start = m.mazeFor(kYourName);
    EXPECT_TRUE(isPathToFreedom(start, kPathOutOfRegularMaze));
}
//
//// Provided Test: This tests your personalized twisty maze to see if you were
//// able to escape.
TEST(maze, escapeTwistyMaze) {
    Maze m(4, 4);
    MazeCell* start = m.twistyMazeFor(kYourName);
    EXPECT_TRUE(isPathToFreedom(start, kPathOutOfTwistyMaze));
}

