//
//  main.cpp
//  Topic E
//
//  Created by user on 10/24/15.
//  Copyright (c) 2015 Ben Dahl. All rights reserved.
//
// Status: working. Tested in Xcode and VS2013.
// Note: exclude from project: Heap*.cpp, ArrayMax*.cpp

#pragma warning ( disable: 4290 )

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "TopicEData.h"
#include "Heap_PriorityQueue.h"

void readInput(Heap_PriorityQueue<TopicEData>& boxQueue, vector<TopicEData>& fullBoxes);
void addWeightToBox(const double weight, Heap_PriorityQueue<TopicEData>& boxQuue, vector<TopicEData>& fullBoxes);

int main() {
    
    Heap_PriorityQueue<TopicEData> boxQueue;
    vector<TopicEData> fullBoxes;
    
    readInput(boxQueue, fullBoxes);
    
    
    cout << endl << endl << "Program Over" << endl << endl;
    // Press enter to end
    cout << "Press Enter to end --> ";
    cin.ignore();

    return 0;
}


void readInput(Heap_PriorityQueue<TopicEData>& boxQueue, vector<TopicEData>& fullBoxes)
{
    string fileName = "TopicEin.txt";
    ifstream inFile(fileName);
    double dataBuffer;
    int totalDataItems = 0;
    int totalBoxes = 0;
    
    if (!inFile)
    {
        cout << "\nInput file" << fileName << " cannot be found" << endl;
        return;
    }
    
    cout << "Valid data entered is:\n";
    
    while (inFile >> dataBuffer)
    {
        if (dataBuffer <= 1.0){
            cout << dataBuffer << " ";
            addWeightToBox(dataBuffer, boxQueue,fullBoxes);
            totalDataItems++;  // counts the number of items in file
        }
    }
    inFile.close();
    
    cout << endl << totalDataItems << " is the total number of valid data items" << endl;
    
    cout << endl << "Boxes which are considered to be full:" << endl << endl;
    
    for (auto boxes : fullBoxes)
    {
        cout << boxes;
    }
    
    cout << endl << "There are " << fullBoxes.size() << " boxes considered to be full" << endl;
    
    totalBoxes += fullBoxes.size();
    
    cout << endl << "Boxes still in the heap:" << endl;
    int count = 0;
    while (!boxQueue.isEmpty())
    {
        cout << ++count << ". " << boxQueue.peek();
        boxQueue.remove();
        totalBoxes++;
    }
    
    cout << "There are " << count << " in the heap" << endl;
    cout << endl << totalBoxes << " is the total number of boxes" << endl;
    cout << totalDataItems << " is the total number of items" << endl;
    
}

void addWeightToBox(const double weight, Heap_PriorityQueue<TopicEData>& boxQueue, vector<TopicEData>& fullBoxes)
{
    // 1) Node represents a box that can add the weight to its load
    // 2) Node cannot add weight because that would put it over its MAX_CAPACITY
    // 3) All boxes are too full to add weight
    
    // 3) first case, is the PQ empty?
    if (boxQueue.isEmpty())
    {
        TopicEData box;
        boxQueue.add(box);
    }
    
    // lets get the top node
    TopicEData node = boxQueue.peek();
    boxQueue.remove();
    

    // 1) Node accepts weight
    if (node.insert(weight))
    {
        if(node.isFull())
            fullBoxes.push_back(node);
        else
            boxQueue.add(node);
        return;
    }
    // 2) Node cant accept weight, get next node.
    else
    {
        addWeightToBox(weight,boxQueue,fullBoxes);
        // put the not full node back on queue
        boxQueue.add(node);
    }

}