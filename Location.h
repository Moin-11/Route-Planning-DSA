//
// Created by moin_11 on 3/20/21.
//

#include<vector>
#include<string>



#ifndef ROUTE_PLANNING_DSA_LOCATION_H
#define ROUTE_PLANNING_DSA_LOCATION_H

class Location{
private:
    int x_coord, y_coord, parentX, parentY;  // location and parent co-ordinates

    int cost; // terrain cost

    bool above, below, left, right;  // neighbours

    bool isVisited, hasParents;   // checks

    char name;



public:

    /* Constructors */


    // default constructor
    Location() :  x_coord{-1}, y_coord{-1}, parentX{-1},parentY{-1}, cost{-1}, // ints -> -1

                  above{false}, below{false}, left{false}, right{false}, //neighbours -> false

                  isVisited{false}, hasParents{false}, // bool checks -> false

                  name{' '} {};



    // constructor with co-ordinates
    Location(int x, int y) : x_coord{x}, y_coord{y},

    parentX{-1},parentY{-1}, cost{-1}, // ints -> -1

    above{false}, below{false}, left{false}, right{false}, //neighbours -> false

    isVisited{false}, hasParents{false}, // bool checks -> false

    name{' '} {};






    /* << Operator overload*/


  friend std::ostream& operator<<( std::ostream& os, Location location) {


        os << "(" << location.x_coord + 1<< "," <<location.y_coord + 1<< ")\t";

        return os;


    }






    /* Getters and Setters */


    // neighbours

    bool getAbove()const{
        return above;

    }

    void setAbove ( bool a) {

        above = a;
    };


    bool getBelow()const{
        return below;

    }


    void setBelow ( bool b) {

        below = b;
    };



    bool getLeft()const{

        return left;

    }

    void setLeft ( bool l) {

        left = l;
    };


    bool getRight()const{
        return right;

    }
    void setRight ( bool r) {

        right = r;
    };



    // essential attributes
    void setName(char c){

        name = c;

    }

    char getName() const{
        return name;
    }


    int getCost() const{
        return cost;
    }

    void setCost(int c) {
        cost = c;
    }



    // Co-ordinate getters and setters
    int getX() const{
        return x_coord;
    }

    void setX(int x) {
        x_coord = x;
    }


    int getY() const{
        return y_coord;
    }

    void setY(int y) {
        y_coord = y;
    }



    int getParentX()const {
        return parentX;
    }
    void setParentX(int x) {
        parentX = x;
    }


    int getParentY() const {
        return parentY;
    }
    void setParentY(int y) {
        parentY = y;
    }


// bool checks

    int getVisited()const {
        return isVisited;
    }
    void setVisited(bool boolean) {
        isVisited = boolean;
    }


    bool getHasParents() const{
        return hasParents;
    }

    void setHasParents(bool boolean){
        hasParents = boolean;
    }





};



#endif //ROUTE_PLANNING_DSA_LOCATION_H
