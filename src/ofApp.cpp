//This class includes the functionality for running the application, such as taking user input, drawing the canvas, and displaying results

#include "ofApp.h"

//Sets up the background of the application with a title, background color of the window, and background music
//--------------------------------------------------------------
void ofApp::setup(){
    //Displays window title and background color
    ofSetWindowTitle("Shivani's English to Chinese Number Translator");
    ofBackground(173, 216, 230);
    srand(static_cast<unsigned>(time(0))); // Seed random with current time
    
    //Loads customized font to be used throughout the program
    pinyin_.load("TimesPinyin", 30);
    heading_.load("Raleway-SemiBoldItalic.ttf", 30);
    
    //Plays background music on an infinite loop
    if (true) {
        sound_player_.load("Titanic.mp3");
        sound_player_.play();
        sound_player_.setVolume(0.1f);
    }
}

//Draws graphics on the window depending on the current state of the application
//2 states: DRAW_CANVAS, RESULT
//--------------------------------------------------------------
void ofApp::draw(){
    //calls drawCanvasMode() if the user is currently on the DRAW_CANVAS state
    if (current_state_ == DRAW_CANVAS) {
        drawCanvasMode();
    }
    //calls drawResultMode() if the user is currently on the RESULT state
    else if(current_state_ == RESULT) {
        drawResultMode();
    }
}

//Performs different functions depending on which key the user presses and what state the user is in currently in the application
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    int upper_key = toupper(key); // Standardize on upper case
    
    //Can only perform these functions if they are in the DRAW_CANVAS state
    if (current_state_ == DRAW_CANVAS) {
        if (upper_key == OF_KEY_RETURN) {
            //processes the picture the user drew and saves it
            my_canvas_image_.grabScreen(150, 150, 588, 588);
            my_canvas_image_.save("User.png");
            
            //calls convertImage() to convert it to the desired format
            vector<vector<char>> image_in_char = convertImage();
            
            //changes the state of the application to the RESULT state
            current_state_ = RESULT;
            
            //detects the image as a number and gets the chinese conversion
            detectImage(image_in_char);
            getChineseConversion();
        }
    }
    //Can only perform these functions if they are in the RESULT state
    else if (current_state_ == RESULT) {
        if (upper_key == 'Q') {
            //Exits out of the RESULT state and returns to DRAW_CANVAS state
            current_state_ = DRAW_CANVAS;
        } else if (upper_key == 'P') {
            //Plays the audio of the chinese pronunciation
            chinese_character_.load(chinese_character_audio_file_path_);
            chinese_character_.play();
        }
    }
}

//Draws a line when the user presses and drags the cursor
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    ofPoint pt;
    pt.set(x,y);
    line_.addVertex(pt);
}

//Clears the line the user draws by clicking the mouse
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    line_.clear();
}

//Draws graphics when the user is currently in the DRAW_CANVAS state
//--------------------------------------------------------------
void ofApp::drawCanvasMode() {
    //Displays welcome message at the top of the screen
    ofSetColor(0, 0, 0);
    string welcome_message = "Please draw a number on the canvas";
    heading_.drawString(welcome_message, 100, 100);
    
    //Features to set up the canvas
    ofSetColor(255,228,196);
    ofFill();
    ofDrawRectangle(150,150,588,588);
    
    //Features to draw the line
    ofSetColor(0,0,0);
    ofSetLineWidth(100.0);
    line_.draw();
    
    //Displays message to press enter once to submit the picture
    string enter_message = "Press Enter to Submit";
    ofDrawBitmapString(enter_message, 870, 720);
    
    //Displays message to clear the canvas
    string clear_message = "Click anywhere to clear";
    ofDrawBitmapString(clear_message, 870, 670);
    
}

