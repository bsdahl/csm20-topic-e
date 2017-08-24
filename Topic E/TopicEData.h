//
//  TopicEData.h
//  Topic E
//
//  Created by user on 10/24/15.
//  Copyright (c) 2015 Ben Dahl. All rights reserved.
//


#ifndef __Topic_E__TopicEData__
#define __Topic_E__TopicEData__

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

class TopicEData
{
    friend ostream &operator << (ostream & out, const TopicEData & val);
public:
    TopicEData() : totLoad(0), seqNum(boxNum), loads(0) { ++boxNum; }
    TopicEData(const double& load);
    
    double getTotalLoad() const { return totLoad; }
    bool isFull() const { return (totLoad >= 0.99); }
    bool insert(const double& load);
    //void clear();
    
    TopicEData operator= (const TopicEData& right);
    double operator+=(const double& right);
    double operator+ (const double& right) { return (totLoad + right); }
    bool operator!=(const TopicEData& right) const	{ return (totLoad != right.totLoad); }
    bool operator==(const TopicEData& right) const	{ return (totLoad == right.totLoad); }
    bool operator>=(const TopicEData& right) const	{ return (totLoad >= right.totLoad); }
    bool operator<=(const TopicEData& right) const	{ return (totLoad <= right.totLoad); }
    bool operator> (const TopicEData& right) const	{ return (totLoad >  right.totLoad); }
    bool operator< (const TopicEData& right) const	{ return (totLoad <  right.totLoad); }
    
private:
    double totLoad;
    int seqNum;
    vector<double> loads;
    static int boxNum;
};



#endif /* defined(__Topic_E__TopicEData__) */
