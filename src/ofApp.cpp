#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowTitle("Shivani's English to Chinese Number Translator");
    ofBackground(173, 216, 230);
    srand(static_cast<unsigned>(time(0))); // Seed random with current time
    
    //gui.setup();
    //ofSetFrameRate(60);
    //gui.loadFromFile("settings.xml");
    //soundPlayer.load("Titanic.mp3");
    //soundPlayer.play();
    
//    button.set(870,700,130,30);
//    bButton = false;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0, 0, 0);
    string welcome_message = "Please draw a number on the canvas";
    ofDrawBitmapString(welcome_message, 100, 100);
    
    //features to set up the canvas
    ofSetColor(255,228,196);
    ofFill();
    ofDrawRectangle(150,150,700,600);
    
    //features to draw the line
    ofSetColor(0,0,0);
    ofSetLineWidth(10.0);
    line.draw();
    
    string enter_message = "Press Enter to Submit";
    ofDrawBitmapString(enter_message, 870, 720);
    //ofSetColor(220,220,220);
    //ofRect(button);
    
    if (enter_key_pressed) {
        ofSetColor(0, 0, 0);
        string key_pressed_message = "Enter Key Pressed";
        ofDrawBitmapString(key_pressed_message, 870, 700);
        //enter_key_pressed = false;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    int upper_key = toupper(key); // Standardize on upper case
    if (upper_key == OF_KEY_RETURN) {
        cout << "Enter key pressed 2" << endl;
        enter_key_pressed = true;
        //detectPicture();
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
    
//    if(button.distance(ofPoint) {
//        bButton = !bButton;
//    }
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
//--------------------------------------------------------------
void ofApp::detectPicture() {
    /*Training Data*/
    
    //function that initially gets the data and organizes it
    //this is first done for the training data
    multimap <int, vector< vector<char> >> associated_label_and_image = get_labels_and_images("/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/traininglabels", "/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/trainingimages");
    //    for (multimap<int, vector<vector<char>>>::const_iterator it = associated_label_and_image.begin();
    //        it != associated_label_and_image.end(); ++it) {
    //        cout << it->first << endl;
    //        vector<vector<char> > currentImage = it->second;
    //        for (int i = 0; i < currentImage.size(); i++)
    //        {
    //            for (int j = 0; j < currentImage[i].size(); j++)
    //            {
    //                cout << currentImage[i][j];
    //            }
    //            cout << endl;
    //        }
    //
    //    }
    
    
    //function that converts the pixels of images in training data to features
    multimap <int, vector< vector<int> >> associated_label_and_image_features = convert_pixels_to_features(associated_label_and_image);
    //    for (multimap<int, vector<vector<int>>>::const_iterator it = associated_label_and_image_features.begin(); it != associated_label_and_image_features.end(); ++it) {
    //        cout << it->first << endl;
    //        vector<vector<int> > currentImage = it->second;
    //        for (int i = 0; i < currentImage.size(); i++)
    //        {
    //            for (int j = 0; j < currentImage[i].size(); j++)
    //            {
    //                cout << currentImage[i][j];
    //            }
    //            cout << endl;
    //        }
    //
    //    }
    
    
    //function that calculates the probability of each feature for each class
    map<int, vector<vector<double>> > class_to_feature_probability =
    calculate_probability_of_training_data_features(associated_label_and_image_features);
    //    for (map<int, vector<vector<double>>>::const_iterator it = class_to_feature_probability.begin(); it != class_to_feature_probability.end(); ++it) {
    //        cout << it->first << endl;
    //        vector<vector<double> > currentProbabilityImage = it->second;
    //        for (int i = 0; i < currentProbabilityImage.size(); i++)
    //        {
    //            for (int j = 0; j < currentProbabilityImage[i].size(); j++)
    //            {
    //                cout << currentProbabilityImage[i][j] << " ";
    //            }
    //            cout << endl;
    //        }
    //    }
    
    
    //function that calculates the probability of each class
    map<int, double> class_to_class_probability = calculate_probability_of_training_data_classes(associated_label_and_image_features);
    
    
    //*Test Data*//*
    
    //function that initially gets the data and organizes it
    // this done for test data, where only the images are available (labels are still kept in the map)
    multimap <int, vector< vector<char> > > associated_label_and_image_test =
    get_labels_and_images("/Users/shivanijain/CLionProjects/naivebayes-jainshivani99/data/testlabels",
                          "/Users/shivanijain/CLionProjects/naivebayes-jainshivani99/data/testimages");
    //    for (multimap<int, vector<vector<char>>>::const_iterator it = associated_label_and_image_test.begin();
    //         it != associated_label_and_image_test.end(); ++it) {
    //        cout << it->first << endl;
    //        vector<vector<char> > currentImage = it->second;
    //        for (int i = 0; i < currentImage.size(); i++)
    //        {
    //            for (int j = 0; j < currentImage[i].size(); j++)
    //            {
    //                cout << currentImage[i][j];
    //            }
    //            cout << endl;
    //        }
    //
    //    }
    
    
    //function that converts the pixels of images in test data to features
    multimap <int, vector< vector<int> > > associated_label_and_image_features_test =
    convert_pixels_to_features(associated_label_and_image_test);
    //    for (multimap<int, vector<vector<int>>>::const_iterator it = associated_label_and_image_features_test.begin(); it != associated_label_and_image_features_test.end(); ++it) {
    //        cout << it->first << endl;
    //        vector<vector<int> > currentImage = it->second;
    //        for (int i = 0; i < currentImage.size(); i++)
    //        {
    //            for (int j = 0; j < currentImage[i].size(); j++)
    //            {
    //                cout << currentImage[i][j];
    //            }
    //            cout << endl;
    //        }
    //
    //    }
    
    
    multimap <vector<int>, vector< vector<int>>> best_estimate_values = test_data_function(associated_label_and_image_features_test, class_to_feature_probability,
                                                                                           class_to_class_probability);
    //    for (multimap< vector<int>, vector<vector<int>>>::const_iterator it = best_estimate_values.begin(); it != best_estimate_values.end(); ++it) {
    //        vector<int> classValues = it->first;
    //        for (vector<int>::const_iterator i = classValues.begin(); i != classValues.end(); ++i) {
    //            cout << *i << endl;
    //        }
    //        vector<vector<int> > currentImage = it->second;
    //        for (int i = 0; i < currentImage.size(); i++)
    //        {
    //            for (int j = 0; j < currentImage[i].size(); j++)
    //            {
    //                cout << currentImage[i][j];
    //            }
    //            cout << endl;
    //        }
    //    }
    
    
    //*Data Evaluation*//*
    
    
    vector<vector<double>> percentage_confusion_matrix = create_confusion_matrix(best_estimate_values);
    print_confusion_matrix(percentage_confusion_matrix);
    multimap<int, vector<vector<int>>> posterior_probability_images = calculate_prototypicals_per_class(posterior_probability_global);
    print_prototypicals_per_class(posterior_probability_images);
    
    //    for (multimap<int, vector<vector<int>>>::const_iterator it = posterior_probability_images.begin(); it != posterior_probability_images.end(); ++it) {
    //        cout << it->first << endl;
    //        vector<vector<int> > currentImage = it->second;
    //        for (int i = 0; i < currentImage.size(); i++)
    //        {
    //            for (int j = 0; j < currentImage[i].size(); j++)
    //            {
    //                cout << currentImage[i][j];
    //            }
    //            cout << endl;
    //        }
    //
    //    }

}