//Draws graphics when the user is currently in the RESULT state
//--------------------------------------------------------------
void ofApp::drawResultMode() {
    //Displays submission message at the top of the screen
    ofSetColor(0, 0, 0);
    string submission_message = "Results of your submission:";
    ofDrawBitmapString(submission_message, 100, 100);
    
    //Displays message to press Q to exit result mode
    string quit_message = "Press Q to exit";
    ofDrawBitmapString(quit_message, 870, 720);
    
    //Displays message to press P to listen to audio
    string play_message = "Press P to play audio";
    ofDrawBitmapString(play_message, 870, 490);
    
    //Displays header for chinese output
    ofDrawBitmapString("Chinese:", 870, 390);
    
    //Displays header for english picture output
    ofDrawBitmapString("Your submission picture:", 870, 70);
    
    //Displays header for english output
    ofDrawBitmapString("English:", 870, 270);
    
    //Displays picture of the user's submission
    my_display_image_.setImageType(OF_IMAGE_COLOR_ALPHA);
    my_display_image_.load("/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/User.png");
    ofSetColor(255);
    my_display_image_.draw(870,90,150,150);
    
    //Displays the appropriate chinese character, english number, and chinese pinyin
    //Associates the correct audio file to play with the correct chinese number
    if (best_estimate_pinyin_ == "Ling") {
        my_chinese_character_.load("/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/Images/ling.png");
        my_chinese_character_.draw(150,150,588,588);
        ofSetColor(0);
        pinyin_.drawString("0 - Zero", 870, 320);
        pinyin_.drawString("Líng", 870, 440);
        chinese_character_audio_file_path_ = "00.mp3";
    } else if (best_estimate_pinyin_ == "Yi") {
        my_chinese_character_.load("/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/Images/yi.png");
        my_chinese_character_.draw(150,150,588,588);
        ofSetColor(0);
        pinyin_.drawString("1 - One", 870, 320);
        pinyin_.drawString("Yï", 870, 440);
        chinese_character_audio_file_path_ = "01.mp3";
    } else if (best_estimate_pinyin_ == "Er") {
        my_chinese_character_.load("/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/Images/er.png");
        my_chinese_character_.draw(150,150,588,588);
        ofSetColor(0);
        pinyin_.drawString("2 - Two", 870, 320);
        pinyin_.drawString("Èr", 870, 440);
        chinese_character_audio_file_path_ = "02.mp3";
    } else if (best_estimate_pinyin_ == "San") {
        my_chinese_character_.load("/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/Images/san.png");
        my_chinese_character_.draw(150,150,588,588);
        ofSetColor(0);
        pinyin_.drawString("3 - Three", 870, 320);
        pinyin_.drawString("Sän", 870, 440);
        chinese_character_audio_file_path_ = "03.mp3";
    } else if (best_estimate_pinyin_ == "Si") {
        my_chinese_character_.load("/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/Images/si.png");
        my_chinese_character_.draw(150,150,588,588);
        ofSetColor(0);
        pinyin_.drawString("4 - Four", 870, 320);
        pinyin_.drawString("Sì", 870, 440);
        chinese_character_audio_file_path_ = "04.mp3";
    } else if (best_estimate_pinyin_ == "Wu") {
        my_chinese_character_.load("/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/Images/wu.png");
        my_chinese_character_.draw(150,150,588,588);
        ofSetColor(0);
        pinyin_.drawString("5 - Five", 870, 320);
        pinyin_.drawString("Wû", 870, 440);
        chinese_character_audio_file_path_ = "05.mp3";
    } else if (best_estimate_pinyin_ == "Liu") {
        my_chinese_character_.load("/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/Images/liu.png");
        my_chinese_character_.draw(150,150,588,588);
        ofSetColor(0);
        pinyin_.drawString("6 - Six", 870, 320);
        pinyin_.drawString("Liù", 870, 440);
        chinese_character_audio_file_path_ = "06.mp3";
    } else if (best_estimate_pinyin_ == "Qi") {
        my_chinese_character_.load("/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/Images/qi.png");
        my_chinese_character_.draw(150,150,588,588);
        ofSetColor(0);
        pinyin_.drawString("7 - Seven", 870, 320);
        pinyin_.drawString("Qï", 870, 440);
        chinese_character_audio_file_path_ = "07.mp3";
    } else if (best_estimate_pinyin_ == "Ba") {
        my_chinese_character_.load("/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/Images/ba.png");
        my_chinese_character_.draw(150,150,588,588);
        ofSetColor(0);
        pinyin_.drawString("8 - Eight", 870, 320);
        pinyin_.drawString("Bä", 870, 440);
        chinese_character_audio_file_path_ = "08.mp3";
    } else if (best_estimate_pinyin_ == "Jiu") {
        my_chinese_character_.load("/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/Images/jiu.png");
        my_chinese_character_.draw(150,150,588,588);
        ofSetColor(0);
        pinyin_.drawString("9 - Nine", 870, 320);
        pinyin_.drawString("Jiû", 870, 440);
        chinese_character_audio_file_path_ = "09.mp3";
    } else if (best_estimate_pinyin_ == "Not a valid entry") {
        my_chinese_character_.load("/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/Images/face.png");
        my_chinese_character_.draw(150,150,588,588);
        ofSetColor(0);
        heading_.drawString("Not a valid entry, please draw again", 100, 140);
        pinyin_.drawString("Not Found", 870, 320);
        pinyin_.drawString("Not Found", 870, 440);
        chinese_character_audio_file_path_ = "Error.mp3";
    }
}

