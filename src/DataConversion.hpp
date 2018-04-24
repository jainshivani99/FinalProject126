//  DataConversion.hpp
//  finalproject

#ifndef DataConversion_hpp
#define DataConversion_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

multimap <int, vector< vector<char> >> get_labels_and_images(string fileLabels, string fileImages);
multimap <int, vector< vector<int> >> convert_pixels_to_features(multimap <int, vector< vector<char> >> associated_label_and_image);

#endif /* DataConversion_hpp */
