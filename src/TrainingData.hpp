//  TrainingData.hpp
//  finalproject

#ifndef TrainingData_hpp
#define TrainingData_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

map<int, vector<vector<double>> > calculate_probability_of_training_data_features(multimap <int, vector< vector<int> >> associated_label_and_image_features);
map <int, double> calculate_probability_of_training_data_classes(multimap <int, vector< vector<int> >> associated_label_and_image_features);

#endif /* TrainingData_hpp */
