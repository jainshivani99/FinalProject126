#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "DataConversion.hpp"
#include "TrainingData.hpp"
#include "TestingData.hpp"


// Enum to represent the current state of the app
enum AppState {
    DRAW_CANVAS = 0,
    RESULT,
};

class ofApp : public ofBaseApp{

	public:
        map<int, string> number_to_pinyin_conversion_;
        ofSoundPlayer sound_player_;
        ofSoundPlayer chinese_character_;
        ofPolyline line_;
        AppState current_state_= DRAW_CANVAS;
        string best_estimate_pinyin_;
        int best_estimate_;
        string chinese_character_audio_file_path_;
        ofImage my_canvas_image_;
        ofImage my_chinese_character_;
        ofImage my_display_image_;
        ofTrueTypeFont pinyin_;
        ofTrueTypeFont heading_;
    
		void setup();
		void draw();
        void drawCanvasMode();
        void drawResultMode();
        void detectImage(vector<vector<char>>);
        void getChineseConversion();
        vector<vector<char>> convertImage();
    
		void keyPressed(int key);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
    
};
