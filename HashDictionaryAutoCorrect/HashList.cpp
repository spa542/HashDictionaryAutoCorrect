#include "HashList.h"

/*
 * Default Constructor:
 * Initializes data to default values
 */
HashList::HashList() {
	head = nullptr;
	tail = nullptr;
}

/*
 * Copy Constructor:
 * Does necessary deep copy for the given list
 */
HashList::HashList(const HashList& old) {
	head = nullptr;
	tail = nullptr;
	HashNode* cursor = old.tail;
	if (cursor == nullptr) {
		return;
	}
	while (cursor) {
		insert(cursor->word);
		cursor = cursor->prev;
	}
}

/*
 * Destructor:
 * Deletes dynamically allocated data
 */
HashList::~HashList() {
	if (head == nullptr) {
		return;
	}
	while (head->next) {
		head = head->next;
		delete head->prev;
	}
	delete head;
}

/*
 * Overloaded Assignment:
 * Performs deep copy overloaded assignment
 */
HashList& HashList::operator=(const HashList& rhs) {
	if (this == &rhs) {
		return *this;
	}

	if (head) {	
		while (head->next) {
			head = head->next;
			delete head->prev;
		}
		delete head;
	}

	head = nullptr;
	tail = nullptr;
	HashNode* cursor = rhs.tail;
	if (cursor == nullptr) {
		return *this;
	}
	while (cursor) {
		insert(cursor->word);
		cursor = cursor->prev;
	}

	return *this;
}

/*
 * insert Function:
 * Inserts a given word at the beginning of the list
 */
void HashList::insert(std::string insertMe) {
	HashNode* newNode = new HashNode();
	newNode->word = insertMe;
	newNode->next = nullptr;
	newNode->prev = nullptr;
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
		return;
	}
	newNode->next = head;
	head = newNode;
	head->next->prev = head;
}

/*
 * print Function:
 * Prints the linked list for testing purposes
 */
void HashList::print() {
	if (head == nullptr) {
		// Emptpy list
		return;
	}
	HashNode* cursor = head;
	while (cursor) {
		std::cout << cursor->word << " ";
		cursor = cursor->next;
	}
	std::cout << std::endl;
}

/*
   isInList Function:
   Returns if a given hash is in the list or not
*/
bool HashList::isInList(std::string check) {
	if (head == nullptr) {
		return false;	
	}
	HashNode* cursor = head;
	while (cursor) {
		if (cursor->word == check) {
			return true;	
		}
		cursor = cursor->next;
	}
	return false;
}

/*
   getLength Function:
   Returns the length of the linked list
*/
int HashList::getLength() {
	int numOfNodes = 0;
	if (head == nullptr) {
		return numOfNodes;
	}
	HashNode* cursor = head;
	while (cursor) {
		numOfNodes++;
		cursor = cursor->next;
	}
	return numOfNodes;
}

/*
   getWords Function:
   Returns all the words in the linked list as a string array
*/
std::string* HashList::getWords() {
	if (head == nullptr) {
		return nullptr;
	}
	HashNode* cursor = head;
	std::string* rtnMe = new std::string[this->getLength()];
	for (int i = 0; cursor; i++) {
		rtnMe[i] = cursor->word;	
		cursor = cursor->next;
	}
	return rtnMe;
}
