//  TestingData.hpp
//  finalproject

#ifndef TestingData_hpp
#define TestingData_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <math.h>

using namespace std;

extern multimap<map<int,double>, vector<vector<int>>> posterior_probability_global;

int get_best_estimate_of_image(vector<vector<int>> currentImage, map<int, vector<vector<double>> > class_to_feature_probability,map <int, double> class_to_class_probability, int currentLabel);

multimap<vector<int>, vector<vector<int>>> test_data_function(multimap <int, vector< vector<int> >> associated_label_and_image_features_test, map<int, vector<vector<double>> > class_to_feature_probability,
                                                              map <int, double> class_to_class_probability);
#endif /* TestingData_hpp */
