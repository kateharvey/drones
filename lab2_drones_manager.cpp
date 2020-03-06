#include "lab2_drones_manager.hpp"
#include <iostream>

// Lab Assignment 2:
//    Group #28
//    Kate Harvey, ID# 20829173
//    Jessica Lui, ID# 20837325

// constructor
DronesManager::DronesManager() {
	first = last = NULL;
	size = 0;
}

// destructor
DronesManager::~DronesManager() {
    
    DroneRecord* curr = first;

	while(curr != NULL) {
        curr = curr -> next;
		delete first;
		first = curr;
    }
    
	first = last = NULL;
	size = 0;
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	bool are_equal = true;
	are_equal = lhs.droneID == rhs.droneID && lhs.droneType == rhs.droneType
		&& lhs.manufacturer == rhs.manufacturer && lhs.description == rhs.description
		&& lhs.range == rhs.range && lhs.batteryType == rhs.batteryType && lhs.yearBought == rhs.yearBought;
	return are_equal;
}

unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
	if(size == 0) return true;
	else return false;
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	DroneRecord* curr = first;
	
	// if list empty, return DroneRecord(0)
	if(size == 0) return DroneRecord(0);
	
	// if index invalid, return the last element
	if(size < index) {
		while(curr -> next != NULL) {
			curr = curr -> next;
		}
		return *curr;
	}
	
	// else return value at given index
	int i = 0;
	while(i < index) {
		curr = curr -> next;
		i ++;
	}
	return *curr;
}

unsigned int DronesManager::search(DroneRecord value) const {
    
    // not working
    
    if(size == 0) return 0;
    
    DroneRecord* target = new DroneRecord(value);
    DroneRecord* curr = first;
    unsigned int index = 0;
    
    while(curr -> next != NULL) {
        if(curr == target) return index; // target found
        else {
            curr = curr -> next;
            index ++;
        }
    }
    
    // if target not found
    return size;
}

void DronesManager::print() const {
    DroneRecord* curr = first;
    int index = 0;
    
    if(size == 0) cout << "There are no drones in the list." << endl;
    while(index < size) {
        cout << "DRONE " << index + 1 << endl;
        cout << "Drone ID: " << curr -> droneID << endl;
        cout << "Range: " << curr -> range << endl;
        cout << "Year Bought: " << curr -> yearBought << endl;
        cout << "Drone Type: " << curr -> droneType << endl;
        cout << "Manufacturer: " << curr -> manufacturer << endl;
        cout << "Description: " << curr -> description << endl;
        cout << "Battery Type: " << curr -> batteryType << endl;
        cout << endl;
        curr = curr -> next;
        index ++;
    }
	return;
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
    if(index > size) return false; // out of range
    if(size == 0) insert_back(value);
    else if(index == 0) insert_front(value);
    else if (index == size) insert_back(value);
    
    else {
        DroneRecord* temp = new DroneRecord(value);
        DroneRecord* curr = first;
        
        // pass over list to target drone:
        int i = 0;
        while(i < index) {
            curr = curr -> next;
            i ++;
        }
        
        if(i == 0) {
            insert_front(value);
        }
        
        temp -> prev = curr -> prev;
        (curr -> prev) -> next = temp;
        temp -> next = curr;
        curr -> prev = temp;
        size ++;
        return true;
    }
    return true;
}

bool DronesManager::insert_front(DroneRecord value) {
	DroneRecord* temp = new DroneRecord(value);

	if(size == 0) {
		first = last = temp;
		size = 1;
		return true;
	}
    
    else {
        first -> prev = temp;
        temp -> next = first;
        first = temp;
        size ++;
        return true;
    }
}

bool DronesManager::insert_back(DroneRecord value) {
	DroneRecord* temp = new DroneRecord(value);

	if(size == 0) {
		first = last = temp;
		size = 1;
		return true;
	}
    
    else {
        last -> next = temp;
        temp -> prev = last;
        last = temp;
        size ++;
        return true;
    }
}

bool DronesManager::remove(unsigned int index) {
	if(size == 0) return false; // empty list
    if(index > size) return false; // out of range
	if(index == 0 || size == 1) remove_front();
	if(index == size - 1) remove_back();
	
	DroneRecord* curr = first;
	DroneRecord* prev = NULL;
	int i = 0;
    
    // pass over list to target drone:
	while(i < index) {
		prev = curr;
		curr = curr -> next;
        i ++;
	}
    
    if(prev != NULL) {
        prev -> next = curr -> next;
        (curr -> next) -> prev = prev;
        curr -> next = NULL;
        size --;
        return true;
    }
    else return false;
}

bool DronesManager::remove_front() {
	if(size == 0) return false;
	if(size == 1) {
        size = 0;
		first = last = NULL;
		return true;
	}
    
	else {
		first = first -> next;
		size --;
		return true;
	}
}

bool DronesManager::remove_back() {
    if(size == 0) return false;
    if(size == 1) {
        size = 0;
        first = last = NULL;
        return true;
    }
    
    DroneRecord* curr = first;

    while(curr -> next -> next != NULL) {
        curr = curr -> next;
    }
    
    curr -> next = NULL;
    last = curr;
    size --;
    return true;
}

// replace drone at [index] with the specified value
bool DronesManager::replace(unsigned int index, DroneRecord value) {
	if(size == 0) return false; // empty list
	else if(size <= index) return false; // out of range

    DroneRecord* newDrone = new DroneRecord(value);
    DroneRecord* curr = first;
    DroneRecord* prev = NULL;
    int i = 0;
    
	// pass over list to index
	while(i < index) {
		prev = curr;
		curr = curr -> next;
		i ++;
	}
    
    // if replacing first drone:
    if(i == 0) {
        newDrone -> next = first -> next;
        (first -> next) -> prev = newDrone;
        first -> next = NULL;
        first = newDrone;
        return true;
    }
    
    // if not replacing first drone:
    else {
        prev -> next = newDrone;
        newDrone -> next = curr -> next;
        // (curr -> next) -> prev = newDrone;
        curr -> next = NULL;
        return true;
    }
}

bool DronesManager::reverse_list() {
    
    // not working
    
    
	if(size == 0 || size == 1) return true;
    
    DroneRecord* curr = first;
    DroneRecord* temp = NULL;

	while(curr != nullptr) {
        temp = curr -> prev;
        curr -> prev = curr->next;
        curr -> next = temp;
        curr = curr -> prev;
	}
    
    if(temp != NULL) first = temp -> prev;

	return true;
}
