// Class mentods/variables/functions that uses an un-sorted Vector
// to implement a patient queue

#pragma once

#include <iostream>
#include <string>
#include "patientqueue.h"
#include "vector.h"
#include "map.h"
using namespace std;



class VectorPatientQueue : public PatientQueue {
public:
    VectorPatientQueue();
    ~VectorPatientQueue();
    string frontName();
    void clear();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int newPriority);
    string toString();


private:
    // each patient record contains a name, an assigned priority and the timing of placement
    struct patient {
        string name;
        int priority;
        int time;
    };
    Vector<patient> pq; //un-sorted vector that stores elements of patient queue
    int count; // represents the time stamp

};
