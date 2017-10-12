//
//  DFO.hpp
//  DFO
//
//  Created by Edmund Oetgen on 12/10/2017.
//
//

#pragma once


#include "ofMain.h"
//#include "global.h"
#include "fly.hpp"

class DFO{
public:
    DFO();
    void setup(double dimensions_, int popSize_);
   // void init(double dimensions, int popSize);
    void findNeighbors(int curr);
    double returnFeature(int f);
    double evaluate (vector<double> a);
    void findBestFly();
  //  void getRandF_or_RingT_Neighbours(int curr, boolean topology);
    void run();
    void display();
    
    double Sphere(vector<double> p);
    
    double dimensions;
    int popSize;
    float dt; //disturbaance threshold
    
    int imgW, imgH;
    float width, height;
    int scaleF;
   
    vector<fly *> flies;
    int leftNeighbor;
    int rightNeighbor;
    int bestFlyIndex;
    
    int evalCount;
    int FE_allowed;
    double offset;
    
    
};