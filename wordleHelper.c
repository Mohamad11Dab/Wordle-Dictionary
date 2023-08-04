#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <csse2310a1.h>
#define BEST "-best"
#define ALPHA "-alpha"
#define WITH "-with"
#define WITHOUT "-without"
#define LENGTH "-len"
#define MAX_ARGUMENTS 9
#define DEFAULT_SIZE 5
#define UNDERSCORE '_'
#define MAX_LENGTH 9
#define MIN_LENGTH 4

/* check_word()
* ------------
* This function checks if a string contains letters only 
*
* string: pointer to a string(char*) that is being checked
*
* Return: returns a value of 1 if all characters in the string are letters.
* returns 0 otherwise
*
*
*/
int check_word(char* string) {
    for (int i = 0; i < strlen(string); i++) {
        if (isalpha(string[i])) {
	    ;
	} else {
	    return 0;
	}
    }
    return 1;
}

/* length_method()
* --------------
* This function checks for "-len" argument in the command line.
*
* string: pointer to a string(char*) that is being checked
* argc: number of arguments in the command line
* argv: pointer to the arguments in the command line
*
* Return: if -len argument is present, return 1 if string's length matches 
* the number given after the argument, 0 otherwise.  
* if not present, return 1 if string's length matches the default length
* of 5, 0 otherwise
*
*/
int length_match(char* string, int argc, char** argv) {
    int length = 0;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], LENGTH) == 0) {
	    length = atoi(argv[i + 1]);
	    break;
        } else {
            length = DEFAULT_SIZE;
        }  
    }
    if (strlen(string) == length) {
	return 1;
    } else {
	return 0;
    }
}

/* pattern_match()
* --------------
* This function checks for a pattern in the command line
*
* string: pointer to a string(char*) that is being checked
* argc: number of arguments in the command line
* argv: pointer to the arguments in the command line
* 
* Return: if pattern is present, return 1 if the string matches
* the pattern given in the command line, 0 otherwise
* if pattern not present, return 1
*
*/
int pattern_match(char* string, int argc, char** argv) {
    int patternFound = 0;
    char patternString[100];
    if (length_match(string, argc, argv) == 0) {
	return 0;
    }
    for (int i = argc - 1; i > 0; i--) {
	if (strcmp(argv[i - 1], LENGTH) == 0 ||
                strcmp(argv[i - 1], WITHOUT) == 0 ||
                strcmp(argv[i - 1], WITH) == 0 || argv[i][0] == '-') {
	;
        } else {
            patternFound = 1;
	    strcpy(patternString, argv[i]);
        }
    }
    if (patternFound == 0) {
	return 1;
    } else {
        for (int k = 0; k < strlen(string); k++) {
	    string[k] = tolower(string[k]);
	}	
        for (int l = 0; l < strlen(patternString); l++) {
	    if (isalpha(patternString[l])) {
                patternString[l] = tolower(patternString[l]);
	    }
        }  
        for (int h = 0; h < strlen(string); h++) {
            if (isalpha(patternString[h])) {
                if (string[h] == patternString[h]) {
                    continue;
                } else {
                    return 0;
                }
            } else {
                continue;
            }
        }

        return 1;
    }
}

/* without_match()
* --------------
* This function checks for "-without" argument in the commad line
*
* string: pointer to a string(char*) that is being checked
* argc: number of arguments in the command line
* argv: pointer to the arguments in the command line 
*
* Return: if -without argument is present, return 1 if the string does
* not contain any letter from the series of letters following the -without
* argument, 0 otherwise
* if -without is not present, return 1
*
*/
int without_match(char* string, int argc, char** argv) {
    char withoutString[100];
    int withoutFound;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], WITHOUT) != 0) {
	    ;
	} else {
	    withoutFound = 1;
            strcpy(withoutString, argv[i + 1]);
	    break; 
        }
    }
    if (withoutFound == 0) {
        return 1;
    } else {
        for (int k = 0; k < strlen(string); k++) {
	    string[k] = tolower(string[k]);
	}	
        for (int l = 0; l < strlen(withoutString); l++) {
	    withoutString[l] = tolower(withoutString[l]);
	}
        for (int h = 0; h < strlen(withoutString); h++) {
            for (int g = 0; g < strlen(string); g++) {
                if (withoutString[h] == string[g]) {
                    return 0;
                }
            }
        }
        return 1;
    } 
}

