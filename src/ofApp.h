#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "DataConversion.hpp"
#include "TrainingData.hpp"
#include "TestingData.hpp"


//Enum to represent the current state of the app
//User starts at DRAW_CANVAS then goes to RESULT
//Can switch between two states by the keyPressed(int key) function
enum AppState {
    DRAW_CANVAS = 0,
    RESULT,
};

class ofApp : public ofBaseApp{

	public:
        //Sound player objects to play sound
        ofSoundPlayer sound_player_;
        ofSoundPlayer chinese_character_;
    
        //Line object to draw a line on the canvas
        ofPolyline line_;
        AppState current_state_= DRAW_CANVAS;
    
        //Class variables that store variables relating to main logic (english to chinese conversion)
        map<int, string> number_to_pinyin_conversion_;
        string best_estimate_pinyin_;
        int best_estimate_;
        string chinese_character_audio_file_path_;
    
        //Image objects to display images
        ofImage my_canvas_image_;
        ofImage my_chinese_character_;
        ofImage my_display_image_;
    
        //ofTrueTypeFont objects to display text in a cutomized font
        ofTrueTypeFont pinyin_;
        ofTrueTypeFont heading_;
    
        //Functions that help set up/modify the application
		void setup();
		void draw();
        void drawCanvasMode();
        void drawResultMode();
        void keyPressed(int key);
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
    
        //Functions that are related to main logic (english to chinese conversion)
        void detectImage(vector<vector<char>>);
        void getChineseConversion();
        vector<vector<char>> convertImage();

};
