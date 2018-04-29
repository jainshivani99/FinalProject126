#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Shivani's English to Chinese Number Translator");
    ofBackground(173, 216, 230);
    srand(static_cast<unsigned>(time(0))); // Seed random with current time
    
    soundPlayer.load("Titanic.mp3");
    soundPlayer.play();
    //soundPlayer.setVolume(0.1f);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    if (current_state_ == DRAW_CANVAS) {
        drawCanvasMode();
    } else if(current_state_ == RESULT) {
        drawResultMode();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    int upper_key = toupper(key); // Standardize on upper case
    if (current_state_ == DRAW_CANVAS) {
        if (upper_key == OF_KEY_RETURN) {
            //process the picture the user drew
            myCanvasImage.grabScreen(150, 150, 588, 588);
            //myCanvasImage.save("User.png");
            vector<vector<char>> image_in_char = convertImage();
            current_state_ = RESULT;
            int bestEstimate = detectImage(image_in_char);
            best_estimate_pinyin = getChineseConversion(bestEstimate);
        }
    } else if (current_state_ == RESULT) {
        if (upper_key == 'Q') {
            current_state_ = DRAW_CANVAS;
        }
    }
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
    
}
//--------------------------------------------------------------
void ofApp::drawCanvasMode() {
    //displays welcome message at the top of the screen
    ofSetColor(0, 0, 0);
    string welcome_message = "Please draw a number on the canvas";
    ofDrawBitmapString(welcome_message, 100, 100);
    
    //features to set up the canvas
    ofSetColor(255,228,196);
    ofFill();
    ofDrawRectangle(150,150,588,588);
    
    //features to draw the line
    ofSetColor(0,0,0);
    ofSetLineWidth(60.0);
    line.draw();
    
    //displays message to press enter once to submit the picture
    string enter_message = "Press Enter to Submit";
    ofDrawBitmapString(enter_message, 870, 720);
    
    //displays message to clear the canvas
    string clear_message = "Click anywhere to clear";
    ofDrawBitmapString(clear_message, 870, 670);
    
}
//--------------------------------------------------------------
void ofApp::drawResultMode() {
    //displays submission message at the top of the screen
    ofSetColor(0, 0, 0);
    string submission_message = "Results of your submission:";
    ofDrawBitmapString(submission_message, 100, 100);
    
    //displays message to press Q to exit result mode
    string quit_message = "Press Q to exit";
    ofDrawBitmapString(quit_message, 870, 720);
    
    //displays the appropriate chinese character
    
    
}
//--------------------------------------------------------------
vector<vector<char>> ofApp::convertImage() {
    myCanvasImage.setImageType(OF_IMAGE_GRAYSCALE);
    vector< vector<char> > image_in_char(28, vector<char> (28));
    ofPixels & pixels = myCanvasImage.getPixels();
    //going through 2D vector image_in_char
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            int sum = 0;
            for (int r = i * 21; r < (i * 21) + 21; r++) {
                for (int c = j * 21; c < (j * 21) + 21; c++) {
                    int index = 588 * r + c;
                    sum += pixels[index];
                }
            }
            double average = sum / 441.0;
            char current_char;
            if (average >= 0 && average <= 50.0) {
                current_char = '#';
            } else if (average >= 50.0 && average <= 100.0) {
                current_char = '+';
            } else if (average >= 100.0) {
                current_char = ' ';
            }
            image_in_char[i][j] = current_char;
        }
    }
    //prints out the image to test
    for (int i = 0; i < image_in_char.size(); i++) {
        for (int j = 0; j < image_in_char[i].size(); j++)
        {
            cout << image_in_char[i][j];
        }
        cout << endl;
    }
    
    return image_in_char;
}
//--------------------------------------------------------------
int ofApp::detectImage(vector<vector<char>> image_in_char) {
    
    /*Training Data*/
    
    //function that initially gets the training data and organizes it
    multimap <int, vector< vector<char> >> associated_label_and_image = get_labels_and_images("/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/Images/traininglabels", "/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/Images/trainingimages");

    //function that converts the pixels of images in training data to features
    multimap <int, vector< vector<int> >> associated_label_and_image_features = convert_pixels_to_features(associated_label_and_image);

    //function that calculates the probability of each feature for each class
    map<int, vector<vector<double>> > class_to_feature_probability =
    calculate_probability_of_training_data_features(associated_label_and_image_features);
    
    //function that calculates the probability of each class
    map<int, double> class_to_class_probability = calculate_probability_of_training_data_classes(associated_label_and_image_features);
    
    /*Test Data*/
    
    //function that converts the pixels of an image in test data to features
    vector<vector<int>> image_in_features = single_image_convert_pixels_to_features(image_in_char);
    
    //function that returns the best estimate of the image
    int bestEstimate = get_best_estimate_of_image(image_in_features, class_to_feature_probability, class_to_class_probability);
    
    cout << bestEstimate << endl;
    return bestEstimate;
}
//--------------------------------------------------------------
string ofApp::getChineseConversion(int bestEstimate) {
    //Setting up the map that stores a number and its associated pinyin (chinese translation)
    //key - number (0-9)
    //value - string (pinyin)
    for (int i = 0; i < 10; i++) {
        number_to_pinyin_conversion[i];
    }
    number_to_pinyin_conversion[0] = "Líng";
    number_to_pinyin_conversion[1] = "Yī";
    number_to_pinyin_conversion[2] = "Èr";
    number_to_pinyin_conversion[3] = "Sān";
    number_to_pinyin_conversion[4] = "Sì";
    number_to_pinyin_conversion[5] = "Wǔ";
    number_to_pinyin_conversion[6] = "Liù";
    number_to_pinyin_conversion[7] = "Qī";
    number_to_pinyin_conversion[8] = "Bā";
    number_to_pinyin_conversion[9] = "Jiǔ";
    
    string best_estimate_pinyin = number_to_pinyin_conversion[bestEstimate];
    return best_estimate_pinyin;
}

