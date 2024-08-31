#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h> 
#include <sys/types.h>
#include <limits.h>

//binary search algo performed on array of dictionary words
int binarySearch(char* arr[], int low, int high, char* targetWord){
    while (low <=high){
        int mid = (low + high)/2;
        int value = strcmp(targetWord, arr[mid]);
        if(value==0){
            return mid;
        }else if(value<0){
            high = mid - 1;
        }else{
            low = mid + 1;
        }
    }
    return -1;
}

//first perform binary search
//if the perfect match of the word isn't in the dictionary (-1 from binary search), perform linear search with case insentivity
char* findWordInDict(char *target, int size, char* dict[]) {
    int retValFromBinSearch = binarySearch(dict,0,size-1,target);
    if (retValFromBinSearch==-1){
        for (int i = 0; i < size; i++) {
            if (strcasecmp(target, dict[i]) == 0) {
                return dict[i]; 
            }
        }
        return NULL; 
    }else{
        return target;
    }
}

//traverse through target word and see which
//checks if targetword (the word in txt file) is ALL CAPITAL.
int capital(char *targetWord, char *dictWord) { 
    char a[2048];
    int lengthOfTarget = strlen(targetWord);
    char* tw =strncpy(a, targetWord,lengthOfTarget + 1);

    char b[2048];
    int lengthOfDictWord = strlen(dictWord);
    char* dw =strncpy(b, dictWord,lengthOfDictWord + 1);
    
    int value = strlen(dw);
    int arr[value];
    int count = 0;

    for (int i = 0; i < strlen(dw); i++) {
        if ((isupper(tw[i]) != 0)) {
            arr[i] = 0;
        }
        else {
            arr[i] = 1;
        }
    }

    for (int p = 0; p < sizeof(arr)/sizeof(arr[0]); p++) { 
        if (arr[p] == 1) {
            count = 1;
            break;
        }
    }
    return count;
}
//if dictionary word is all lowercase, then it checks if targetword is all lowercase
int lowercase(char *targetWord, char *dictWord) { 
    char a[2048];
    int lengthOfTarget = strlen(targetWord);
    char* tw =strncpy(a, targetWord,lengthOfTarget + 1);

    char b[2048];
    int lengthOfDictWord = strlen(dictWord);
    char* dw =strncpy(b, dictWord,lengthOfDictWord + 1);

    int value = strlen(dw);
    int arr[value];
    int count = 0;

    for (int i = 0; i < strlen(dw); i++) {
        if ((islower(dw[i]) != 0) && (islower(tw[i]) != 0)) {
            arr[i] = 0;
        }
        else {
            arr[i] = 1;            
        }
    }

    for (int p = 0; p < sizeof(arr)/sizeof(arr[0]); p++) { 
        if (arr[p] == 1) {
            count = 1;
            break;
        }
    }
    return count;
}

//considers the case of MacDonald, where we have capital letters in the middle of the word
//checks if target word has capital letters at the same locations that dictionary word does
int caseofMacDonald(char *targetWord, char *dictWord) {
    char a[2048];
    int lengthOfTarget = strlen(targetWord);
    char* tw =strncpy(a, targetWord,lengthOfTarget + 1);

    char b[2048];
    int lengthOfDictWord = strlen(dictWord);
    char* dw =strncpy(b, dictWord,lengthOfDictWord + 1);

    int value = strlen(dw);
    int arr[value];
    int ret = 1;

    for (int i = 0; i < strlen(dw); i++) {
        if (((isupper(dw[i]) != 0) && (isupper(tw[i]) == 0)) || ((islower(dw[i]) != 0) && (islower(tw[i]) == 0))){ 
                arr[i] = 0;    
        }else {
            arr[i] = 1; 
        }
    }

    for (int j = 0; j < (sizeof(arr)/sizeof(arr[0])); j++){
        if (arr[j] == 0) {
            ret = 0;
        }
    }
    return ret;
}

//checks if dictionary word is all lowercase, then the first letter of target word can also be capital, but the rest have to be lowercase.
int initialCapital(char *targetWord, char *dictWord) { 
    char a[2048];
    int lengthOfTarget = strlen(targetWord);
    char* tw =strncpy(a, targetWord,lengthOfTarget + 1);

    char b[2048];
    int lengthOfDictWord = strlen(dictWord);
    char* dw =strncpy(b, dictWord,lengthOfDictWord + 1);

    int value = strlen(tw);
    int ret = 1;
    int arr[value];
    arr[0] = 1;

    for (int i = 1; i < strlen(dw); i++) {
        if((islower(dw[i]) != 0) && (islower(tw[i]) != 0)){
            arr[i] = 1; 
        }else{
            arr[i] = 0;
        }
    }

    for (int k = 0; k < (sizeof(arr)/sizeof(arr[0])); k++){
        if (arr[k] == 0) { 
            ret = 0;
        }
    }
    return ret;
}

