//  DataEvaluation.cpp
//  finalproject

#include "DataEvaluation.hpp"

using namespace std;

//print out confusion matrix
void print_confusion_matrix(vector<vector<double>> percentage_confusion_matrix) {
    cout << "Confusion Matrix: " << endl;
    for (int i = 0; i < percentage_confusion_matrix.size(); i++)
    {
        for (int j = 0; j < percentage_confusion_matrix[i].size(); j++)
        {
            cout << percentage_confusion_matrix[i][j] << ", ";
        }
        cout << endl;
    }
    cout << "\n";
}


vector<vector<double>> create_confusion_matrix(multimap <vector<int>, vector< vector<int>>> best_estimate_values) {
    //confusion matrx - create a 10 by 10 nested vector
    //each element contains a percentage value (predicted / actual)
    vector<vector<int>> count_confusion_matrix;
    for (int i = 0; i < 10; i++) {
        vector<int> currentValue(10, 0);
        count_confusion_matrix.push_back(currentValue);
    }
    for (multimap <vector<int>, vector< vector<int>>>::iterator mapIterator = best_estimate_values.begin();
         mapIterator != best_estimate_values.end(); mapIterator++) {
        vector<int> classValues = mapIterator->first;
        int predictedValue = classValues.at(0);
        int actualValue = classValues.at(1);
        count_confusion_matrix[predictedValue][actualValue]++;
    }
    
    vector<vector<double> > percentage_confusion_matrix(10, vector<double>(10));
    
    //get the value from count confusion matrix
    //divide by total number of images for each element in that column
    //store that in percentage confusion matrix
    
    vector<int> totalImagesOfClass(10, 0);
    //adds values to the above vector
    for (int c = 0; c < 10; c++) {
        int totalNumber = 0;
        for (int r = 0; r < 10; r++) {
            totalNumber += count_confusion_matrix[r][c];
        }
        totalImagesOfClass[c] = totalNumber;
    }
    
    for (int c = 0; c < 10; c++) {
        for (int r = 0; r < 10; r++) {
            int currentCount = count_confusion_matrix[r][c];
            double probability = static_cast<double> (currentCount) / (double) (totalImagesOfClass[c]);
            double rounded = (int)(probability * 1000.0)/1000.0;
            percentage_confusion_matrix[r][c] = rounded;
        }
    }
    return percentage_confusion_matrix;
}

void print_prototypicals_per_class(multimap<int, vector<vector<int>>> posterior_probability_images) {
    cout << "Prototypicals: " << endl;
    for (multimap<int, vector<vector<int>>>::const_iterator it = posterior_probability_images.begin(); it != posterior_probability_images.end(); ++it) {
        cout << it->first << endl;
        vector<vector<int> > currentImage = it->second;
        for (int i = 0; i < currentImage.size(); i++)
        {
            for (int j = 0; j < currentImage[i].size(); j++)
            {
                cout << currentImage[i][j];
            }
            cout << endl;
        }
        
    }
}

multimap<int, vector<vector<int>>> calculate_prototypicals_per_class(multimap<map<int,double>, vector<vector<int>>> posterior_probability_global) {
    multimap<int, vector<vector<int>>> posterior_probability_images;
    
    //i = current class you are calculating
    for (int i = 0; i < 10; i++) {
        //double currentMax = -5000.0;
        //double currentMin = 100.0;
        double currentMax;
        double currentMin;
        vector<vector<int>> currentMaxImage(28, vector<int>(28));
        vector<vector<int>> currentMinImage(28, vector<int>(28));
        
        //only look at the images where the best estimate and label match up
        for (multimap<map<int,double>, vector<vector<int>>>::iterator mapIterator = posterior_probability_global.begin();
             mapIterator != posterior_probability_global.end(); mapIterator++) {
            map<int, double> classAndProbabilityMap = mapIterator->first;
            vector<vector<int>> currentImage = mapIterator->second;
            currentMax = classAndProbabilityMap[i];
            currentMin = classAndProbabilityMap[i];
            currentMaxImage = currentImage;
            currentMinImage = currentImage;
            break;
        }
        
        //Calculating the max within a class
        for (multimap<map<int,double>, vector<vector<int>>>::iterator mapIterator = posterior_probability_global.begin();
             mapIterator != posterior_probability_global.end(); mapIterator++) {
            map<int, double> classAndProbabilityMap = mapIterator->first;
            vector<vector<int>> currentImage = mapIterator->second;
            double currentValue = classAndProbabilityMap[i];
            if (currentValue > currentMax) {
                currentMax = currentValue;
                currentMaxImage = currentImage;
            }
        }
        //Calculating a min within a class
        for (multimap<map<int,double>, vector<vector<int>>>::iterator mapIterator = posterior_probability_global.begin();
             mapIterator != posterior_probability_global.end(); mapIterator++) {
            map<int, double> classAndProbabilityMap = mapIterator->first;
            vector<vector<int>> currentImage = mapIterator->second;
            double currentValue = classAndProbabilityMap[i];
            if (currentValue < currentMin) {
                currentMin = currentValue;
                currentMinImage = currentImage;
            }
        }
        posterior_probability_images.insert(make_pair(i, currentMaxImage));
        posterior_probability_images.insert(make_pair(i, currentMinImage));
    }
    return posterior_probability_images;
}