/* with_match()
* ------------
* This function checks for "-with" argument in the command line
*
* string: pointer to a string(char*) that is being checked
* argc: number of arguments in the command line
* argv: pointer to the arguments in the command line
*
* Return: if "-with" is present, return 1 if the number of each letter in
* the series of letters following the argument is more or equal to the number
* of letters in the string, 0 otherwise. 
* if "-with" is not present, return 1
*
*/
int with_match(char* string, int argc, char** argv) {
    int withFound = 0, alphabet[26] = {0}, count, alphabet1[26] = {0}, count1; 
    char withString[100];
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], WITH) != 0) {
	    ;
        } else {
	    withFound = 1;
	    strcpy(withString, argv[i + 1]);
	    break; 
        }
    }
    if (withFound == 0) {
	return 1;	
    } else {
	for (int k = 0; k < strlen(string); k++) {
	    string[k] = tolower(string[k]);
	}	
	for (int l = 0; l < strlen(withString); l++) {
	    withString[l] = tolower(withString[l]);
	}
        for (int j = 0; string[j] != '\0'; j++) {
            if (string[j] >= 'a' && string[j] <= 'z') {
                count = string[j] - 'a';
                ++alphabet[count];
            }
        }
        for (int m = 0; withString[m] != '\0'; m++) {
            if (withString[m] >= 'a' && withString[m] <= 'z') {
                count1 = withString[m] - 'a';
                ++alphabet1[count1];
            }
        }
        for (int n = 0; n < 26; n++) {
	    if (alphabet1[n] <= alphabet[n]) {
	        continue;
	    } else {
	        return 0;
	    }
	}
        return 1;
    }
}

/* file_read()
* ----------
* Open the file for reading and output each line to check if the string is
* valid. If the string is valid, add it to an array of strings
* if the file can not be opened, print out a message to standard error and
* exit with exit status of 3
*
* argc: number of arguments in the command line
* argv: pointer to the arguments in the command line
*
* Return: return the pointer to array of valid strings
*
*/
char** file_read(int argc, char** argv){
    int bufferSize = 50;
    int numRead = 0;
    char** array = malloc(sizeof(char*) * bufferSize);
    for (int i = 0; i < bufferSize; i++) {
        array[i] = malloc(sizeof(char) * 50);
    }
    char* file = getenv("WORDLE_DICTIONARY");
    if (file == NULL) {
        file = "/usr/share/dict/words";
    }
    FILE* fp;
    if ((fp = fopen(file, "r"))) {
        ;
    } else {
	free(array);
	fprintf(stderr, "wordle-helper: dictionary file \"%s\""
                " cannot be opened\n",file);
	exit(3);
    }
    char buffer[50];
    char* line;
    while (( line = fgets(buffer, 50, fp))) {
        if (buffer[strlen(buffer) - 1] == '\n') {
            buffer[strlen(buffer) - 1] = '\0';
        }
        if (check_word(buffer) == 1) {
            if (with_match(buffer, argc, argv) == 1 &&
                    without_match(buffer, argc, argv) == 1 &&
                    length_match(buffer, argc, argv) == 1 &&
                    pattern_match(buffer, argc, argv) == 1) {
                if (numRead == bufferSize - 1) {
                    bufferSize *= 3;
                    array = realloc(array, sizeof(char*) * bufferSize);
                    for (int k = numRead + 1; k < bufferSize; k++) {
                        array[k] = malloc(sizeof(char) * 50);  
                    }
                }
                strcpy(array[numRead], buffer);
                numRead++;
            }
        }
    }
    fclose(fp);
    if (numRead == 0) {
	free(array);
	return NULL;
    }
    array[numRead] = "EOF";
    return array;
}

/* check_pattern()
* ---------------
* check for the validity of pattern argument
*
* argc: number of arguments in the command line
* argv: pointer to the arguments in the command line *
*
* If the pattern's length does not match the expected word length or
* if the pattern contains characters other than underscores and/or letters
* print out a message to standard error and exit with exit status of 2.
* if pattern argument is repeated more than once print out a message to
* standard error and exit with exit status of 1.
* Otherwise do nothing
*
*/
void check_pattern(int argc, char** argv) {
    int pattern = 0;
    int length;
    char string[1000];
    for (int j = 1; j < argc; j++) {
        if (strcmp(argv[j], LENGTH) == 0) {
            length = atoi(argv[j + 1]);
            break;
        } else {
	    length = DEFAULT_SIZE;
        }
    }
    for (int i = argc - 1; i > 0; i--) {
        if (strcmp(argv[i - 1], LENGTH) == 0 ||
                strcmp(argv[i - 1], WITHOUT) == 0 ||
                strcmp(argv[i - 1], WITH) == 0 || argv[i][0] == '-') {
            ;
        } else {
            for (int k = 0; k < strlen(argv[i]); k++) {
                if (isalpha(argv[i][k]) || argv[i][k] == UNDERSCORE) {
                    continue;
                } else {
                    fprintf(stderr, "wordle-helper: pattern must be of length"
                            " %i and only contain underscores and/or"
                            " letters\n", length);
                    exit(2);
                }
            }
            pattern++;
            strcpy(string, argv[i]);
 
        }
    }
    if (pattern > 1) {
        fprintf(stderr, "Usage: wordle-helper [-alpha|-best] [-len len] "
                "[-with letters] [-without letters] [pattern]\n");
        exit(1);
    }
    if (pattern == 1) {
        if (strlen(string) != length) {
            fprintf(stderr, "wordle-helper: pattern must be of length %i and "
                    "only contain underscores and/or letters\n", length);
            exit(2);
        }
    }
}

