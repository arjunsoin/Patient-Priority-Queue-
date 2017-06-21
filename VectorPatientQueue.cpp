// VectorPatientQueue.cpp implements the patient queue class using various mentods

#include "VectorPatientQueue.h"
#include "map.h"


// Initializes new empty queue
VectorPatientQueue::VectorPatientQueue() {
    pq;
}

VectorPatientQueue::~VectorPatientQueue() {

}

// Clears out patient queue
void VectorPatientQueue::clear() {
    pq.clear();
}

// Returns name of most urgent priority patient
string VectorPatientQueue::frontName() {
    if(pq.isEmpty()) throw string("No patients");
    patient result = pq[0];
    for(int i = 0; i < pq.size(); i++) {   // loop through entire vector to find most urgen priority
        if(pq[i].priority < result.priority) {
            result = pq[i];
        }
    }
    return result.name;
}

// Returns priority of most urgent patient
int VectorPatientQueue::frontPriority() {
    if(pq.isEmpty()) throw string("No patients");
    patient result = pq[0];
    for(int i = 0; i < pq.size(); i++) {
        if(pq[i].priority < result.priority) {
            result = pq[i];
        }
        if(pq[i].priority == result.priority && pq[i].time < result.time) {
            result = pq[i];
        }
    }
    return result.priority;
}

// Checks if queue is empty
bool VectorPatientQueue::isEmpty() {
    return pq.size() == 0;
}

// Adds a new patient, as well as increments timestamp variable
void VectorPatientQueue::newPatient(string name, int priority) {
    patient newOne;
    newOne.name = name;
    newOne.priority = priority;
    count++;
    newOne.time = count;
    pq.add(newOne);
}

// Removes patient with most urgent priority from queue
string VectorPatientQueue::processPatient() {
    if(pq.isEmpty()) throw string("No patients");
    int index = 0;
    patient urgent = pq[0];
    count = pq[0].time;
    for(int i = 0; i < pq.size(); i++) {
        if(pq[i].priority < urgent.priority) {
            urgent = pq[i];
            index = i;
        }
        if(pq[i].priority == urgent.priority && pq[i].time < urgent.time) {
            urgent = pq[i];
            index = i;
        }
    }
    pq.remove(index);
    return urgent.name;
}

// Modifies the priority of given existing patient in queue
void VectorPatientQueue::upgradePatient(string name, int newPriority) {
    for(int i = 0; i < pq.size(); i++) {
        if(pq[i].name == name) {
            if(pq[i].priority < newPriority) throw string("Already lower priority");
            pq[i].priority = newPriority;
            return;
        }
    }
    throw string("No such patient");
}

// Returns string of patient queue to be printed out to console
string VectorPatientQueue::toString() {
    string needed;
    for(patient p : pq) {
        needed += to_string(p.priority) + ":" + p.name + ", ";
    }
    return "{" + needed.substr(0,needed.size()-2) + "}";  // substring removes comma if queue over
}
