
#include <iostream>
#include<stack>
#include<queue>
#include<vector>
#include<string>
#include "Map.h"

using std::cout; using std::cin;
using std::endl;




void printMap(const Map& m){

int height = m.getHeight();
int width = m.getWidth();

    for(int line = 0; line < height; line++){

        bool start = m.getStart() == m(line, 0).getName(), end = m.getEnd() == m(line, 0).getName();


        if (!m(line, 0).getAbove()) {
            cout << "+---+";
        } else {
            cout << "+   +";
        }


        for(int cell = 1; cell  < width; cell++) {


            if (!m(line, cell).getAbove()) {
                cout << "---+";
            } else {
                cout << "   +";
            }

        }

        cout << endl;


        if(start) {
            if (!m(line, 0).getLeft()) {
                cout << "|(";
            } else {
                cout << "( ";
            }

            if (m(line, 0).getCost() != 0) {
                cout <<  m(line, 0).getCost();
            } else {
                cout << m(line, 0).getName();
            }


            if (!m(line, 0).getRight()) {
                cout << ")|";
            } else {
                cout << ") ";
            }

        }


        if(end){
            if (!m(line, 0).getLeft()) {
                cout << "|{";
            } else {
                cout << "{ ";
            }

            if (m(line, 0).getCost() != 0 ) {
                cout << m(line, 0).getCost();
            } else {
                cout << m(line, 0).getName();
            }

            if (!m(line, 0).getRight()) {
                cout << "}|";
            } else {
                cout << "} ";
            }


        }


        if(!start and !end){

            if (!m(line, 0).getLeft()) {
                cout << "| ";
            } else {
                cout << "  ";
            }

            if (m(line, 0).getCost() != 0) {
                cout << m(line, 0).getCost();
            } else {
                cout << m(line, 0).getName();
            }

            if (!m(line, 0).getRight()) {
                cout << " |";
            } else {
                cout << "  ";
            }
        }


        for(int cell = 1; cell  < width; cell++) {

            start = m.getStart() == m(line, cell).getName();
            end = m.getEnd() == m(line, cell).getName();

            if(start){
                if (m(line, cell).getCost() != 0) {
                    cout << "(" << m(line, cell).getCost();
                } else {
                    cout << "(" << m(line, cell).getName();
                }

                if (!m(line, cell).getRight()) {
                    cout << ")|";
                } else {
                    cout << ") ";
                }

            }


            if(end){

                if (m(line, cell).getCost() != 0) {
                    cout << "{" << m(line, cell).getCost();
                } else {
                    cout << "{" << m(line, cell).getName();
                }

                if (!m(line, cell).getRight()) {
                    cout << "}|";
                } else {
                    cout << "} ";
                }


            }
            if(!start and !end) {

                if (m(line, cell).getCost() != 0) {
                    cout<< " " << m(line, cell).getCost();
                } else {
                    cout << " " << m(line, cell).getName();
                }

                if (!m(line, cell).getRight()) {
                    cout << " |";
                } else {
                    cout << "  ";
                }
            }
        }

        cout << endl;



    }

    if(!m(height - 1, 0).getBelow()){

        cout << "+---+";
    }
    else{
        cout << "+   +";
    }


    for(int cell = 1; cell < width; cell++){

        if(!m(height - 1, cell).getBelow()){

            cout << "---+";
        }
        else{
            cout << "   +";
        }


    }
    cout << endl << endl;

}


struct compareLocations { // defining the comparison operator
    bool operator() (Location const& l1, Location const& l2) {
        return l1.getCost() > l2.getCost();
    }
};





// uses recursion, prints the co-ordinates of the found Path.

void PrintCoordinates(Location loc, Map & m, int x, int y){

    if(x == m.getStartX() and y == m.getStartY()) { // ensures start co-ordinate is printed
        cout << m(x, y).getName() <<m(x, y);
        return;
    }



    PrintCoordinates(m(loc.getParentX(), loc.getParentY()), m, loc.getParentX(), loc.getParentY());

m(x, y).getName()!= ' ' and  m(x, y).getName()!= '.' ?   cout << m(x, y).getName() <<m(x, y) : cout << m(x, y);
/* if the location has a Name like A, B. then print it otherwise don't*/

}

void Failure(){  //used in both Djikstra and searchPath


    cout << "could not find a path from start to destination" << endl;
}

void success(Location loc, Map& m){
    int currentX = loc.getX();
    int currentY = loc.getY();

 PrintCoordinates(loc, m, currentX, currentY); // prints the co-ordinates

    while(currentY != m.getStartY() or currentX != m.getStartX()){ // loops till start Location


        if(loc.getName() == '.' ) { // if the name is '.'
            m.setNameAt(currentX, currentY, 'o');  // it is set to 'o'
        }

        currentX = loc.getParentX();  // x is now parent x
        currentY = loc.getParentY(); // y is parent y
        loc = m(currentX, currentY);  // loc = parent loc


    }

    m.setPathFounded(true);  // set path found to true to print
    cout << endl << endl;
}





