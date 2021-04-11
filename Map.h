//
// Created by moin_11 on 3/20/21.
//


#ifndef ROUTE_PLANNING_DSA_MAP_H
#define ROUTE_PLANNING_DSA_MAP_H

#include<iostream>
#include <utility>
#include<vector>
#include<fstream>
#include <cctype>
#include<cstring>
#include<string>
#include "Location.h"


using namespace std;

class Map {


private:

    int width{}, height{}; // width and height of map

    vector<vector<Location>> locations; // map of locations

    char start{}, end{}; // stores the name of start and end location

    int start_X{}, start_Y{}, end_X{}, end_Y{}; // start and end location co-ordinates

    bool Loaded{false}, pathFounded{false}; // to check if the map is loaded



public:
    Map(int w, int h, vector<vector<Location>> vec_locations) : width{w}, height{h}, locations{std::move(vec_locations)} {}


   explicit Map()= default;

    explicit Map(const string& fileName) {

        ifstream in(fileName);

        if (in.fail()) {
            cout << "error: map file not found" << endl;

        }

        else {



            string str1, str2, str3;
            getline(in, str1);
            getline(in, str2);
            getline(in, str3);


            int line = 0;
int cell = 0;
            while (!in.eof()) {
cell = 0;
                int i = 0, j = 0, k = 1;
                char name = ' ';


                vector<Location> vec_location;

                while (i < str1.size() - 1) {

                    Location location;

                    location.setX(line);
                    location.setY(cell);

                    if (str1[i] == '+')
                        i++; // new path

                    if (str1[i] == '-')
                        location.setAbove(false);
                    else if (str1[i] == ' ')
                        location.setAbove(true);

                    else
                        cout << "error evaluation above at line = " << line <<"  cell = " << cell << endl;


                    i = i + 3; // path left

                    if (str2[j] == '|')
                        location.setLeft(false);
                    else if (str2[j] == ' ')
                        location.setLeft(true);
                    else
                        cout << "error evaluation left"<< line <<"  cell = " << cell  << endl;


                    j = j + 2; // cost

                    if (str2[j] != ' ')

                        if (isdigit(str2[j]))
                            location.setCost(str2[j] - '0');

                        else {
                            location.setCost(0);
                            location.setName(str2[j]);
                        }
                    else location.setCost(0);

                    j = j + 2; //path right

                    if (str2[j] == '|') location.setRight(false);
                    else if (str2[j] == ' ') location.setRight(true);
                    else
                        cout << "error evaluation right"<< line <<"  cell = " << cell  << endl;


                    //path below
                    if (str3[k] == ' ') location.setBelow(true);
                    else if (str3[k] == '-') location.setBelow(false);
                    else
                        cout << "error evaluation below" << line <<"  cell = " << cell << endl;


                    k = k + 4; // wall below

                    vec_location.push_back(location); // push in vector<Location>
                    cell++; // increment cell
                }

                line++;   // increment line

                str1 = str3;
                getline(in, str2);
                getline(in, str3);

                this->locations.push_back(vec_location);  // pushing vector<Location> to member variable vector<vector>Location>>



            }

            width = cell;
            height = line;

            Loaded = true;
            pathFounded = false;

        }


    }












// sets all locations to unvisited
    void setLocationsUnvisited(){

        for(auto & location : locations){
            for(auto & j : location){

                j.setVisited(false);

            }
        }
    }


// sets the starting location
    void setStart(){

        char start_char;
        bool found = false;

        do {
            cout << "\nplease enter start location: " << endl;
            cin >> start_char;

            bool same = start_char == end;
            if(same){
                cout << "start and end co-ordinates cannot be same!" << endl;

            }

            for(int i  = 0 ; i < locations.size() && !found && !same; i++){
                for(int j = 0 ; j < locations[i].size(); j++){

                    if( locations[i][j].getName() == start_char){

                        start_X = i; // line
                        start_Y = j; // cell
                        start = locations[i][j].getName();

                        found = true;
                    }

                }

            }
        }
        while(!found);

    }
    // selects the end location
    void setEnd(){

        char end_char;
        bool found = false;


        do {
            cout << "\nplease enter destination location: " << endl;
            cin >> end_char;

            bool same = end_char == start;
            if(same){
                cout << "start and end co-ordinates cannot be same!" << endl;

            }

            for(int i  = 0 ; i < locations.size() && !found && !same; i++){
                for(int j = 0 ; j < locations[i].size(); j++){

                    if(end_char == locations[i][j].getName()){

                        end_X = i; // line
                        end_Y = j; // cell
                        end = locations[i][j].getName();

                        found = true;
                    }

                }

            }


        }
        while(!found);
    }


    /*Setters and Getters*/

    char getStart() const{
        return start;
    }



    char getEnd() const{
        return end;
    }

    int getStartX() const {
        return start_X;
    }

    int getStartY() const{
        return  start_Y;
    }



    void setEndX(int x)  {
        end_X = x;
    }

    void setEndY(int y) {
        end_Y = y;
    }


    void setStartX(int x) {
        start_X = x;
    }

    void setStartY(int y){
        start_Y = y;
    }



    int getEndX() const {
        return end_X;
    }

    int getEndY() const{
        return  end_Y;
    }





    int getWidth() const {

        return width;


    };

    int getHeight() const {

        return height;

    };


    int setWidth(int w) {

        width = w;


    };

    int setHeight(int h) {

        height = h;

    };


    vector<vector<Location>> getLocations() const {

        return locations;


    }


    void setLocations(vector<vector<Location>> vec_vec_locations)  {

        locations = std::move(vec_vec_locations);

    }




    void setCost(int x, int y, int cost){
        locations[x][y].setCost(cost);

    }

    bool getLoaded ()const
    {

        return Loaded;
    }

    void setLoaded(bool boolean){

        Loaded = boolean;
    }

    bool getPathFounded ()const
    {

        return pathFounded;
    }

    void setPathFounded(bool boolean){

        pathFounded = boolean;
    }


    /*special setters*/


    // sets bool visited of a location to a boolean
    void setVisitedAt(int x, int y, bool boolean){

        locations[x][y].setVisited(boolean);

    }

    // sets the parent coordinates of a specific location
    void setParentsAt(int x, int y, int X_coord, int Y_coord) {

        locations[x][y].setParentX(X_coord);
        locations[x][y].setParentY(Y_coord);

    }


// set whether the location at coordinates has parents
    void setHasParents(int x, int y, bool Boolean){
        locations[x][y].setHasParents(Boolean);

    }


// sets name at to obj at specific co-ordinates
    void setNameAt(int x, int y, char obj){
        locations[x][y].setName(obj);

    }




    /*Specific to Djikstra, it will loop and check if a location does not have a parent, it will set it's cost to 0 to not print it when we call print. Called in the Djikstra success function*/

    void zeroCostPaths(){

        for( auto& line: locations){
            for(auto& cell: line){

                    cell.setCost(0);
           }
        }

    }


    // operator overload
 Location& operator () (const int line, const int cell)
    {

            return locations[line][cell];

    }


  const  Location& operator () (const int line, const int cell) const
    {

        return locations[line][cell];

    }



};



#endif //ROUTE_PLANNING_DSA_MAP_H
