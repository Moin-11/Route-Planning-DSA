//
// Created by moin_11 on 3/20/21.
//

#include<vector>

#ifndef ROUTE_PLANNING_DSA_LOCATION_H
#define ROUTE_PLANNING_DSA_LOCATION_H

class Location{
private:
    int row, column;
    char object;
    vector<Location> neighbours;

public:
    Location(int r, int c, char obj = " ", vector<Location> nebs) : row{r}, column{c}, object{obj}, neighbours{nebs} {};
    Location(int r, int c, char obj = " ") : row{r}, column{c}, object{obj} {};




};



#endif //ROUTE_PLANNING_DSA_LOCATION_H
