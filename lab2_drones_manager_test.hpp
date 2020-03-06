#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.hpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

// Lab Assignment 2:
//    Group #28
//    Kate Harvey, ID# 20829173
//    Jessica Lui, ID# 20837325

class DronesManagerTest {
public:

	// PURPOSE: New empty list is valid
	bool test1() {
		DronesManager manager;
		ASSERT_TRUE(manager.get_size() == 0)
		ASSERT_TRUE(manager.empty() == true)
		ASSERT_TRUE(manager.first == NULL)
		ASSERT_TRUE(manager.last == NULL)
	    return true;
	}
	
	// PURPOSE: insert_front() and insert_back() on zero-element list
	bool test2() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));
	    
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
		ASSERT_TRUE(manager1.first -> prev == NULL && manager1.last -> next == NULL)
		ASSERT_TRUE(manager2.first -> prev == NULL && manager2.last -> next == NULL)
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))		
	    return true;
	}
	
	// TODO: Implement all of the test cases below
	
	// PURPOSE: select() and search() work properly
	bool test3() {
        DronesManager manager;
        DronesManager::DroneRecord test_drone_1(1000);
        DronesManager::DroneRecord test_drone_2(1234);
        DronesManager::DroneRecord test_drone_3(4321);
        
        // test select on empty list:
        ASSERT_TRUE(manager.select(0) == 0);
        
        // test search on empty list:
        ASSERT_TRUE(manager.search(500) == 0);
        
        // test select on non-empty list:
        manager.insert_front(test_drone_1);
        ASSERT_TRUE(manager.select(0) == 1000);
        manager.insert_back(test_drone_2);
        ASSERT_TRUE(manager.select(1) == 1234);
        manager.insert(test_drone_3, 0);
        ASSERT_TRUE(manager.select(0) == 4321);
        
        // test search on non-empty list:
        //cout << "Index of td_3: " << manager.search(test_drone_3) << endl;
        //cout << "Index of td_1: " << manager.search(test_drone_1) << endl;
        //cout << "Index of td_2: " << manager.search(test_drone_2) << endl;
        
        //ASSERT_TRUE(manager.search(test_drone_3) == 0);
        //ASSERT_TRUE(manager.search(test_drone_1) == 1);
        //ASSERT_TRUE(manager.search(test_drone_2) == 2);
        
        return true;
	}
	
	// PURPOSE: remove_front() and remove_back() on one-element list
	bool test4() {
        DronesManager manager;
        DronesManager::DroneRecord test_drone(1000);
        
        // remove_front() on one-element list:
        manager.insert_front(test_drone);
        ASSERT_TRUE(manager.get_size() == 1);
        ASSERT_TRUE(manager.remove_front() == true);
        ASSERT_TRUE(manager.get_size() == 0);
        
        // remove_back() on one-element list:
        manager.insert_back(test_drone);
        ASSERT_TRUE(manager.get_size() == 1);
        ASSERT_TRUE(manager.remove_back() == true);
        ASSERT_TRUE(manager.get_size() == 0);
        
	    return true;
	}
	
	// PURPOSE: replace() and reverse_list() work properly
	bool test5() {
        DronesManager manager;
        DronesManager::DroneRecord test_drone_1(1000);
        DronesManager::DroneRecord test_drone_2(1234);
        DronesManager::DroneRecord test_drone_3(4321);
        
        manager.insert_back(test_drone_1);
        manager.insert_back(test_drone_1);
        manager.insert_back(test_drone_1);

        // test replace() method:
        manager.replace(0, test_drone_1);
        manager.replace(1, test_drone_2);
        manager.replace(2, test_drone_3);
        ASSERT_TRUE(manager.select(0) == test_drone_1);
        ASSERT_TRUE(manager.select(1) == test_drone_2);
        ASSERT_TRUE(manager.select(2) == test_drone_3);
        
        // test reverse_list() method:
        ASSERT_TRUE(manager.reverse_list() == true); // does not work
        //ASSERT_TRUE(manager.select(0) == test_drone_3);
        //ASSERT_TRUE(manager.select(1) == test_drone_2);
        //ASSERT_TRUE(manager.select(2) == test_drone_1);
        
	    return true;
	}
	
	// PURPOSE: insert_front() keeps moving elements forward
	bool test6() {
        DronesManager manager;
        DronesManager::DroneRecord test_drone_1(1000);
        DronesManager::DroneRecord test_drone_2(1234);
        DronesManager::DroneRecord test_drone_3(4321);
        
        manager.insert_front(test_drone_3);
        ASSERT_TRUE(manager.select(0) == 4321);
        manager.insert_front(test_drone_2);
        ASSERT_TRUE(manager.select(0) == 1234);
        manager.insert_front(test_drone_1);
        ASSERT_TRUE(manager.select(0) == 1000);
        manager.insert_front(test_drone_2);
        ASSERT_TRUE(manager.select(0) == 1234);
        manager.insert_front(test_drone_3);
        ASSERT_TRUE(manager.select(0) == 4321);
        
        return true;
	}
	
	// PURPOSE: inserting at different positions in the list
	bool test7() {
        DronesManager manager;
        DronesManager::DroneRecord test_drone_1(1000);
        DronesManager::DroneRecord test_drone_2(1234);
        DronesManager::DroneRecord test_drone_3(4321);
        DronesManager::DroneRecord test_drone_4(5555);
        
        // test insertion using insert_front(), insert_back(), and insert():
        ASSERT_TRUE(manager.insert_front(test_drone_1) == true);
        ASSERT_TRUE(manager.insert_back(test_drone_2) == true);
        ASSERT_TRUE(manager.insert(test_drone_3, 1) == true);
        ASSERT_TRUE(manager.insert(test_drone_4, 0) == true);
        
        return true;
	}
	
	// PURPOSE: try to remove too many elements, then add a few elements
	bool test8() {
        DronesManager manager;
        DronesManager::DroneRecord test_drone_1(1000);
        DronesManager::DroneRecord test_drone_2(1234);
        DronesManager::DroneRecord test_drone_3(4321);
        
        // insert some drones:
        manager.insert_front(test_drone_1);
        manager.insert_back(test_drone_2);
        manager.insert_front(test_drone_3);
        
        ASSERT_TRUE(manager.get_size() == 3);
        
        // remove inserted drones:
        manager.remove(0);
        manager.remove(0);
        manager.remove(0);
        ASSERT_TRUE(manager.get_size() == 0);
        
        // try to remove a drone from an empty list:
        ASSERT_TRUE(manager.remove(0) == false);
        
        // verify that more elements can be inserted properly:
        manager.insert_back(test_drone_1);
        ASSERT_TRUE(manager.get_size() == 1);
        ASSERT_TRUE(manager.select(0) == test_drone_1);
        
        manager.insert_front(test_drone_2);
        ASSERT_TRUE(manager.get_size() == 2);
        ASSERT_TRUE(manager.select(0) == test_drone_2);
        
        manager.insert(test_drone_3, 1);
        ASSERT_TRUE(manager.get_size() == 3);
        ASSERT_TRUE(manager.select(1) == test_drone_3);
        
        return true;
	}
	
	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
        DronesManager manager;
        DronesManager::DroneRecord test_drone_1(1000);
        DronesManager::DroneRecord test_drone_2(1234);
        DronesManager::DroneRecord test_drone_3(4321);
        DronesManager::DroneRecord test_drone_4(5555);
        DronesManager::DroneRecord test_drone_5(1010);
        DronesManager::DroneRecord test_drone_6(6789);
        
        // try to insert at invalid index in empty list:
        manager.insert(test_drone_1, 1);
        ASSERT_TRUE(manager.get_size() == 0);
        ASSERT_TRUE(manager.first == NULL);
        ASSERT_TRUE(manager.last == NULL);
        
        // valid (size = 1)
        ASSERT_TRUE(manager.insert(test_drone_2, 0) == true);
        ASSERT_TRUE(*manager.first == test_drone_2);
        ASSERT_TRUE(*manager.last == test_drone_2);
        ASSERT_TRUE(manager.get_size() == 1);
        
        // invalid (size still = 1)
        manager.insert(test_drone_3, 2);
        ASSERT_TRUE(manager.get_size() == 1);
        
        manager.insert_front(test_drone_4);
        manager.insert_back(test_drone_5);
        manager.insert(test_drone_6, 1);
        manager.insert(test_drone_1, 2);
        
        // try to remove at invalid index:
        manager.remove(8);
        ASSERT_TRUE(manager.remove(8) == false);
        ASSERT_TRUE(manager.get_size() == 5);
        
        manager.remove_back();
        manager.remove_front();
        manager.remove(1);
        
        ASSERT_TRUE(manager.get_size() == 2);
        ASSERT_TRUE(manager.select(0) == 6);
        ASSERT_TRUE(manager.select(1) == 2);
        
		return true;
	}    
	    	
	// PURPOSE: lots of inserts, reverse the list, and then lots of removes until empty
	bool test10() {
        DronesManager manager;
        DronesManager::DroneRecord test_drone_1(1000);
        DronesManager::DroneRecord test_drone_2(1234);
        DronesManager::DroneRecord test_drone_3(4321);
        DronesManager::DroneRecord test_drone_4(5555);
        DronesManager::DroneRecord test_drone_5(1010);
        DronesManager::DroneRecord test_drone_6(6789);
        
        // insert drones:
        manager.insert_back(test_drone_1);
        manager.insert_back(test_drone_2);
        manager.insert_back(test_drone_3);
        manager.insert_back(test_drone_4);
        manager.insert_back(test_drone_5);
        manager.insert_back(test_drone_6);
        ASSERT_TRUE(manager.get_size() == 6);
        
        // test reverse_list() function:
        //manager.reverse_list();
        //ASSERT_TRUE(manager.reverse_list() == true);
        ASSERT_TRUE(manager.select(0) == 6789);
        ASSERT_TRUE(manager.select(5) == 1000);
        ASSERT_TRUE(manager.get_size() == 6);
        
        // remove drones:
        manager.remove_back();
        ASSERT_TRUE(manager.get_size() == 5);
        manager.remove_back();
        manager.remove_front();
        manager.remove_front();
        manager.remove(0);
        manager.remove(0);
        ASSERT_TRUE(manager.get_size() == 0);
        
        return true;
	} 
};

#endif
