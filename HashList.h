#ifndef _HASHLIST_H_
#define _HASHLIST_H_
#include <iostream>
#include <string>

class HashList {
	private:
		struct HashNode {
			std::string word;
			HashNode* next;
			HashNode* prev;
		};

		HashNode* head;
		HashNode* tail;
	public:
		HashList(); // Default Constructor
		HashList(const HashList&); // Copy Constructor
		~HashList(); // Deconstructor
		HashList& operator=(const HashList&); // Overloaded Assignment

		void insert(std::string); // Inserts a string node at the head of list
		void print(); // Prints the linked list for testing purposes
		int getLength(); // Returns the length of the linked list

		bool isInList(std::string); // Returns if a given word is in the linked list
		std::string* getWords(); // Returns all the words of the linked list as an 
								// array of strings
};

#endif
