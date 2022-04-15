#include <utility>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

/* Change this constant to contain your full first and last name (middle is ok too).
 *
 * WARNING: Once you've set set this constant and started exploring your maze,
 * do NOT edit the value of kYourName. Changing kYourName will change which
 * maze you get back, which might invalidate all your hard work!
 */
const string kYourName = "Christian Sanchez Jimenez";

/* Change these constants to contain the paths out of your mazes. */
const string kPathOutOfRegularMaze = "EEWSESSENNN";
const string kPathOutOfTwistyMaze = "ESSE";


bool invalidFind(string moves) {
    for (size_t i = 0; i < moves.size(); i++) {
        if(moves[i] != 'N' && moves[i] != 'E' &&
        moves[i] != 'S' && moves[i] != 'W') {
            return false;
        }
    }
    return true;
}


// returns the next move in the string and deletes it.
// If the string is empty, then return empty char.
string currMove(string &directions) {
    //first check if the string is empty
    if (directions == "")
        return "";
    string moveAtFront = directions.substr(0,1);
    return moveAtFront;
}



// deletes the current move to get the next at the front
// of the list.
void deleteFirst(string &directions) {
    directions.erase(0,1);
}



// checks to see if the current position holds an items and
// updates the boolean values for each item.
// It then checks if all have been found and returns that value.
bool foundAllItems(MazeCell *currPos, bool &potion, bool &wand,
bool &spellbook) {
    if (currPos->whatsHere == "Spellbook")
        spellbook = true;
    else if (currPos->whatsHere == "Potion")
        potion = true;
    else if (currPos->whatsHere == "Wand")
        wand = true;

    // checking to see if all have been found, else
    // else return false.
    if (spellbook && potion && wand) {
        return true;
    } else {
        return false;
    }
}


//Checks is the path given is a valid path, else return false.
bool isPathToFreedom(MazeCell *start, const string& moves) {
    if (start == nullptr) {
        return false;
    }
    MazeCell *currPos = start;
    string directions = moves;
    // Checks for invalid characters
    if (invalidFind(directions) == false) {
        return false;
    }
    // made these as bool variables instead of counter
    // in case there could be 2 potions, wand, and no
    // spellbook found.
    bool potion = false;
    bool wand = false;
    bool spellbook = false;
    //loop that continues until all the moves are
    // used up.
    while(currMove(directions) != "") {
        //checking to see if items are found
        if (foundAllItems(currPos, potion, wand, spellbook) == true)
            return true;
        if (currMove(directions) == "N") {
            if (currPos->north != nullptr) {
                    currPos = currPos->north;
                } else {
                    return false;
                }
        } else if (currMove(directions) == "E") {
            if (currPos->east != nullptr) {
                    currPos = currPos->east;
                } else {
                    return false;
                }
        } else if (currMove(directions) == "S") {
            if (currPos->south != nullptr) {
                    currPos = currPos->south;
                } else {
                    return false;
                }
        } else if (currMove(directions) == "W") {
            if (currPos->west != nullptr) {
                    currPos = currPos->west;
                } else {
                    return false;
                }
        } else {
            //invalid move
            return false;
        }

        deleteFirst(directions);
    }
    // The code will reach this block
    // if the moves ran out before reaching all items
    if (foundAllItems(currPos, potion, wand, spellbook) == true) {
        return true;
    } else {
        return false;
    }
}