//Converts the image the user submits to the desired format of characters #, +, and ' ' to enter it into the classifier
//--------------------------------------------------------------
vector<vector<char>> ofApp::convertImage() {
    //Converts image to gray scale
    my_canvas_image_.setImageType(OF_IMAGE_GRAYSCALE);
    
    //Sets up nested vector of chars to hold the final, downsized image
    vector< vector<char> > image_in_char(28, vector<char> (28));
    
    //Gets the pixels of my_canvas_image in a singular array
    ofPixels & pixels = my_canvas_image_.getPixels();
    
    //Going through 2D vector image_in_char
    for (int i = 0; i < kDesiredImageSize; i++) {
        for (int j = 0; j < kDesiredImageSize; j++) {
            int sum = 0;
            //Accesses a block of pixels from pixels (array of pixels of my_canvas_image)
            //Calculates the average of the gray scale numbers of these pixels in order to downsize the image to 28 x 28 (desired image size)
            for (int r = i * kPatchNumPixels; r < (i * kPatchNumPixels) + kPatchNumPixels; r++) {
                for (int c = j * kPatchNumPixels; c < (j * kPatchNumPixels) + kPatchNumPixels; c++) {
                    int index = kTotalCanvasNumPixels * r + c;
                    sum += pixels[index];
                }
            }
            double average = sum / kTotalPatchNumPixels;
            char current_char;
            
            //associates the average value to a character and stores that character within the nested vector image_in_char
            if (average >= 0 && average <= kBlackUpperBound) {
                current_char = '#';
            } else if (average >= kBlackUpperBound && average <= kGrayUpperBound) {
                current_char = '+';
            } else if (average >= kGrayUpperBound) {
                current_char = ' ';
            }
            image_in_char[i][j] = current_char;
        }
    }
    return image_in_char;
}

//Classifies image that user drew as a number by passing it through the Naive Bayes classifier
//--------------------------------------------------------------
void ofApp::detectImage(vector<vector<char>> image_in_char) {
    
    /*Training Data*/
    
    //Function that initially gets the training data and organizes it
    multimap <int, vector< vector<char> >> associated_label_and_image = get_labels_and_images("/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/Images/traininglabels", "/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/Images/trainingimages");

    //Function that converts the pixels of images in training data to features
    multimap <int, vector< vector<int> >> associated_label_and_image_features = convert_pixels_to_features(associated_label_and_image);

    //Function that calculates the probability of each feature for each class
    map<int, vector<vector<double>> > class_to_feature_probability =
    calculate_probability_of_training_data_features(associated_label_and_image_features);
    
    //Function that calculates the probability of each class
    map<int, double> class_to_class_probability = calculate_probability_of_training_data_classes(associated_label_and_image_features);
    
    /*Test Data*/
    
    //Function that converts the pixels of an image in test data to features
    vector<vector<int>> image_in_features = single_image_convert_pixels_to_features(image_in_char);
    
    //Function that returns the best estimate of the image
    best_estimate_ = get_best_estimate_of_image(image_in_features, class_to_feature_probability, class_to_class_probability);
    
}

//Accesses the chinese conversion of the classified image
//--------------------------------------------------------------
void ofApp::getChineseConversion() {
    //Setting up the map that stores a number and its associated pinyin (chinese translation)
    //key - number (0-10) (10 - not a valid entry)
    //value - string (pinyin)
    for (int i = 0; i < 11; i++) {
        number_to_pinyin_conversion_[i];
    }
    
    //Storing associated pinyin (chinese translation) to english number
    number_to_pinyin_conversion_[0] = "Ling";
    number_to_pinyin_conversion_[1] = "Yi";
    number_to_pinyin_conversion_[2] = "Er";
    number_to_pinyin_conversion_[3] = "San";
    number_to_pinyin_conversion_[4] = "Si";
    number_to_pinyin_conversion_[5] = "Wu";
    number_to_pinyin_conversion_[6] = "Liu";
    number_to_pinyin_conversion_[7] = "Qi";
    number_to_pinyin_conversion_[8] = "Ba";
    number_to_pinyin_conversion_[9] = "Jiu";
    number_to_pinyin_conversion_[10] = "Not a valid entry";
    
    //Assigns best_estimate_pinyin_ to the value at this map's best_estimate_ key
    best_estimate_pinyin_ = number_to_pinyin_conversion_[best_estimate_];
}
