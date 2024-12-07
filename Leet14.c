#include <string.h>
char* longestCommonPrefix(char** strs, int strsSize) {
    for (int i = 1; i < strsSize; i++){
        for (int j = 0; j < strlen(*strs); j++){
            if (strs[0][j] != strs[i][j]){
                strs[0][j] = '\0';
                break;
            }
        }
    }
    return strs[0];
}