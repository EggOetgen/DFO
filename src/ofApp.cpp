#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
   
    DFO.setup(100,10);
    ofSetWindowShape(DFO.imgW * DFO.scaleF, DFO.imgH * DFO.scaleF);
}

//--------------------------------------------------------------
void ofApp::update(){
    DFO.run();
    cout << DFO.flies[DFO.bestFlyIndex]->returnFeatureVector()[0] << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
    DFO.display();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
