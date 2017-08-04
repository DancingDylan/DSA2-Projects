/**
 * Contains functions that either checks parameters
 * or gets information from files or directories.
 *
 * @author Dylan Hall and Nathan Cooper
 * @date 1/22/2017
 * @info Course COP4534
 */

#include "document.h"
#include "chkgets.h"
#include "frequency.h"

/** -readDocs function-
 * @params document structure type, and an unsigned short to hold filecount
 *
 * Function uses above txt document to get and open the files, and saves their names
 * within the document strucuture
 *
 */


void readDocs(DictionaryT* dictionary, FrequencyT* frequency,
		const char* dirName, int debug) {

	DIR* dir;
	struct dirent* dirEntry;

	char absName[256] = { "\0" };	// the name of a file

	DocumentT* document[MAXDOCS];	// a Document array to store each document while creating the incidence matrix
	StopWordListT* stopList = (StopWordListT*) malloc(sizeof(StopWordListT));
	createStopList(stopList);

	if (!stopList) {
		printf("Failed to allocate memory for stopList.\n");
		exit(1);
	}

	if ((dir = opendir(dirName)) != NULL) {
		while ((dirEntry = readdir(dir)) != NULL) {		// read in the directory structure and create the documents from it
			if (strlen(dirEntry->d_name) > 2) {

				document[dictionary->counter] = (DocumentT*) malloc(
						sizeof(DocumentT));

				sprintf(absName, "%s/%s", dirName, dirEntry->d_name);
				document[dictionary->counter]->name = absName;

				FILE* fp = fopen(document[dictionary->counter]->name, "r");

				if (fp == NULL) {
					perror("Error");
					exit(1);
				} else {
					fclose(fp);
				}

				toString(document, dictionary, frequency, stopList); //sends the entire document to single string in memory
				dictionary->counter++;
			}
		}

		freeList(stopList);
		free(dirEntry);
	} else {
		printf("Failed to open directory.\n");
		showUsage();
		exit(1);
	}

	if (debug == 0)
		dicshow(dictionary);

	freqCalculateWeight(frequency);
	docusim(frequency);

	docdelete(document);
	closedir(dir);
}

/** -lineCount function-
 * @params chkName, #makes the function more dynamic for either directories or files
 *
 * Takes in a path, or name. Checks whether it is a file or directory.
 * Allows the function to be more flexible and reusable
 *
 * @returns an unsigned short of the file count
 *
 */

unsigned short lineCount(const char* chkName) {

	unsigned short linecount = 0;

	if (isFile(chkName) == 1) { //else the path is a file

		char line[256] = { 0x0 };
		FILE *fp = fopen(chkName, "r");

		while (fgets(line, 1023, fp)) //number of rows translate to number of files
		{
			++linecount;
		}

		fclose(fp);
		return linecount;
	} else { //else the path or name is neither a directory of file
		perror("Error");
		return -1;
	}
}

unsigned short fileListing(const char* chkName) {

	unsigned short foldercount = 0;

	if (isDirectory(chkName) == 1) {

		DIR *dirPointer;
		struct dirent* dirEntry;

		if ((dirPointer = opendir(chkName)) != NULL) {
			while ((dirEntry = readdir(dirPointer)) != NULL) {
				foldercount++;
			}
		}

		foldercount = foldercount - 2; //minus two to remove the . and .. path holders
		closedir(dirPointer);
		free(dirEntry);
		return foldercount;

	} else { //else the path or name is neither a directory of file
		perror("Error");
		return -1;
	}
}

/** -isDirectory function-
 * @params: const char pointer for a path or name
 *
 * Function just checks whether the passed parameter is a directory
 *
 * returns 1 if it is a direcoty, else returns -1
 *
 */
int isDirectory(const char* dir) {

	DIR *directory = opendir(dir);

	if (directory) {
		closedir(directory);
		return 1;
	} else {
		perror("Error");
		return -1;
	}
}

/** -isFile function-
 * @params: const char pointer for a path or name
 *
 * Function just checks whether the passed parameter is a file
 *
 * returns 1 if it is a direcoty, else returns -1
 *
 */
int isFile(const char* file) {

	FILE *fp = fopen(file, "r");
	if (file) {
		fclose(fp);
		return 1;
	} else {
		perror("Error");
		return -1;
	}
}
