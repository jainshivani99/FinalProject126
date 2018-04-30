//  TestingData.cpp
//  finalproject
//This class contains functions that relates to getting and using the training data for the program.

#include "TestingData.hpp"

using namespace std;

//Function that takes a an image as input and converts its pixels into features
//Returns the image with its features
vector<vector<int>> single_image_convert_pixels_to_features(vector<vector<char>> image_in_char) {
    vector<vector<int>> image_in_features(28, vector<int>(28));
    
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            char currentChar = image_in_char[i][j];
            if (currentChar == ' ') {
                int currentCharValue = 0;
                image_in_features[i][j] = currentCharValue;
            } else if (currentChar == '+') {
                int currentCharValue = 1;
                image_in_features[i][j] = currentCharValue;
            } else if (currentChar == '#') {
                int currentCharValue = 1;
                image_in_features[i][j] = currentCharValue;
            }
        }
    }
    return image_in_features;
}

int get_best_estimate_of_image(vector<vector<int>> currentImage, map<int, vector<vector<double>> > class_to_feature_probability,map <int, double> class_to_class_probability) {
    //go through class_to_feature_probability_test
    //calculate log formula for each value in map
    //store that into another map
    //find max value in that map and return it
    
    map<int, vector<vector<double>>> class_to_feature_probability_test;
    for (int i = 0; i < 10; i++) {
        vector<vector<double>> probabilityOfClassTest(28, vector<double>(28));
        class_to_feature_probability_test.insert(make_pair(i, probabilityOfClassTest));
    }
    
    for (map<int, vector<vector<double>>>::iterator mapIterator = class_to_feature_probability.begin();
         mapIterator != class_to_feature_probability.end(); mapIterator++) {
        vector<vector<double> > testProbabilityValues;
        //initializing the above nested vector
        for (int i = 0; i < 28; i++) {
            vector<double> currentValue(28, 0.0);
            testProbabilityValues.push_back(currentValue);
        }
        int classLabel = mapIterator->first;
        vector<vector<double> > trainingProbabilityImageValues = mapIterator->second;
        double testFeatureProbability;
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 28; j++) {
                if (currentImage[i][j] == 0) {
                    testFeatureProbability = trainingProbabilityImageValues[i][j];
                    testProbabilityValues[i][j] = testFeatureProbability;
                } else if (currentImage[i][j] == 1){
                    testFeatureProbability = 1.0 - trainingProbabilityImageValues[i][j];
                    testProbabilityValues[i][j] = testFeatureProbability;
                }
            }
        }
        class_to_feature_probability_test[classLabel] = testProbabilityValues;
    }
    
    map<int, double> class_to_posterior_probability_test;
    for (int i = 0; i < 10; i++) {
        double x = 0.0;
        class_to_posterior_probability_test.insert(make_pair(i, x));
    }
    
    for (map<int, vector<vector<double>>>::iterator pMapIterator = class_to_feature_probability_test.begin();
         pMapIterator != class_to_feature_probability_test.end(); pMapIterator++) {
        vector<vector<double>> currentProbabilityMap = pMapIterator->second;
        int currentLabel = pMapIterator->first;
        double currentClassPrior = 0.0;
        double posteriorProbability = 0.0;
        currentClassPrior = class_to_class_probability[currentLabel];
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 28; j++) {
                double currentProbability = currentProbabilityMap[i][j];
                posteriorProbability += log(currentProbability);
            }
        }
        posteriorProbability += log(currentClassPrior);
        class_to_posterior_probability_test[currentLabel] = posteriorProbability;
    }
    
    double currentMax = class_to_posterior_probability_test[0];
    int currentClass = 0;
    
    for (int i = 0; i < class_to_posterior_probability_test.size(); i++) {
        if (class_to_posterior_probability_test[i] > currentMax) {
            currentMax = class_to_posterior_probability_test[i];
            currentClass = i;
        }
    }
    
    if (currentMax <= -350.0) {
        currentClass = 10;
    }
        
    return currentClass;    
}



