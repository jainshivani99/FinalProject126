#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/DataConversion.hpp"
#include <iostream>
#include <map>

using namespace std;

TEST_CASE("Test Get Images and Labels") {
    multimap <int, vector< vector<char> >> associated_label_and_image;
    string fileLabels = "/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/Images/traininglabels";
    string fileImages = "/Users/shivanijain/OF_ROOT/apps/myApps/finalproject/bin/data/Images/trainingimages";
    ifstream inFile2;
    inFile2.open(fileImages);
    char imageChar;
    vector<vector<char>> fullImage;
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 29; j++) {
            inFile2.get(imageChar);
            if (imageChar == '\n') {
                continue;
            }
            fullImage[i][j] = imageChar;
        }
    }
    associated_label_and_image.insert(make_pair(5, fullImage));
    associated_label_and_image.insert(make_pair(0, fullImage));
    REQUIRE(get_labels_and_images(fileLabels, fileImages) == associated_label_and_image);
}

TEST_CASE("Convert Pixels to Features") {
    multimap <int, vector< vector<char> >> associated_label_and_image;
    multimap <int, vector< vector<int> >> associated_label_and_image_features;
    vector<vector<int> > imageWithFeatures(28, vector<int>(28));

    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            char currentChar;
            if (currentChar == ' ') {
                int currentCharValue = 0;
                imageWithFeatures[i][j] = currentCharValue;
            } else if (currentChar == '+') {
                int currentCharValue = 1;
                imageWithFeatures[i][j] = currentCharValue;
            } else if (currentChar == '#') {
                int currentCharValue = 1;
                imageWithFeatures[i][j] = currentCharValue;
            }
        }
    }
    associated_label_and_image_features.insert(make_pair(5, imageWithFeatures));
    associated_label_and_image_features.insert(make_pair(0, imageWithFeatures));
    REQUIRE(convert_pixels_to_features(associated_label_and_image) == associated_label_and_image_features);
}