/*used in searchPath Function*/
template <class T>
T& top(std::stack<T>& s) { return s.top(); } // returns the top of a stack

template <class T>
T& top(std::queue<T>& q) { return q.front(); } // returns the front of a queue





/*Since the DFS and BFS algorithm are almost identical, it is better to implement a single  search template function to avoid code duplication*/


template<class T>
bool SearchPath(Map& m){ // single function that takes stack or queue

    T LocationContainer;

    LocationContainer.push(m(m.getStartX(), m.getStartY()));

    Location currentNode;  // initialize currentNode


    while(!LocationContainer.empty()){  // until it is empty
        currentNode = top(LocationContainer);
        /* currentNode is top of a stack in DFS or front of a queue in BFS*/


        int  x = currentNode.getX();
        int  y = currentNode.getY();

        LocationContainer.pop();  // pop the top or front.

        if(x == m.getEndX() and y == m.getEndY()){ // if we have reached the end, call the success function and return true

            success(currentNode, m);

            return true;

        }

        if(m(x, y).getName() == ' '){
            // if name is a blank space, make it a '.', I preferred not to make Locations like A, B, C into '.'

            m.setNameAt(x, y, '.');

        }


        if(currentNode.getBelow() and  !m(x + 1, y).getVisited()){  // check if below is accessible and if its not visited

            m.setParentsAt(x + 1, y, x, y);      // set parent of location_below to current node

            m.setHasParents(x + 1, y, true);       // set hasParents for location_below to true

            LocationContainer.push(m(x + 1, y));   // push the location_below to Container



        }
        if(currentNode.getRight() and !m(x,y + 1).getVisited()){   // same algorithm for below, except for right
            m.setParentsAt(x, y + 1, x, y);
            m.setHasParents(x, y + 1, true);
            LocationContainer.push(m(x,y + 1));


        }
        if(currentNode.getLeft() and !m(x ,y - 1).getVisited()){ // same algorithm for below, except for left


            m.setParentsAt(x, y - 1, x, y);
            m.setHasParents(x, y - 1, true);
            LocationContainer.push(m(x ,y - 1));

        }

        if(currentNode.getAbove() and !m(x-1,y).getVisited()){ // same algorithm for below, except for above


            m.setParentsAt(x- 1, y, x, y);
            m.setHasParents(x - 1, y, true);
            LocationContainer.push(m(x-1,y));


        }

        m(x, y).setVisited(true);  // set the current node to visited


    }


    Failure();
    return false;

}



/*Djikstras Functions*/

void successDjikstra(Location loc, Map& m){


    int currentX = loc.getX();
    int currentY = loc.getY();
    int totalCost = 0; // total cost value



    PrintCoordinates(loc, m, currentX, currentY); // print the co-ordinates

    while(currentY != m.getStartY() or currentX != m.getStartX()){
        if(loc.getName() == ' ' or loc.getName() == '.') {
            m.setNameAt(currentX, currentY, m(currentX, currentY).getCost() + '0');
            // makes the cost of the location, the name. if at (2, 1) has cost is 1 and name of ' ' now it will have a name of '1'
        }
        totalCost += m(currentX, currentY).getCost(); // at teh cost of current node

        currentX = loc.getParentX();
        currentY = loc.getParentY();
        loc = m(currentX, currentY);

    }
    cout << "\n\ncost: " << totalCost << endl << endl;

    m.setPathFounded(true);
    m.zeroCostPaths(); // making the cost of every other path 0 to print '.' and ' '. Print function prints;

}

