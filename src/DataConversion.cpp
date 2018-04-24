//  DataConversion.cpp
//  finalproject

#include "DataConversion.hpp"

using namespace std;

/*This function gets all the images and labels for training data, and groups them in a multimap together where they are sorted by their key
key- class they belong to
value- the image itself
 */
multimap <int, vector< vector<char> >> get_labels_and_images(string fileLabels, string fileImages) {
    //multimap that stores the label and associated image
    multimap <int, vector< vector<char> >> associated_label_and_image;
    
    ifstream inFile;
    inFile.open(fileLabels);
    string imageLabel;
    
    ifstream inFile2;
    inFile2.open(fileImages);
    char imageChar;
    vector< vector<char> > fullImage(28, vector<char> (28));
    while (getline(inFile, imageLabel)) {
        stringstream stringObj(imageLabel);
        int myImageLabel;
        stringObj >> myImageLabel;
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 29; j++) {
                inFile2.get(imageChar);
                if (imageChar == '\n') {
                    continue;
                }
                fullImage[i][j] = imageChar;
            }
        }
        associated_label_and_image.insert(pair<int, vector< vector<char> >>(myImageLabel, fullImage));
    }
    
    return associated_label_and_image;
}

//Function that takes a multimap of images as input and converts its pixels into features
//Returns a multimap of images with features and its associated label
multimap <int, vector< vector<int> >> convert_pixels_to_features(multimap <int, vector< vector<char> >> associated_label_and_image) {
    
    multimap <int, vector< vector<int> >> associated_label_and_image_features;
    //get each value in the multimap, which is an image with pixels
    for (multimap<int, vector< vector<char>> >::iterator mapIterator = associated_label_and_image.begin();
         mapIterator != associated_label_and_image.end(); mapIterator++) {
        
        vector<vector<char> > currentImage = mapIterator->second;
        int currentLabel = mapIterator->first;
        vector<vector<int> > imageWithFeatures(28, vector<int>(28));
        
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 28; j++) {
                char currentChar = currentImage[i][j];
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
        associated_label_and_image_features.insert(make_pair(currentLabel, imageWithFeatures));
    }
    return associated_label_and_image_features;
}
