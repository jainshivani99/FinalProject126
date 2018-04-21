//  DataEvaluation.hpp
//  finalproject

#ifndef DataEvaluation_hpp
#define DataEvaluation_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

vector<vector<double>> create_confusion_matrix(multimap <vector<int>, vector< vector<int>>> best_estimate_values);

void print_confusion_matrix(vector<vector<double>> percentage_confusion_matrix);

multimap<int, vector<vector<int>>> calculate_prototypicals_per_class(multimap<map<int,double>, vector<vector<int>>> posterior_probability_global);

void print_prototypicals_per_class(multimap<int, vector<vector<int>>> posterior_probability_images);

#endif /* DataEvaluation_hpp */
