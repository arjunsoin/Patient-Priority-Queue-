// Class mentods/variables/functions that uses a sorted linked list
// to implement a patient queue

#pragma once

#include <iostream>
#include <string>
#include "patientnode.h"
#include "patientqueue.h"
using namespace std;

class LinkedListPatientQueue : public PatientQueue {
public:
    LinkedListPatientQueue();
    ~LinkedListPatientQueue();
    string frontName();
    void clear();
    int frontPriority();
    bool isEmpty();
    void newPatient(string name, int priority);
    string processPatient();
    void upgradePatient(string name, int newPriority);
    string toString();

private:
   PatientNode* start;  // pointer to the start of the list
   void deleteRecords();
   void checkRecord(PatientNode* &previous, PatientNode* &current, string name, int newPriority);
   void addPatient(string name, int priority);
   void upgradeRecords(string name, int newPriority);

};
