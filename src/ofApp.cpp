#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Shivani's English to Chinese Number Translator");
    ofBackground(173, 216, 230);
    srand(static_cast<unsigned>(time(0))); // Seed random with current time
    
    //gui.setup();
    //ofSetFrameRate(60);
    //gui.loadFromFile("settings.xml");
    soundPlayer.load("Titanic.mp3");
    soundPlayer.play();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0, 0, 0);
    string welcome_message = "Please draw a number on the canvas";
    ofDrawBitmapString(welcome_message, 100, 100);
    ofSetColor(255,228,196);
    ofFill();
    ofDrawRectangle(150,150,700,600);
    ofSetColor(0,0,0);
    ofSetLineWidth(10.0);
    line.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    ofPoint pt;
    pt.set(x,y);
    line.addVertex(pt);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    line.clear();
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
//--------------------------------------------------------------
void ofApp::exit() {
    //gui.saveToFile("settings.xml");
}
