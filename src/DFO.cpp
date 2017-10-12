//
//  DFO.cpp
//  DFO
//
//  Created by Edmund Oetgen on 12/10/2017.
//
//

#include "DFO.hpp"

DFO::DFO(){

    width = ofGetWidth();
    height = ofGetHeight();
   
    scaleF = 5;
//    dimensions = dimensions_;
//    popSize = popSize_;
    dt = 0.01;
    
    
    evalCount = 0;
    FE_allowed = 30000;
    offset = -0.0;
    
//    flies.clear();
//    flies.resize(popSize);
//    for (int i = 0; i < flies.size(); i++ ){
//        flies[i] = new fly();
//        flies[i]->init(dimensions, imgW);
//    }
}

void DFO::setup(double dimensions_, int popSize_){
    dimensions = dimensions_;
    popSize = popSize_;
    
    imgW = 100;
    imgH =  dimensions;
    flies.clear();
    flies.resize(popSize);
    for (int i = 0; i < flies.size(); i++ ){
        flies[i] = new fly();
        flies[i]->init(dimensions, imgW);
    }
}

//taken from Mohammad Majid al-Rifaie's example code in java
void DFO::findNeighbors(int curr){
double minDL = 10E15;
for (int i = 0; i < popSize; i++) {
    if (i == curr)
        continue;
    
    double d = flies[curr]->getDistanceSquared(flies[i]->returnFeatureVector());
    if (d < minDL) {
        minDL = d;
        leftNeighbor = i;
    }
}

    double minDR = 10E15;
for (int i = 0; i < popSize; i++) {
    if (i == curr)
        continue;
    if (i == leftNeighbor)
        continue;
    
    double d = flies[curr]->getDistanceSquared(flies[i]->returnFeatureVector());
    if (d < minDR) {
        minDR = d;
        rightNeighbor = i;
    }
}

// println( leftN + " :: " + rightN );

}

double DFO::evaluate(vector<double> a) {
    evalCount++;
    return abs( Sphere(a) );
    // Sphere Schwefel12 Rosenbrock GSchwefel26
    // Rastrigin Ackley Griewank PenalizedP8 PenalizedP16
}

void DFO::findBestFly() {
    double min = 10E10;
    
    for (int i = 0; i < popSize; i++) {
        if (flies[i]->getFitness() < min) {
            min = flies[i]->getFitness();
            bestFlyIndex = i;
        }
    }
}

//void DFO::getRandF_or_RingT_Neighbours(int curr, boolean topology) {
//    
//    if (topology) // RING
//    {
//        Global.leftN = curr - 1;
//        Global.rightN = curr + 1;
//        
//        if (curr == 0)
//            Global.leftN = Global.popSize - 1;
//        if (curr == Global.popSize - 1)
//            Global.rightN = 0;
//    }
//    else // RANDOM
//    {
//        Global.leftN = r.nextInt(Global.popSize);
//        while (Global.leftN == curr)
//            Global.leftN = r.nextInt(Global.popSize);
//        
//        Global.rightN = r.nextInt(Global.popSize);
//        while ((Global.rightN == curr) || (Global.rightN == Global.leftN))
//            Global.rightN = r.nextInt(Global.popSize);
//    } 
//    
//}

void DFO::run(){

    if (evalCount < FE_allowed) {
        // EVALUATION Phase
        for (int i = 0; i < popSize; i++)
        {
            flies[i]->setFitness(evaluate(flies[i]->returnFeatureVector()));
            //if ( Global.evalCount % 1000 == 0 ) dt = dt/2;
        }
        
        findBestFly();
        
        // INTERACTION Phase
        for (int i = 0; i < popSize; i++) {
            if (i == bestFlyIndex)
                continue;
            
             findNeighbors(i);
          //  utils.getRandF_or_RingT_Neighbours(i, true);
            // println(leftN + " :: " + i + " :: " + rightN);
            // double leftD = Global.fly[i].getDistance(Global.leftN);
            // double rightD = Global.fly[i].getDistance(Global.rightN);
            
            // neighbours
            double leftP, rightP;
            if (true) {
                leftP = flies[leftNeighbor]->getFitness();// leftD *
                // fly[leftN].getFitness();
                rightP = flies[rightNeighbor]->getFitness();// rightD *
                // fly[rightN].getFitness();
            }
            // else // suitable for gradual and non-steep hills
            // {
            // leftP = leftD * fly[leftN].getFitness();
            // rightP = rightD * fly[rightN].getFitness();
            // }
            
            int chosen;
            if (leftP < rightP)
                chosen = leftNeighbor;
            else
                chosen = rightNeighbor;
            
            int dCounter = 0;
            // ================ Apply the update equation
            // =======================
            vector<double> temp;
            temp.resize(dimensions);
            
            for (int d = 0; d < dimensions; d++) {
                temp[d] = flies[chosen]->getFeature(d) +
                ofRandom(1.0) * (flies[bestFlyIndex]->getFeature(d) - flies[i]->getFeature(d));// FINAL
                
                
                // disturbance mechanism
                if (true)
                    if (ofRandom(1.0) < dt)
                    {
                        temp[d] = //utils.getGaussian(Global.imgW/2.0, Global.imgW/2.0);//
                        ofRandom(-imgW, imgW);
                        dCounter++;
                    }
            }
            
            //println("Disturbances in Fly  #" + i + ": \t" + dCounter);
           flies[i]->setFeatureVector(temp);
            
        } // end of interaction phase
        
    }
}

