#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "DataConversion.hpp"
#include "TrainingData.hpp"
#include "TestingData.hpp"


// Enum to represent the current state of the app
enum AppState {
    DRAW_CANVAS = 0,
    RESULT
};

class ofApp : public ofBaseApp{

	public:
        map<int, string> number_to_pinyin_conversion;
        ofSoundPlayer soundPlayer;
        ofSoundPlayer chineseCharacter;
        ofPolyline line;
        AppState current_state_= DRAW_CANVAS;
        string best_estimate_pinyin;
        string chineseCharacterAudioFilePath;
        ofImage myCanvasImage;
        ofImage myChineseCharacter;
        ofImage myDisplayImage;
        ofTrueTypeFont pinyin;
        ofTrueTypeFont heading;
    
		void setup();
		void update();
		void draw();
        void exit();
        void drawCanvasMode();
        string drawResultMode();
        vector<vector<char>> convertImage();
        int detectImage(vector<vector<char>>);
        string getChineseConversion(int bestEstimate);
    
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
