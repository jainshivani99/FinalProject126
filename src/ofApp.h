#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "DataConversion.hpp"
#include "TrainingData.hpp"
#include "TestingData.hpp"
#include "DataEvaluation.hpp"


// Enum to represent the current state of the app
enum AppState {
    DRAW_CANVAS = 0,
    RESULT
};

class ofApp : public ofBaseApp{

	public:
        multimap<map<int,double>, vector<vector<int>>> posterior_probability_global;
        ofSoundPlayer soundPlayer;
        ofPolyline line;
        AppState current_state_= DRAW_CANVAS;
        ofImage myImage;
    
		void setup();
		void update();
		void draw();
        void exit();
        void drawCanvasMode();
        void drawResultMode();
        vector<vector<char>> convertImage();
        int detectPicture(vector<vector<char>>);

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