//output calls on each of the four functions, and if it returns the appropriate value for each case 0 and 1, respectively, then that means targetword fits the dictionary 
//otherwise it returns NULL
char* output(char* tw, char *dw) {
    if (capital(tw, dw) == 0) {
        return tw;
    }else if (lowercase(tw, dw) == 0){
        return tw;
    }else if ((caseofMacDonald(tw, dw)) == 1){ 
        return tw;
    }else if ((isupper(tw[0]) != 0) && (islower(dw[0]) != 0)){
        if (initialCapital(tw,dw) == 1) {
            return tw;
        }
    }
    return NULL;
}

//removes ',",(,{,[ at the beginning of the word and all punctuation at the end of the word
char* fixWord(char *targetWord) { 
    char fixed[2048]={0};
    char words[strlen(targetWord)+1]; 
        
    for (int i = 0; i < strlen(targetWord)+1; i++){ 
            words[i] = *(targetWord + i); 
    }
    
    //removing and counting the number of specific punctuation marks at the beginning of the word
    int count = 0;
    while (words[0]=='\'' || words[0]=='"'|| words[0]=='(' || words[0]=='[' || words[0]=='{'){
        for (int i = 1; i < strlen(targetWord); i++) { 
            words[i-1] = words[i];
        }
        count++;
    }

    //removing and counting the number of any punctuation marks at the end of the word
    size_t value = strlen(targetWord)-count -1;
    int count2 = 0;
    while (ispunct(words[value])!=0) {
        words[value] = '\0';
        value=value-1; 
        count2++;
    }

    //copy word to return char* instead of char[]
    size_t until = strlen(targetWord) - count -count2+1;
    return strncpy(fixed, words, until + 1);
} 

void spellchecker(char* dictArray[], int dictSize,char* directoryName){
    //open text file
    int curr = open(directoryName, O_RDONLY);
    if(curr<0){
        perror(directoryName);
        exit(EXIT_FAILURE);
    }

    //get file size
    size_t fileSize = lseek(curr, (size_t)0, SEEK_END);
    lseek(curr, 0, SEEK_SET);

    //allocate enough buffer space using file size
    char* buffer = (char*)malloc(fileSize+1);
    if (buffer == NULL) {
        close(curr);
        perror("Error: Can't allocate memory");
    }

    //read text file character by character
    ssize_t bytes = read(curr, buffer, fileSize+1);
    if (bytes != fileSize) {
        close(curr);
        free(buffer);
        perror("Error: Can't read file");
    }
    //null terminate file
    buffer[fileSize]='\0';

    //row represents the line number
    int row = 0;

    //col represents the character number in a line
    int col = 1;
    
    //delimiters we are looking for
    const char lineDelimiters[] = "\n";
    const char wordDelimiters[] = " ";
    const char hyphenWordDelimiters[] = "-";
 
    char* line;
    char* lineSaveptr = NULL;
    char* wordSaveptr = NULL;
    char* hyphenWordSaveptr = NULL;
    
    //separate buffer, line by line
    line = strtok_r(buffer, lineDelimiters, &lineSaveptr);
    while (line != NULL) { 
        //update line count
        row++;     

        //separate line, word by word
        char* word = strtok_r(line, wordDelimiters, &wordSaveptr);
        while(word != NULL){
            //make copy of word to use when printing error
            char copyOfWord[strlen(word)+1];
            memcpy(copyOfWord, word, strlen(word)+1);

            //clean up the word using fixWord() function
            char* sanitizedWord = fixWord(word);

            //check if the word is a hyphenated word
            if(strchr(sanitizedWord,'-')==NULL){
                //see if the word is in the dictionary
                char* dw=findWordInDict(sanitizedWord,dictSize,dictArray);
                if (dw != NULL){
                    //see if word passes all the possible cases for versions of words we accept
                    if(output(sanitizedWord,dw)==NULL){
                        fprintf(stderr, "%s %s%d%s%d%s %s\n",directoryName,"(",row,",", col,"):",copyOfWord);
                    }
                } else {
                        fprintf(stderr, "%s %s%d%s%d%s %s\n",directoryName,"(",row,",", col,"):",copyOfWord);
                }
            
            }else{
                //separate hyphenated word, word part by word part
                char* partOfHyphen = strtok_r(sanitizedWord, hyphenWordDelimiters, &hyphenWordSaveptr);
                while(partOfHyphen!=NULL){
                    //see if the word part is in the dictionary
                    char* dw=findWordInDict(partOfHyphen,dictSize,dictArray);
                    if (dw != NULL) {
                        //see if word part passes all the possible cases for versions of words we accept
                        if(output(partOfHyphen,dw)==NULL){
                            fprintf(stderr, "%s %s%d%s%d%s %s\n",directoryName,"(",row,",", col,"):",copyOfWord);
                            break;
                        }
                    } else {
                            fprintf(stderr, "%s %s%d%s%d%s %s\n",directoryName,"(",row,",", col,"):",copyOfWord);
                            break;
                    }
                    //increment to next part of the hyphenated word
                    partOfHyphen = strtok_r(NULL, hyphenWordDelimiters, &hyphenWordSaveptr);
                }
            }
            //update column number
            col = col + strlen(copyOfWord)+1;

            //increment to next word in the line
            word = strtok_r(NULL, wordDelimiters, &wordSaveptr);
        }
        //increment to next line in the buffer
        line = strtok_r(NULL, lineDelimiters,&lineSaveptr);

        //reset column number to 1 for next line
        col = 1;
    }
    close(curr);
    free(buffer);
}

