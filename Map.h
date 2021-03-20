//
// Created by moin_11 on 3/20/21.
//

#include<vector>
#ifndef ROUTE_PLANNING_DSA_MAP_H
#define ROUTE_PLANNING_DSA_MAP_H


class Map {
private:
    int width, height;
    vector<vector> locations;


public:
    Map(int w, int h, vector<vector> loc) : width{w}, height{h}, locations{loc} {}

    Map(int w, int h) : width{w}, height{h}{}



};


#endif //ROUTE_PLANNING_DSA_MAP_H
