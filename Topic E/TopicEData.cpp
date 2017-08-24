//
//  TopicEData.cpp
//  Topic E
//
//  Created by user on 10/24/15.
//  Copyright (c) 2015 Ben Dahl. All rights reserved.
//

#include "TopicEData.h"
using namespace std;

int TopicEData::boxNum = 1;

TopicEData::TopicEData(const double& load)
{
    seqNum = ++boxNum;
    loads.push_back(load);
    totLoad = load;
}

bool TopicEData::insert(const double& load)
{
    if (totLoad+load <= 1.0) {
        loads.push_back(load);
        totLoad += load;
    }
    else
        return false;
    return true;
}

TopicEData TopicEData::operator=(const TopicEData& right)
{
    loads.clear();
    totLoad = 0;
    
    totLoad += right.totLoad;
    seqNum = ++boxNum;
    
    for (unsigned int i = 0; i < right.loads.size(); i++)
        this->loads.push_back(right.loads[i]);
    
    return *this;
}

ostream &operator << (ostream & out, const TopicEData & val)
{
    out << "For box " << val.seqNum
    << ", Total Items:\t" << val.loads.size()
    << ", Total Load:\t" << val.getTotalLoad() << ", \t"
    << "consisting of ";
    for (int i = 0;i < val.loads.size(); i++)
        out << val.loads[i] << " ";
    out << endl;
    
    return out;
}