void traversal(char* dictArray[],int dictSize, char *path) { 
    DIR *dir;
    struct dirent *content; 
    
    struct stat sbuf;
    int r = stat(path, &sbuf);
    
    //check if the path is a regular file or a directory
    if(r != 0||S_ISREG(sbuf.st_mode)){
        //regular file name cannot start with a .
        if(path[0] == '.'){
            return;
        }

        int fd = open(path, O_RDONLY);
        if (fd < 0){
            perror(path);
            exit(EXIT_FAILURE);
        }

        //call spellcheck() even though regular file (not a txt file but a root level file)
        spellchecker(dictArray,dictSize,path);
    }else if(S_ISDIR(sbuf.st_mode)){
        //directory name cannot start with a .
        if(path[0] == '.'){
            return;
        }

        //open directory
        if(!(dir = opendir(path))){ 
            return;
        }

        //read contents of directory
        while((content = readdir(dir)) != NULL){
            //files or directory we traverse through cannot be ., .., or start with a .
            if(strcmp(content->d_name,"." )==0 || strcmp(content->d_name, "..")==0 || content->d_name[0] == '.'){
                continue;
            }

            //is the first thing of contents is a subdirectory or a regular file 
            if(content->d_type == DT_DIR){
                //form absolute path
                strcat(path, "/");
                strcat(path, content->d_name);

                //recursively traverse through subdirectory
                traversal(dictArray, dictSize, path);
            }else if(content->d_type == DT_REG){
                //check if regular file is a txt file
                static const char ext[] = ".txt";
                //check if there is a word to the left of .txt
                if (strlen(content->d_name) > strlen(ext)){
                    //compare extension of file using pointer arithmetic
                    if (strcmp(content->d_name + strlen(content->d_name) - strlen(ext),ext) == 0){
                        //form absolute path
                        char absPath[PATH_MAX] ={0};
                        strcat(absPath, path);
                        strcat(absPath, "/");
                        strcat(absPath, content->d_name);

                        //call spellchecker() on txt file
                        spellchecker(dictArray,dictSize,absPath);
                    }
                }
            }
        }
        closedir(dir);
    }
}

int main(int argc, char **argv){
    //dictionary file is the second command line argument
    char *dictionary = argv[1];
    //open dictionary file
    int dict = open(dictionary, O_RDONLY);
    if (dict < 0){
        perror(dictionary);
        exit(EXIT_FAILURE);
    }

    //get dictionary file size
    size_t fileSize = lseek(dict, (size_t)0, SEEK_END);
    lseek(dict, 0, SEEK_SET);

    //allocate enough buffer space using file size
    char* buffer = (char*)malloc(fileSize+1);
    if (buffer == NULL) {
        close(dict);
        perror("Error: Can't allocate memory");
        return EXIT_FAILURE;
    }

    //read dictionary file
    ssize_t r = read(dict, buffer, fileSize+1);
    if (r != fileSize) {
        close(dict);
        free(buffer);
        perror("Error: Can't read file");
        return EXIT_FAILURE;
    }
    //null terminate file
    buffer[fileSize]='\0';

    //create an array to store words in dictionary so later we can perform binary or linear search on it
    char* words[fileSize+1];
    
    //get dictionary size
    int numWordsInDict = 0;

    //separte buffer, line by line
    char *w = strtok(buffer, "\n");
    while (w != NULL && numWordsInDict < (fileSize + 1)){ 
       words[numWordsInDict] = strdup(w); 
       w = strtok(NULL, "\n");
       numWordsInDict++;
    }   

    //all other command line arguments are files or directories we need to traverse through
    if(argc<2){
        return EXIT_FAILURE;
    }
    for(int i=2;i<argc;i++){
        char a[2048]={0};
        char* fname =strcpy(a, argv[i]);

        //call traversal() to traverse through files/directories
        traversal(words, numWordsInDict, fname);
    }

    close(dict);
    free(buffer);

    for (int i = 0; i < numWordsInDict; i++) { 
       free(words[i]);
    }
    return EXIT_SUCCESS;
}