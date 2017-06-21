// LinkedListPatientQueue.cpp implements the patient queue class using various mentods

#include "LinkedListPatientQueue.h"

// Initializes new empty queue
LinkedListPatientQueue::LinkedListPatientQueue() {
    start = NULL;
}
// Frees up any memory (linked list) nodes used
LinkedListPatientQueue::~LinkedListPatientQueue() {
    while(start != NULL) {
        PatientNode* next = start->next;
        delete start;
        start = next;
    }
}

// Clears out patient queue
void LinkedListPatientQueue::clear() {
    while(start) {
        deleteRecords();
    }
}

// Returns name of most urgent priority patient
string LinkedListPatientQueue::frontName() {
    if(start == NULL) throw string("No patients");
    string head = start->name; //directs pointer to name of first node
    return head;
}

// Returns priority of most urgent patient
int LinkedListPatientQueue::frontPriority() {
    if(start == NULL) throw string("No patients");
    int pr = start->priority;
    return pr;
}

// Returns whether queue is empty or not
bool LinkedListPatientQueue::isEmpty() {
    return (start == NULL);
}

// Adds a new patient to the list such that it remains sorted
void LinkedListPatientQueue::newPatient(string name, int priority) {
    if(start == NULL) {
        start = new PatientNode(name,priority);
    } else {
       addPatient(name,priority); // helper function
    }
}

// Removes most urgent priority patient, which in this case
// is the patient record at the start/front of the list
string LinkedListPatientQueue::processPatient() {
    if(start == NULL) throw string("No patients");
    PatientNode* next = start->next;   // points to node after front
    delete start;  // removes most urgent
    start = next;   // sets start to next node
    return frontName(); // returns most urgent
}

// Modifies the priority of given existing patient in queue
void LinkedListPatientQueue::upgradePatient(string name, int newPriority) {
    if(start == NULL) throw string("No patients");
    upgradeRecords(name,newPriority);  // Helper function
}

// Returns string of patient queue to be printed out to console
string LinkedListPatientQueue::toString() {
    PatientNode* currPatient = start;
    string needed;
    while(currPatient) {
        needed += to_string(currPatient->priority) + ":" + currPatient->name + ", ";
        currPatient = currPatient->next; // sets the current patient to memory address of next node
    }
    return "{" + needed.substr(0,needed.size()-2) + "}";
}

// Deletes given patient record
void LinkedListPatientQueue::deleteRecords() {
    PatientNode* next = start->next;
    delete start;
    start = next;
}

// Helper function to add new patient to queue
void LinkedListPatientQueue::addPatient(string name, int priority) {
    PatientNode* value = new PatientNode(name,priority); //uses given struct to initialize new node
    PatientNode* current = start; // sets the current pointer to front node at neginning
    while(current->next && current->next->priority <= priority) { // condition for current and next node before adding
        current = current->next;
        if(current->priority == priority && name < current->name) { // if patient being added
            string record = current->name;
            current->name = name;
            name = record;
        }
    }
    if(priority < current->priority) {
        value->next = current;
        start = value;
    } else {
        value->next = current->next;
        current->next = value;
    }
}

// Helper function to modify priority of given patient
void LinkedListPatientQueue::upgradeRecords(string name, int newPriority) {
    PatientNode* current = start;
    PatientNode* previous = start;
    while(current != NULL) {  // moves from one node to another while the list is not empty
        if(current->name == name) {  // finds corresponding name
            if(current->priority > newPriority) {  // checks if new priority is more urgent
                if (current == start) { // if current is still the front node
                    start = current->next;
                } else {
                    previous->next = current->next;
                }
                delete current;  // frees up memory associated with current
                newPatient(name,newPriority); // modifies as if it were adding new patient with changed priority
                return;
            }
            throw string("Already more urgent!");
        }
        previous = current; // sets the previous pointer to the node it currently points at
        current = current->next;
    }
    throw string("No such patient");
}