bool searchDjikstra(Map& m){

    priority_queue<Location, vector<Location>, compareLocations> locationQueue;


    locationQueue.push(m(m.getStartX(), m.getStartY()));

    Location currentNode;

    while(!locationQueue.empty()){

        currentNode = locationQueue.top();


        int   x_currentNode = currentNode.getX();
        int   y_currentNode = currentNode.getY();

        m.setVisitedAt(x_currentNode, y_currentNode, true); // set current node to visited

        locationQueue.pop();

        if(x_currentNode == m.getEndX() and y_currentNode == m.getEndY()){

            successDjikstra(currentNode, m);
            return true;

        }

        if(m(x_currentNode,y_currentNode).getName() == ' '){

            m.setNameAt(x_currentNode, y_currentNode, '.');

        }

        if(currentNode.getBelow() and  !m(x_currentNode + 1, y_currentNode).getVisited()){

            m.setParentsAt(x_currentNode + 1, y_currentNode, x_currentNode, y_currentNode);

            m.setHasParents(x_currentNode + 1, y_currentNode, true);

            locationQueue.push(m(x_currentNode + 1, y_currentNode));



        }

        if(currentNode.getLeft() and !m(x_currentNode, y_currentNode - 1).getVisited()){

            m.setParentsAt(x_currentNode, y_currentNode - 1, x_currentNode, y_currentNode);
            m.setHasParents(x_currentNode, y_currentNode - 1, true);
            locationQueue.push(m(x_currentNode, y_currentNode - 1));

        }
        if(currentNode.getRight() and !m(x_currentNode,y_currentNode+ 1).getVisited()){
            m.setParentsAt(x_currentNode, y_currentNode+ 1, x_currentNode,y_currentNode);
            m.setHasParents(x_currentNode, y_currentNode + 1, true);
            locationQueue.push(m(x_currentNode,y_currentNode + 1));


        }

        if(currentNode.getAbove() and !m(x_currentNode- 1, y_currentNode).getVisited()){


            m.setParentsAt(x_currentNode- 1, y_currentNode, x_currentNode,y_currentNode);
            m.setHasParents(x_currentNode - 1, y_currentNode, true);
            locationQueue.push(m(x_currentNode - 1,y_currentNode));


        }


    }


    Failure(); // calls the failure function
    return false;

}

void loadMap(Map& m){

    string fileName;

    cout << "please enter filename (with extension): " << endl;
cin >> fileName;

    m = Map{fileName};

    m.getLoaded() ? cout << "loaded successfully" : cout << "failed to load map, check filename";
    cout << endl << endl;


}

void DisplayPath(Map& m){

    if (m.getPathFounded()) {
        printMap(m);
    } else {
        cout << "error: no path was found" << endl << endl;
    }


}

void optionsMenu(int & choice)  {



        cout << "Please select an option: " << endl;

        cout
                << "\n1)Load Map"
                << "\n2)Display Map"
                << "\n3)Set Start"
                << "\n4)Set Goal"
                << "\n5)Find Path with DFS"
                << "\n6)Find Path with BFS"
                << "\n7)Find Path with DA"
                << "\n8)Display Path"
                << "\n9)Quit" << endl;
        cin >> choice;







}

int main() {


    int choice = -1;
    Map m;




    while(choice != 9){


        optionsMenu(choice);


        switch (choice) {

            case 1:{
 // Load Map

 loadMap(m); // Loaded is set true in the constructor

    break;
            }


            case 2: {

        if(!m.getLoaded()){ // check if map is loaded before attempting to print.
            cout << "map is not loaded " << endl;
        }


        else {
    printMap(m);
            }


break;

            }


            case 3: {

                if(!m.getLoaded()){
                    cout << "map is not loaded " << endl;
                }               else {

                    if(m.getPathFounded()) {

                    cout << "please reload the map" << endl;
                    }

                    else {
                        m.setStart();
                    }
                }
            break;

            }


            case 4: {

                if(!m.getLoaded()){
                    cout << "map is not loaded " << endl;
                }

                else {

                    if(m.getPathFounded()) {

                        cout << "please reload the map" << endl;
                    }
else {
                        m.setEnd();
                    }
                }
                break;

            }


            case 5: {
        if(!m.getLoaded() xor m.getPathFounded()){

    cout << "please load/reload the map: " << endl;
        }

        else {

            if (!m.getStart()) {

                cout << "please select a start value!" << endl;
                m.setStart();
            }

            if (!m.getEnd()) {
                cout << "please select a end value!" << endl;
                m.setEnd();

            }


            SearchPath<stack<Location>>(m);
        }

            }
            break;


            case 6: {

                if(!m.getLoaded() xor m.getPathFounded()){

                    cout << "please load/reload the map: " << endl;
                }
                else {


                    if (!m.getStart()) {

                        cout << "please select a start value!" << endl;
                        m.setStart();
                    }

                    if (!m.getEnd()) {
                        cout << "please select a end value!" << endl;
                        m.setEnd();

                    }


                    SearchPath<queue<Location>>(m);
                }
                break;
            }


            case 7: {

                if(!m.getLoaded() xor m.getPathFounded()){
                    cout << "please load/reload the map!" << endl;
                }
                else{

                    if (!m.getStart()) {

                        cout << "please select a start value!";
                        m.setStart();
                    }

                    if (!m.getEnd()) {
                        cout << "please select a end value!";
                        m.setEnd();

                    }

                    searchDjikstra(m);
                }
                break;
            }


            case 8: {
            DisplayPath(m);

                break;
            }
            case 9: {

                cout << "goodbye :D" << endl;
                break;
            }

            default: {

                cout << "incorrect option chosen...." << endl;
                break;
            }
        }


    }
    return 0;
}
