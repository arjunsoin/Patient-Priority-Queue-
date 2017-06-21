// HeapPatientQueue.cpp implements the patient queue class using various mentods

#include "HeapPatientQueue.h"
int INIT_CAPACITY = 10;  // initial capacity of the internal array

// Initializes new empty queue
HeapPatientQueue::HeapPatientQueue() {
    size = 1;
    capacity = INIT_CAPACITY;
    array = new PatientNode[capacity];
}

// frees up memory associated with the internal array that is pointed to
HeapPatientQueue::~HeapPatientQueue() {
    delete [] array;
}

// clears the queue of patients
void HeapPatientQueue::clear() {
    size = 1;
}

// Returns name of most urgent priority patient
string HeapPatientQueue::frontName() {
    if(size == 1) throw string("No patients");
    return array[1].name;
}

// Returns priority of most urgent patient
int HeapPatientQueue::frontPriority() {
    if(size == 1) throw string("No patients");
    return array[1].priority;
}

// Returns whether or not the patient queue is empty
bool HeapPatientQueue::isEmpty() {
    return size == 1;
}

// Adds new patient to the queue
void HeapPatientQueue::newPatient(string name, int priority) {
    if(size > capacity) expandArray(); // uses helper method to expand internally if size exceeds capacity
    array[size] = PatientNode(name,priority); // adds patien node with given priority and name into first empty index
    if(size > 0) bubbleUp(size); // percolates up using helper function
    size++;
}

// Removes most urgent priority patient from queue
string HeapPatientQueue::processPatient() {
    if(size == 1) throw string("No patients");
    string processed = array[1].name;
    array[1] = array[size-1];  // replaces element at first index with that at last before bubbling down
    if(size == 2 || size == 3) {  // special case if queue has just one or two patient records
        size--;
        return processed;
    } else {
        bubbleDown(1); // percolates down using helper function
        size--;
        return processed;
    }
}

// Modifies priority of given patient in the queue
void HeapPatientQueue::upgradePatient(string name, int newPriority) {
    if(size == 1) throw string("No patients");
    for (int i = 1; i <= size; i++) {  // loops over internal array to find corresponding name
        if(array[i].name == name) {
            if(newPriority < array[i].priority) {
                array[i].priority = newPriority;
                bubbleUp(size-1); // bubbles up from present location like enqueue operation
                return;
            } else {
                throw string("Already lower priority");
            }
        }
    }
    throw string("No such patient");
}

// Returns string of patient queue to be printed out to console
string HeapPatientQueue::toString() {
    string needed;
    for(int i = 1; i < size; i++) {
        needed += to_string(array[i].priority) + ":" + array[i].name + ", ";
    }
    return "{" + needed.substr(0,needed.size()-2) + "}";
}

// Helper function that internally expands array, as shown in lecture
void HeapPatientQueue::expandArray() {
    PatientNode* bigArray = new PatientNode[capacity * 2]; // new pointer to internal array with double capacity
    for(int i = 0; i <= size; i++) {
        bigArray[i] = array[i];
    }
    delete [] array;  // frees up used memory
    array = bigArray;
    capacity *=2;
}

// Function to percolate up
void HeapPatientQueue::bubbleUp(int i) {
    int parentIndex = i/2;
    while(i > 0 && array[i].priority < array[parentIndex].priority) { // so long as it has a more urgent priority than its parent
        std::swap(array[i],array[parentIndex]); // swaps with parent
        i = parentIndex;
        parentIndex = parentIndex/2;
        i = i/2;
    }
}

// Function to percolate down useful for removing(dequeue)
void HeapPatientQueue::bubbleDown(int i) {
    // sets indices of both children
    int child1 = i*2;
    int child2 = i*2+1;
    if(array[i].priority < array[child1].priority && array[i].priority < array[child2].priority) {
        frontName();
    }
    // operation goes on so long as it has a less urgent (higher) priority than its child
    while(i > 0 && array[i].priority > array[child1].priority || array[i].priority > array[child2].priority) {
        if(array[child1].priority < array[child2].priority) {
            std::swap(array[i],array[child1]);
            i = child1;
            return;
        } else if(array[child1].priority > array[child2].priority) {
            std::swap(array[i],array[child2]);
            i = child2;
            return;
        } else if(array[child1].priority == array[child2].priority) { // condition if priority is the same
            if(array[child1].name < array[child2].name) { // checks which name comes first using standard operator
                std::swap(array[i],array[child1]);
                i = child1;
                return;
            } else {
                std::swap(array[i],array[child2]);
                i = child2;
                return;
            }
        }
    }
}
