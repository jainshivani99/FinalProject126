//  TestingData.cpp
//  finalproject
//This class contains functions that relates to getting and using the training data for the program.

#include "TestingData.hpp"

using namespace std;

int get_best_estimate_of_image(vector<vector<int>> currentImage, map<int, vector<vector<double>> > class_to_feature_probability,map <int, double> class_to_class_probability, int currentLabel) {
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
        //class_to_posterior_probability_test[currentLabel] = abs(posteriorProbability);
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
    //if the best estimate value is equal to the actual label of the image (it was correctly classified), then add it to
    // the global variable to print prototypicals
    if (currentClass == currentLabel) {
        //multimap<int, map<int,double>> actual_class_and_probability;
        //actual_class_and_probability.insert(make_pair(currentLabel, class_to_posterior_probability_test));
        posterior_probability_global.insert(make_pair(class_to_posterior_probability_test, currentImage));
    }
    
    return currentClass;
    
};

multimap<vector<int>, vector<vector<int>>> test_data_function(multimap <int, vector< vector<int> >> associated_label_and_image_features_test,
                                                              map<int, vector<vector<double>> > class_to_feature_probability,
                                                              map <int, double> class_to_class_probability) {
    map<int, vector <vector<vector<int>>> > organized_data;
    //initializing the map organized_data
    //key- class
    //value- vector of images that belong to a class (label)
    for (int i = 0; i < 10; i++) {
        vector <vector<vector<int>> > vectorOfImages;
        organized_data.insert(make_pair(i, vectorOfImages));
    }
    
    int currentClassLabel = 0;
    vector<vector<int>> currentClassImage;
    //adding values to the map organized_data
    for (multimap<int, vector<vector<int>>>::iterator mapIterator = associated_label_and_image_features_test.begin();
         mapIterator != associated_label_and_image_features_test.end(); mapIterator++) {
        currentClassLabel = mapIterator->first;
        currentClassImage = mapIterator->second;
        organized_data[currentClassLabel].push_back(currentClassImage);
    }
    
    //key-best estimate, actual class label
    //value- image in binary
    multimap<vector<int>, vector<vector<int>>> best_estimate_values;
    
    //go through each image in organized_data
    for (map<int, vector<vector<vector<int>>>>::iterator mapIterator = organized_data.begin();
         mapIterator != organized_data.end(); mapIterator++) {
        int currentLabel = mapIterator->first;
        vector<vector<vector<int> >> currentVectorOfImages = mapIterator->second;
        //for one class
        for (int j = 0; j < currentVectorOfImages.size(); j++) {
            vector<vector<int>> currentImage(28, vector<int>(28));
            currentImage = currentVectorOfImages[j];
            int bestEstimateValue = get_best_estimate_of_image(currentImage, class_to_feature_probability, class_to_class_probability, currentLabel);
            vector<int> classValues;
            classValues.push_back(bestEstimateValue); //first element
            classValues.push_back(currentLabel); //second element
            best_estimate_values.insert(make_pair(classValues, currentImage));
        }
    }
    return best_estimate_values;
};