/* check_repetition()
* -----------------
* check if any argument is present more than once (except pattern)
*
* argc: number of arguments in the command line
* argv: pointer to the arguments in the command line
*
* print out a message to standard error and exit with exit status 1
* if any argument is repeated more than one or if -best and -alpha are 
* both given at the same time 
*
*/
void check_repetition(int argc, char** argv) {
    int best = 0;
    int alpha = 0;
    int with = 0;
    int without = 0;
    int length = 0;
    for (int i = 1; i < argc; i++) {
	if (strcmp(argv[i], BEST) == 0) {
	    best++;
        }	
	if (strcmp(argv[i], ALPHA) == 0) {
	    alpha++;
	}
	if (strcmp(argv[i], WITH) == 0) {
	    with++;
	}
	if (strcmp(argv[i], WITHOUT) == 0) {
	    without++;
	}
	if (strcmp(argv[i], LENGTH) == 0) {
	    length++;
	}
    }
    if (best > 1 || alpha > 1 || with > 1 || without > 1 || length > 1 ||
            (best > 0 && alpha > 0)) {
	fprintf(stderr, "Usage: wordle-helper [-alpha|-best] [-len len] "
                "[-with letters] [-without letters] [pattern]\n");
	exit(1);
    }	
}

/* print_error()
* -------------
* print out a message to standard error and exit with exit status 1
* if the command line is not valid.
*
*/
void print_error(void){
    
    fprintf(stderr, "Usage: wordle-helper [-alpha|-best] [-len len] " 
            "[-with letters] [-without letters] [pattern]\n");
    exit(1);

}

/* check_validity()
* ---------------
* check for the validity of the arguments in the command line
*
* argc: number of arguments in the command line
* argv: pointer to the arguments in the command line
*
* if the command line has more than 9 arguments OR
* if the argument following -with and -without(if present) has characters
* other than letter OR
* if argument following -len(if present) is not a digit between 4 and 9 
* inclusive OR
* if the argument starts with '-' but it is not one of -alpha, -best, -len,
* -with, or -without: execute print_out
*
*/
void check_validity(int argc, char** argv) {
    if (argc > MAX_ARGUMENTS) {
	print_error();
    }
    if (strcmp(argv[argc - 1], LENGTH) == 0 ||
            strcmp(argv[argc - 1], WITH) == 0 ||
            strcmp(argv[argc - 1], WITHOUT) == 0) {
	print_error();
    }
    for (int i = 1; i < argc; i++) {
	if (argv[i][0] == '-') {
            if (strcmp(argv[i], BEST) == 0 || strcmp(argv[i], ALPHA) == 0 ||
                    strcmp(argv[i], WITH) == 0 ||
                    strcmp(argv[i], WITHOUT) == 0 ||
                    strcmp(argv[i], LENGTH) == 0) {
	         ;
            } else {
	        print_error();
            }
        }
        if (strcmp(argv[i], LENGTH) == 0) {
	    for (int m = 0; m < strlen(argv[i + 1]); m++) {
		if (!isdigit(argv[i+1][m])) {
		    print_error();
		}
	    }
            if (atoi(argv[i + 1]) < MIN_LENGTH ||
                    atoi(argv[i + 1]) > MAX_LENGTH) {
	        print_error();
            }    
        }
        if (strcmp(argv[i], WITH) == 0 || strcmp(argv[i], WITHOUT) == 0) {
            for (int k = 0; k < strlen(argv[i + 1]); k++) {
                if (!isalpha(argv[i + 1][k])) {
        	    print_error();
                }
            }
        }
    }
}

