/**
 * This program reads in multiple documents and calculates their similarities based on their content
 *
 * @author Dylan Hall and Nathan Cooper
 * @date 1/22/2017
 * @info Course COP4534
 */

//Includes
#include "document.h"
#include "chkgets.h"
#include "dictionary.h"
#include "word.h"

//Main Function; runs program
int main(int argc, char **argv) {

	//Displays help; usage
	if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "-help") == 0) {
		showUsage();
		return 0;
	}

	int debug = -1;
	if (argc == 3)
	{
		//Displays debug
		if (strcmp(argv[2], "-d") == 0 || strcmp(argv[2], "-debug") == 0) {
			debug = 0;
		}
	}
	
	//Checks to make sure command line arugment is a directory, later will allow single files aswell
	if (isDirectory(argv[1]) != 1) {
		fprintf(stderr, "%s: not a directory; [ -h || -help] for usage.",
				argv[1]);
		exit(EXIT_FAILURE);
	}

	DictionaryT* dictionary = newDictionary(200);	// the inverted index to be added to and manipulated
	FrequencyT* frequency = newFrequency(200);		// the frequency index to be added to and manipulated

	readDocs(dictionary, frequency, argv[1], debug); //gets the actual documents, and opens them

	freqDelete(frequency);
	dicdelete(dictionary);
	return 0;
}
