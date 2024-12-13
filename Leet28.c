#include <string.h>
int strStr(char* haystack, char* needle) {
    int control = -1;
    for(int i = 0; i < strlen(haystack); i++){
        if(haystack[i] == needle[0]){
            if(control > -1) return control;
            int k = i;
            for(int j = 0; j < strlen(needle); j++){
                control = i;
                if(haystack[k] == needle[j])
                    k++;
                else{
                    control = -1;
                    break;
                }
            }
        }
    }
    return control;
}