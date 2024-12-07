#include <string.h>
int romanToInt(char* s) {
    int soma = 0, controle = 1, num;
    for(int i=strlen(s)-1;i>=0;i--){
        if(s[i]=='I')
            num = 1;
        else if(s[i]=='V')
            num = 5;
        else if(s[i]=='X')
            num = 10;
        else if(s[i]=='L')
            num = 50;
        else if(s[i]=='C')
            num = 100;
        else if(s[i]=='D')
            num = 500;
        else if(s[i]=='M')
            num = 1000;
        else return 0;
        if(num<controle)
            soma-=num;
        else
            soma+=num;
        controle = num;
    }
    return soma;
}