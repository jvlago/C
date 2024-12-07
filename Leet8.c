#include <string.h>
#include <climits>
int myAtoi(char* s) {
    int sinal = 1, soma = 0, cmc = 0, dout = 0;
    for(int i = 0;i<strlen(s);i++){
        if(s[i]==' '){
            if (cmc != 0) break;
        }
        else if(s[i]=='+' || s[i]=='-'){
            if(cmc != 0) break;
            else if(s[i]=='-') sinal = -1;
            cmc = 1;
            dout++;
        }
        else if(s[i] < '0' || s[i] > '9' || dout >=2) break;
        else
        {
            if(soma > (INT_MAX / 10)  || (soma == (INT_MAX / 10) && (s[i]-'0') > 7))
            return sinal == -1 ? INT_MIN : INT_MAX;
            soma = soma * 10 + (s[i]-'0');
            cmc = 1;
        }
    }
    return soma*sinal;
}