double DFO::Sphere(vector<double> p) {
    double a = 0;
    for (int i = 0; i < dimensions; i++) {
        a = a + pow(p[i] + offset, 2);
    }
    //Global.funcName = "Sphere";
    return a;
}

void DFO::display(){

    // Draw the flies and update their positions
    for (int i = 0; i < popSize; i++) {
       // fill(255 / popSize, 255 / popSize, 255 / popSize);
        ofSetColor(255, 255, 255);
        
        // draw the axis (i.e. X and Y axis)
        if (true) {
            ofSetColor(200, 200, 200, 5);
            ofSetLineWidth((float) 10.5);
            ofLine(width / 2, 0, width / 2, height); // y
//            if (mode_2D)
//                line(0, height / 2, width, height / 2); // x
//        }
        
        // ======================= Visualising the flies on the canvas
        // ========================================
        // ========================================
        ofPushMatrix();
        ofTranslate(imgW * scaleF / 2, imgH * scaleF / 2);
        
        // EVERY 2D together (true) :: EACH D separate (false)
//        if (Global.mode_2D) {
//            for (int d = 0; d < Global.dim - 2; d = d + 2)
//                // for ( int d = 0; d < 1; d++ )
//            {
//                int eSize = 5; // ellipse size
//                if (i == Global.bestIndex) // make the colour of the best particle
//                    // RED and twice the size
//                {
//                    fill(255, 0, 0);
//                    eSize = eSize * 2;
//                }
//                stroke(255, 255, 255);
//                strokeWeight(0);
//                ellipse((float) Global.fly[i].getPos(d) * Global.scaleF / 2,
//                        (float) Global.fly[i].getPos(d + 1) * Global.scaleF / 2, eSize,
//                        eSize);
//                
//                stroke(0);
//                strokeWeight((float) 0.1);
//                line((float) Global.fly[i].getPos(d) * Global.scaleF / 2,
//                     (float) Global.fly[i].getPos(d + 1) * Global.scaleF / 2,
//                     (float) Global.fly[i].getExPos(d) * Global.scaleF / 2,
//                     (float) Global.fly[i].getExPos(d + 1) * Global.scaleF / 2);
//            }
//        } else // show each Dimension separately
//        {
            int gap = height / (dimensions + 1);
            for (int d = 0; d < dimensions; d++) {
                ofSetColor(0, 0, 0, 100);
                ofSetLineWidth((float) 0.3);
                // line( (float)fly[i].getHypo(d)*scaleF/2,
                // (float)fly[i].getHypo(d+1)*scaleF/2,
                // (float)fly[i].xhypo[d]*scaleF/2,
                // (float)fly[i].xhypo[d+1]*scaleF/2 );
                
                // Horizontal Lines
                int xGap = imgW * scaleF / 2;
                int yGap = -imgW * scaleF / 2 + gap * (d + 1);
                
                ofLine(-xGap, yGap, xGap, yGap);
                
                // flies position
                int eSize = 5;
                if (i == bestFlyIndex) {
                    ofSetColor(255, 0, 0);
                    eSize = eSize * 2;// 5;
                }else{
                ofSetColor(0);
                }
                // strokeWeight(1);
                ofDrawEllipse((float) flies[i]->getFeature(d) * scaleF / 2, yGap, eSize, eSize);
                
           // }
        }
        
        ofPopMatrix();
        
    }

}


}

