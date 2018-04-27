#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "DataConversion.hpp"
#include "TrainingData.hpp"
#include "TestingData.hpp"
#include "DataEvaluation.hpp"

class ofApp : public ofBaseApp{

	public:
        multimap<map<int,double>, vector<vector<int>>> posterior_probability_global;
        ofSoundPlayer soundPlayer;
        ofPolyline line;
        bool enter_key_pressed;
        ofRectangle button;
        bool bButton;
//        ofxPanel gui;
//        ofxIntSlider countX;
//        ofxFloatSlider stepX;
//        ofxFloatSlider twistX;
    
		void setup();
		void update();
		void draw();
        void exit();
        void detectPicture();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
};
