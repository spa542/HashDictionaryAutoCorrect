#include "Dictionary.h"

/*
 * Default Constructor:
 * Initializes private member data to default attributes
 */
Dictionary::Dictionary() {
	arr = new HashList[8192];
	length = 8192;
	usage = new int[length];
	for (int i = 0; i < length; i++) {
		usage[i] = 0;
	}
}

/*
 * Copy Constructor:
 * Does necessary operations in order to deep copy
 */
Dictionary::Dictionary(const Dictionary& old) {
	arr = new HashList[old.length];
	length = old.length;
	usage = new int[old.length];
	for (int i = 0; i < length; i++) {
		arr[i] = old.arr[i];
	}
	for (int i = 0; i < length; i++) {
		usage[i] = old.usage[i];
	}
}

/*
 * Destructor:
 * Deallocates dynamically allocated data
 */
Dictionary::~Dictionary() {
	delete [] arr;
	delete [] usage;
}

/*
 * Overloaded Assignment:
 * Performs a necessary deep copy for assignment
 */
Dictionary& Dictionary::operator=(const Dictionary& rhs) {
	if (this == &rhs) {
		return *this;
	}

	delete [] arr;
	delete [] usage;

	arr = new HashList[rhs.length];
	length = rhs.length;
	usage = new int[rhs.length];
	for (int i = 0; i < length; i++) {
		arr[i] = rhs.arr[i];
	}
	for (int i = 0; i < length; i++) {
		usage[i] = rhs.usage[i];
	}

	return *this;
}

/*
 * insert Function:
 * Inserts a given string into the hash table
 */
void Dictionary::insert(std::string words) {
	arr[hash(words) > 8191 ? 0 : hash(words)].insert(words);
	usage[hash(words) > 8191 ? 0 : hash(words)]++;
}

/*
 * hash Function:
 * Hashes an a string into an index to be inserted into an array
 */
size_t Dictionary::hash(std::string hashMe) {
	size_t w = 32;
	size_t p = 13;
	size_t a = 362824561;

	size_t sum = 0;
	size_t seven = 7;
	for (size_t i = 0; i < hashMe.length(); i++) {
		sum += (size_t) (hashMe[i] << i * seven);	
	}
	size_t ax = a * sum;

	const size_t ONE = 1;
	size_t twoToW = ONE << w;

	size_t axModW = ax & (twoToW - ONE);
	size_t hash = axModW >> (w - p);

	return hash;
}

/*
 * print Function:
 * Prints the hash table for testing purposes
 */
void Dictionary::print() {
	for (int i = 0; i < 10; i++) {
		arr[i].print();
	}
}

/*
 * printUsage Function:
 * Prints the usage table to see how much of the hash 
 * table is being used
 */
void Dictionary::printUsage() {
	for (int i = 0; i < 10; i++) {
		std::cout << usage[i] << std::endl;
	}
}

/*
   findBiggestBucket Function:
   Fines the largest bucket size
*/
int Dictionary::findBiggestBucket() {
	int max = 0;
	for (int i = 0; i < length; i++) {
		if (usage[i] > max) {
			max = usage[i];
		}
	}
	return max;
}

/*
   findSmallestBucket Function:
   Finds the smallest bucket size
*/
int Dictionary::findSmallestBucket() {
	int min = 8192;
	for (int i = 0; i < length; i++) {
		if (usage[i] < min) {
			min = usage[i];
		}
	}
	return min;
}

/*
   countUsedBuckets Function:
   Returns the amount of buckets filled
*/
int Dictionary::countUsedBuckets() {
	int num = 0;
	for (int i = 0; i < length; i++) {
		if (usage[i] > 0) {
			num++;
		}
	}
	return num;
}

/*
   getLength Function:
   Gest the length of the hash table
*/
int Dictionary::getLength() {
	return length;
}

/*
   avgNodes Function:
   Returns the average amount of noeds in each bucket
*/
double Dictionary::avgNodes() {
	double sum = 0;
	for (int i = 0; i < length; i++) {
		sum += usage[i];
	}
	return sum / (double)length;
}

/*
   isInHash Function:
   Returns if the string is in the hash or not
*/
bool Dictionary::isInHash(std::string check) {
	bool rtnMe = arr[hash(check)].isInList(check);
	return rtnMe;
}

/*
   findSuggestions Function:
   Finds all the suggestions for errors for one edit distance and returns a hashlist 
   with those suggestions
*/
HashList Dictionary::findSuggestions(std::string errorWord) {
	HashList suggestions;	
	replaceChar(suggestions, errorWord);
	addChar(suggestions, errorWord);
	delChar(suggestions, errorWord);
	swapChar(suggestions, errorWord);
	return suggestions;
}

/*
   findSuggestions Function:
   Fins all the suggestions for errors for two edit distances and returns a hashlist 
   with those suggestions
*/
HashList Dictionary::findSuggestions(HashList oneEdit) {
	std::string* oneEditWords = oneEdit.getWords();
	HashList suggestions;
	for (int i = 0; i < oneEdit.getLength(); i++) {
		replaceChar(suggestions, oneEditWords[i]);
		addChar(suggestions, oneEditWords[i]);
		delChar(suggestions, oneEditWords[i]);
		swapChar(suggestions, oneEditWords[i]);
	}
	delete [] oneEditWords;
	return suggestions;
}

/*
   replaceChar Function:
   Checks for errors by replacing chars with different chars
*/
void Dictionary::replaceChar(HashList& suggestions, std::string editMe) {
	std::string original = editMe;
	for (int i = 0; i < original.length(); i++) {
		for (char j = 'a'; j <= 'z'; j++) {
			editMe[i] = j;
			if (isInHash(editMe)) {
				suggestions.insert(editMe);	
			}
			editMe = original;
		}
	}
}

/*
   addChar Function:
   Checks for errors by adding characters to various parts of the word
*/
void Dictionary::addChar(HashList& suggestions, std::string editMe) {
	std::string original = editMe;
	for (int i = 0; i < original.length(); i++) {
		for (char j = 'a'; j <= 'z'; j++) {
			editMe = editMe.substr(0, i) + j + editMe.substr(i, original.length());
			if (isInHash(editMe)) {
				suggestions.insert(editMe);
			}
			editMe = original;
		}
	}
}

/*
   delChar Function:
   Checks for errors by deleting characters 
*/
void Dictionary::delChar(HashList& suggestions, std::string editMe) {
	std::string original = editMe;
	for (int i = 0; i < original.length(); i++) {
		editMe.erase(i, 1);
		if (isInHash(editMe)) {
			suggestions.insert(editMe);
		}
		editMe = original;
	}
}

/*
   swapChar Function:
   Checks for errors by swapping characters in place
*/
void Dictionary::swapChar(HashList& suggestions, std::string editMe) {
	std::string original = editMe;
	for (int i = 0; i < original.length(); i++) {
		for (int j = i + 1; j < original.length(); j++) {
			if (i != j) {
				std::swap(editMe[i], editMe[j]);
				if (isInHash(editMe)) {
					suggestions.insert(editMe);
				}
				editMe = original;
			}
		}
	}
}