/* count_strings()
* --------------
* count the number of strings in an array of strings
*
* array: pointer to an array of string from which the function
* counts the number os strings in it
*
* Return: the number of strings in the array of strings
*
*/
int count_strings(char** array) {
    int i = 0;
    do {
        if (strcmp(array[i], "EOF") == 0) {
	    break;
        }
	i++;
    } while (1);
    return i;
}

/* array_upper()
* ------------
* turn all the characters in the array of strings to upper-case letters
*
* array: pointer to an array of strings from which all the letters
* inside will be  turned to upper-case letters
*
*/
void array_upper(char** array) {
    int max = count_strings(array);
    for (int i = 0; i < max; i++) {
        for (int k = 0; k < strlen(array[i]); k++) {
            array[i][k] = toupper(array[i][k]);
        }
    }
}

/* remove_duplicate()
* ------------------
* remove all the duplicates in an array of strings
*
* array: pointer to an array of strings from which all the duplicates
* will be removed 
*
*/
void remove_duplicate(char** array) {
    int max = count_strings(array);
    for (int i = 0; i < max; i++) {
        if (strcmp(array[i], array[i + 1]) == 0) {
	    ;

	} else {
	    printf("%s\n", array[i]);
        }   
    }
}

/* best_compare()
* --------------
* qsort() comparator function for -best argument that compares two strings
*
* stringOne,stringTwo: pointers to strings that we're comparing
*
* Return: if the two strings has the same potential Wordle guess,
* return an integer less then, equal to, or greater than zero if the string
* pointed to by stringOne is less than, equal to or greater than the string
* pointed to by stringTwo
* Otherwise return an integer less then or greater than zero depending on
* whether stringOne is better or worse potential Wordle guess than stringTwo 
* Reference: This code was inspired by qsort(3) man page
*/
int best_compare(const void* stringOne, const void* stringTwo) {
    if (guess_compare(*(const char**)stringOne,
            *(const char**)stringTwo) == 0) {
	return strcmp(*(const char**)stringOne, *(const char**)stringTwo);
    } else {
        return -(guess_compare(*(const char**)stringOne,
                *(const char **)stringTwo));
    }
}

/* alpha_compare()
* −−−−−−−−−−−−−−−
* qsort() comparator function for -alpha argument that compares two strings.
*
* stringOne, stringTwo: pointers to strings (char*) that we’re comparing.
*
* Returns: an integer less then, equal to, or greater than zero if the string
* pointed to by str1 is less than, equal to or greater than the string
* pointed to by str2
* Reference: This code is taken from the qsort(3) man page.
*/
int alpha_compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

/* best_sort()
*-----------
* check if -best argument is present then sort the strings in the array
* of strings in the decreasing order of likelihood then exit with exit
* status 0
*
* array: pointer to an array of strings which needs to be sorted
* numberElements: number of elements in the array of strings
* argc: the number of arguments in the command line
* argv: pointer to the arguments in the command liney
*
* if -best argument is not present, nothing happens 
*
*/
void best_sort(char** array, int numberElements, int argc, char** argv) {

    for (int i = 1; i < argc; i++) {
	if (strcmp(argv[i], BEST) == 0) {
            array_upper(array);
            qsort(array, numberElements, sizeof( char* ), best_compare);
            remove_duplicate(array);
            free(array);
            exit(0);
        }
    }   
}

/* alpha_sort()
*-----------
* check if -alpha argument is present then sort the strings in the array
* of strings in alphabetical order then exit with exit
* status 0
*
* array: pointer to an array of strings which needs to be sorted
* numberElements: number of elements in the array of strings
* argc: the number of arguments in the command line
* argv: pointer to the arguments in the command liney
*
* if -alpha argument is not present, nothing happens 
*
*/
void alpha_sort(char** array, int numberElements, int argc, char** argv) {

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], ALPHA) == 0) {
            array_upper(array);
            qsort(array, numberElements, sizeof( char* ), alpha_compare);
            remove_duplicate(array);
            free(array);
            exit(0);
        }
    }   
}

int main(int argc, char** argv) {
    check_validity(argc, argv);
    check_repetition(argc, argv);
    check_pattern(argc, argv);
    char** array = file_read(argc, argv);
    //if array is empty exit with exit status of 4
    if (array == NULL) {
	exit(4);
    }
    alpha_sort(array, count_strings(array), argc, argv);
    best_sort(array, count_strings(array), argc, argv);
    int i = 0;
    array_upper(array);
    do {
        if (strcmp(array[i], "EOF") == 0) {
            break;
        }
        printf("%s\n", array[i]);
        i++;
    } while (1);
    free(array);

    return 0;
}

