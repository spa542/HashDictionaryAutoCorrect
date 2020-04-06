#include <iostream> // cout, endl, ispunct
#include <string> // std::string
#include <stdio.h> // printf
#include <fstream> // ifstream
#include "Dictionary.h" // Dictionary
#include "HashList.h" // HashList
#include <time.h> // time
#include <chrono> // chrono
#include <cctype> // tolower
#include <sstream> // istringstream
#include <algorithm> // transform

#define ANSI_COLOR_YELLOW "\x1b[33m" // yellow highlighting
#define ANSI_COLOR_RESET "\x1b[0m" // regular console highlighting

int main(int argc, char** argv) {

	int argCount = argc;
	if (argCount != 2) { // Error Code for incorrect arguments
		std::perror("Cannot Execute Program: Error Code\n\t--Amount of arguments incorrect");
		exit(1);
	}
	std::ifstream inFile;
	try {
			inFile.open(argv[1]);
	} catch (...) {
		std::perror("Error: File input not found"); // Error code for incorrect file name
		exit(1);
	}

	std::cout << "Welcome to the Spell Checker!" << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << "Loading the database..." << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;

	Dictionary d;
	std::string inputWord;
	int numOfWords = 0;

	auto start = std::chrono::system_clock::now();

	while(inFile.peek() != EOF) {
		std::getline(inFile, inputWord);
		transform(inputWord.begin(), inputWord.end(), inputWord.begin(), ::tolower);	
		d.insert(inputWord);
		numOfWords++;
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	std::cout << "Total words = " << numOfWords << std::endl;
	std::cout << "Biggest bucket size = " << d.findBiggestBucket() << std::endl;
	std::cout << "Smallest bucket size = " << d.findSmallestBucket() << std::endl;
	std::cout << "Total number of buckets = " << d.getLength() << std::endl;
	std::cout << "Number of used buckets = " << d.countUsedBuckets() << std::endl;
	std::cout << "Average number of nodes in each bucket = " << d.avgNodes() << std::endl;
	std::cout << "Total time taken = " << elapsed_seconds.count() << "s\n"; 
	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << std::endl;

	std::cout << "Please enter some text: " << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << std::endl;
	
	std::string word;
	std::string inputLine;
	int numMisspelled = 0;
	int numOfSuggestions = 0;

	std::getline(std::cin, inputLine);
	std::istringstream iss(inputLine);

	while (iss >> word) {
		std::string originalWord = word;
		std::string garb;
		for (int i = 0, len = word.length(); i < word.length(); i++) {
			if (ispunct(word[i])) {
				word.erase(i--, 1);
				len = word.length();
			}
		}
		transform(word.begin(), word.end(), word.begin(), ::tolower);

		start = std::chrono::system_clock::now();

		if (!d.isInHash(word)) {
			std::istringstream highlightInc(inputLine);
			std::cout << std::endl;
			std::cout << "---------------------------------------------------" << std::endl;
			std::cout << std::endl;
			while (highlightInc >> garb) {
				if (garb == originalWord) {
					printf(ANSI_COLOR_YELLOW "%s " ANSI_COLOR_RESET, garb.c_str());
				} else {
					printf("%s ", garb.c_str());	
				}
			}
			std::cout << std::endl;
			numMisspelled++;
			std::cout << std::endl;
			printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, originalWord.c_str());
			std::cout << " is misspelled! Below are the words within one edit distance" << std::endl;
			std::cout << "---------------------------------------------------" << std::endl;
			std::cout << std::endl;
			
			HashList suggestions = d.findSuggestions(word);
			numOfSuggestions += suggestions.getLength();

			std::cout << "Suggestions for ";
			printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, originalWord.c_str());
			std::cout << ": ";
			suggestions.print();
			
			std::cout << std::endl;
			std::cout << "The following are within two edit distances" << std::endl;
			std::cout << "---------------------------------------------------" << std::endl;
			std::cout << std::endl;

			HashList moreSuggestions = d.findSuggestions(suggestions);
			numOfSuggestions += moreSuggestions.getLength();

			std::cout << "Suggestions for ";
			printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET, originalWord.c_str());
			std::cout << ": ";
			moreSuggestions.print();
		}
		
		end = std::chrono::system_clock::now();
		elapsed_seconds = end - start;
		end_time = std::chrono::system_clock::to_time_t(end);
	}

	std::cout << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << "Summary" << std::endl;
	std::cout << "---------------------------------------------------" << std::endl;
	std::cout << "Number of misspelled words = " << numMisspelled << std::endl;
	std::cout << "Number of suggestions = " << numOfSuggestions << std::endl;
	std::cout << "Time required to find suggestions = " << elapsed_seconds.count() << "s\n";
		
	inFile.close();	

	return 0;
}
