// Class mentods/variables/functions that uses a binary heap
// to implement a patient queue


#pragma once

#include <iostream>
#include <string>
#include "patientnode.h"
#include "patientqueue.h"
using namespace std;

class HeapPatientQueue : public PatientQueue  {
public:
    HeapPatientQueue();
    ~HeapPatientQueue();
    string frontName();
    void clear();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int newPriority);
    string toString();

private:
    int size;  // size of array
    int capacity; // capacity, which is set initially
    PatientNode* array; // pointer to internal array of elements using given struct
    void expandArray();  // expands internal array if size exceeds capacity
    void bubbleUp(int i); // method for binary heap
    void bubbleDown(int i); // method for binary heap
};
