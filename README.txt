Names: Deeya Patel, Aditi Parekh
NetId: dmp450, avp126

There are three primary components behind performing spellcheck on the user-inputted directory/file: recursive directory traversal on the user-passed argument of the directory/file and opening them, reading the contents of the .txt files and organizing the contents in terms of row and column, and performing the spell checking functionality by comparing words in the text file to the user-inputting dictionary argument. 

We designed our code to perform these functionalities, by dividing them into primarily 5 different functions. 

Main(): The main function fills up the contents of the user-inputted dictionary into an array and calsl traversal() on the user-inputted file/directory.

Traversal(): Takes in the dictionary array, size of dictionary array, and path of the file/directories and recursively traverses through the user-inputted file/directory using the dirent library. Then, it calls spellchecker() only on .txt files, and doesn’t go through with functions starting with “.”

Spellchecker(): It is a void function that takes in the parameters: dictionary array, the size of the dictionary, and the name of the path. It opens the appropriate file and keeps track of the line and column numbers of the words in .txt files. It also accounts for printing error statements when a word is not in the dictionary, in accordance with the all capital, all lower case, MacDonald, and initial capital cases. The spellchecker() method calls on findwordindict() to search for the target word, which is a word in the text file in comparision to words in the dictionary array. Spellchecker() also considers hyphen words, by dividing the words by the hyphen delimiter before spell-checking each part of the hyphenated word. Spellchecker() calls upon fixword(), which takes in the char * to the word in the .txt file, and checks and gets rid of any starting or ending punctuation. 

Findwordindict(): This method searches for and returns a dictionary pointer that points to the word in dictionary corresponding to the targetword (word in text file). It calls on binary search to search through the dict array, and if binary search returns -1, it performs a case insensitive search of dictionary to return a pointer to a dictionary word. If target word is not in dictionary, and hence, findwordindict() returns NULL, the spellchecker() method prints out an error statement with the file name, line and column number, as well as the word in the text file (the target word).

Output(): findwordindict() calls on output(). The output function takes in the target word and the pointer to the word in dictionary to check if target word falls into any of the four allowed cases: if it is all capital, if it's lowercase (corresponding to the dictionary word), if it has an initial capital case, or if it falls into the "MacDonald" case. Output() returns a pointer to targetword if it is acceptable, and NULL otherwise. 

Testing Strategy
Dictionaries (all sorted with case sensitivity based on ASCII values)
We tested our code using:
1. the /usr/share/dict/words dictionary
2. all_lower - a dictionary of 10 words that are all lowercase 
3. all_upper - a dictionary of 10 words that are all uppercase
4. my_dict - a dictionary with words that are all lowercase, all uppercase, or a mix of uppercase and lowercase to address cases such as the hello, Hello, HELLO and MacDonald and MACDONALD cases
Hyphenated words were included in all 5 of these dictionaries.

Comparision Directories/Files
We tested our code against single files that begin with a '.', do not end in ".txt", those that require no directory traversal to reach, and those that do require directory traversal to reachh.
Additionally, we tested our code to open subdirectories and directories within these subdirectories that do and don't start with '.'.
file1 - regular file
works.txt - regular text file
.wrong - a file that starts with '.'
my_files - directory
my_files/baz - subdirectory
my_files/one.txt - regular text file in the first level
my_files/baz/.no.txt - a file that starts with '.' in the second level
my_files/baz/bar.txt - regular text file in the second level
my_files/baz/two.txt - another regular text file in the second level
my_files/baz/house - directory within subdirectory
my_files/baz/house/three.txt - regular text file in the third level
my_files/baz/house/unopened.h - does not end in ".txt" extension
.notright - a directory that starts with '.'
.notright/stuff.txt - regular text file in the first level

Command Line Arguments
We tested our code with each directory name (as the third command line argument) against the dictionaries. 
We also tested our code with multiple directory names (3rd to nth command line arguments) against the dictionaries. 
    The order of these arguments did not affect the output of our code. 
    Whether or not a command line argument corresponded to a regular file or a directory did not matter for the order.