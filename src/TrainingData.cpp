//  TrainingData.cpp
//  finalproject
//This class contains functions that relates to getting and using the training data for the program.

#include "TrainingData.hpp"

using namespace std;
const int laplace_smoothing_factor = 3.0;

//total number of P(a|b) = 784 * 10
//Input :images with features, labels
//Output: all P(a|b) stored in a map

//Test all the images given in TrainingImages, that belong to a certain class we're testing
//1. Go through each feature in an image and calculate the probability of it being in one class
//2. Do this for all 10 classes
//3. Do this for all features in an image
//4. Store it in the map
map<int, vector<vector<double>> > calculate_probability_of_training_data_features(multimap <int, vector< vector<int> >> associated_label_and_image_features) {
    //initializing the map class_to_feature_probability
    //key -class
    //value - will store an image, where each element is the probability of each feature
    map<int, vector<vector<double>>> class_to_feature_probability;
    for (int i = 0; i < 10; i++) {
        vector<vector<double>> probabilityOfClass;
        class_to_feature_probability.insert(make_pair(i, probabilityOfClass));
    }
    
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
    for (multimap<int, vector<vector<int>>>::iterator mapIterator = associated_label_and_image_features.begin();
         mapIterator != associated_label_and_image_features.end(); mapIterator++) {
        currentClassLabel = mapIterator->first;
        currentClassImage = mapIterator->second;
        organized_data[currentClassLabel].push_back(currentClassImage);
    }
    
    //for one class
    for (map<int, vector<vector<vector<int>>>>::iterator mapIterator = organized_data.begin();
         mapIterator != organized_data.end(); mapIterator++) {
        vector<vector<int> > backgroundPixelCount;
        for (int i = 0; i < 28; i++) {
            vector<int> currentValue(28, 0);
            backgroundPixelCount.push_back(currentValue);
        }
        vector<vector<vector<int> >> currentVectorOfImages = mapIterator->second;
        for (int j = 0; j < currentVectorOfImages.size(); j++) {
            vector<vector<int>> currentImage = currentVectorOfImages[j];
            for (int i = 0; i < 28; i++) {
                for (int j = 0; j < 28; j++) {
                    if (currentImage[i][j] == 0) {
                        backgroundPixelCount[i][j]++;
                    }
                }
            }
        }
        
        //Access the nested vector in the map per class
        for (map<int, vector<vector<double>>>::iterator pMapIterator = class_to_feature_probability.begin();
             pMapIterator != class_to_feature_probability.end(); pMapIterator++) {
            int currentClass = pMapIterator->first;
            vector<vector<double>> classProbabilityMap = pMapIterator->second;
            for (int i = 0; i < 28; i++) {
                vector<double> currentValue(28, 0.0);
                classProbabilityMap.push_back(currentValue);
            }
            //print classProbabilityMap
            for (int i = 0; i < classProbabilityMap.size(); i++) {
                for (int j = 0; j < classProbabilityMap[i].size(); j++) {
                    cout << classProbabilityMap[i][j] << " ";
                }
                cout << "HI" << endl;
            }
            cout << classProbabilityMap.size() << endl;
            /*Go through backgroundPixelCount and calculate the probability at each feature location, then store this value
             in your map*/
            //            for (int i = 0; i < 28; i++) {
            //                for (int j = 0; j < 28; j++) {
            //                    int currentCount = backgroundPixelCount[i][j];
            //                    double featureProbability = static_cast<double> (laplace_smoothing_factor + currentCount) /
            //                            (double) (2 * laplace_smoothing_factor
            //                        + currentVectorOfImages.size());
            //                    classProbabilityMap[i][j] = featureProbability;
            //                }
            //            }
            //            class_to_feature_probability[currentClass] = classProbabilityMap;
        }
    }
    return class_to_feature_probability;
}

map <int, double> calculate_probability_of_training_data_classes(multimap <int, vector< vector<int> >> associated_label_and_image_features) {
    map <int, double> class_to_class_probability;
    int totalSameLabel;
    for (multimap<int, vector<vector<int>>>::iterator mapIterator = associated_label_and_image_features.begin();
         mapIterator != associated_label_and_image_features.end(); mapIterator++) {
        int currentLabel = mapIterator->first;
        totalSameLabel = associated_label_and_image_features.count(currentLabel);
        int trainingExamplesSize = associated_label_and_image_features.size();
        double classProbability = static_cast<double>(totalSameLabel) / (double) (trainingExamplesSize);
        class_to_class_probability.insert(make_pair(currentLabel, classProbability));
    }
    return class_to_class_probability;
}
