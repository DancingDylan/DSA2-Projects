/**
 * Contains functions that process, edit,
 * and modifies string data using pointers.
 *
 * @author Dylan Hall and Nathan Cooper
 * @date 1/22/2017
 * @info Course COP4534
 */


#include "document.h"
#include "chkgets.h"

/** -toString function-
 * @ params: Document document, unsigned short filecount
 *
 * @ unsigned short filecount: used throughout the code to retain the number of documents.
 *     -allows reusability
 *     -code is more dynamic
 *
 * Function saves an entire document of text into a single string of memory.
 *   i.e. finds total size of a document in bytes, then allocates memory equal to
 *        the nubmer of bytes to a text, that the document gets loaded into
 */
void toString(DocumentT** document, DictionaryT* dictionary,
		FrequencyT* frequency, StopWordListT* stopList) {

	FILE* fp = fopen(document[dictionary->counter]->name, "r");

	if (fp == NULL) {
		perror("Error");
		exit(1);
	}

	size_t i, nmemb = 0;

	fseek(fp, 0, SEEK_END);
	nmemb = ftell(fp) + 1;
	rewind(fp);

	document[dictionary->counter]->text = (char*) malloc(sizeof(char) * nmemb);
	if (!document[dictionary->counter]->text) {
		printf("Failed to allocate memory for document->text.\n");
		exit(1);
	}

	memset(document[dictionary->counter]->text, 0, nmemb); // Initializes all of the text to null
	fread(document[dictionary->counter]->text, sizeof(char), nmemb, fp); // reading in the entire document
	fclose(fp);

	// set all of the words to lower case
	for (i = 0; document[dictionary->counter]->text[i]; i++) {
		document[dictionary->counter]->text[i] = tolower(document[dictionary->counter]->text[i]);
	}

	tokenize(document, dictionary, frequency, stopList); //tokenize the entire document; split the text into individual words to be processed

}

/** -tokenize function-
 * @params: Document document, unsigned short filecout
 *     -same as above function params
 *
 * Function tokenizes a string, or splits it based on a set of delimiters
 *
 */

void tokenize(DocumentT** document, DictionaryT* dictionary,
		FrequencyT* frequency, StopWordListT* stopList) {

	//for the tokenizing
	char* tok = NULL;
	char* saveptr = NULL;

	tok = strtok_r(document[dictionary->counter]->text, DELIMITER, &saveptr);

	// as long as their are tokens left in the document add them to the dictionary and frequency ADTs
	while (tok != NULL) {
		tok = strtok_r(NULL, DELIMITER, &saveptr);

		if (checkWord(tok, stopList) == 1) {
			dicadd(dictionary, tok, dictionary->counter);
			freqAdd(frequency, tok, dictionary->counter);
		}
	}
}

/** -checkWord function-
 *
 *  @params: char* tok, StopWordListT* stopList
 *
 *  -tok: token of the text passed to this function to be compared with
 *  -stopList: a list of the stop words to compare to the token passed
 *
 *  function takes in a list of stop words, and a current token within a doucment
 *  from strtok, then uses a binary search to compare the words, then returns
 *  1 if not found, 0 if found.
 *
 */

int checkWord(char* tok, StopWordListT* stopList) {

	if (tok == NULL)
		return 0;

	// Implements a binary search for determining if a particular word is in the stopword list
	unsigned int upper = stopList->size - 1;
	unsigned int lower = 0, midpoint = 0;

	while (upper >= lower) {
		midpoint = (lower + upper) / 2;

		if (strcmp(stopList->text[midpoint], tok) > 0) {
			upper = midpoint - 1;
		} else if (strcmp(stopList->text[midpoint], tok) < 0) {
			lower = midpoint + 1;
		} else
			return 0;
	}

	if (strcmp(stopList->text[midpoint], tok) < 0)
		midpoint++;
	return 1;
}

void createStopList(StopWordListT* newList) {

	// Create a stopword list container
	newList->size = lineCount(STOPWORDFILE) + 1;
	newList->text = (char**) malloc(sizeof(char*) * newList->size);

	memset(newList->text, 0, newList->size);

	char word[WORDLENGTH];
	FILE *fp = fopen(STOPWORDFILE, "r");
	size_t i = 0;

	while (!feof(fp)) {
		fscanf(fp, "%s", word);
		newList->text[i] = (char*) malloc(sizeof(char) * WORDLENGTH);
		strcpy(newList->text[i], word);
		i++;
	}

	fclose(fp);

}

/** -getStopWords-
 * @params a double pointer to be manipulated into an array and hold the stop words
 *
 * Function opens the file (currently hardcoded file name)
 * and scans and pulls out the stop words for later use.
 *
 */

/** -show_usage function-
 * #not currently implemented
 *    -later will be called when and if the user inputs incorrect command line arguments
 *    -either files or paths that aren't accessible, readable, are empty, dont exist
 *    -or they didnt add enough arguments, or too man
 *
 */

void showUsage(void) {
	printf("Usage: ./docusim ./dir [-d || -h]\n");
}

/** -docDelete function -
 * credit: nathan
 *
 * Function takes in document types,
 * and free's the associated structure
 *
 */

void docdelete(DocumentT** document) {

	// free all of the documents contained in the document array
	size_t i;
	for (i = 0; i < MAXDOCS; i++) {
		free(document[i]->text);
		free(document[i]);
	}

}

/** -freeList function-
 *
 * Function frees the stop word list:
 * stopList; of type StopWordListT
 *
 */

void freeList(StopWordListT* stopList) {

	size_t i;
	for (i = 0; i < stopList->size; i++)
		free(stopList->text[i]);

	free(stopList->text);
	free(stopList);

	printf("Stop list has been freed\n");
}

