#include "../include/test_macro_compil_2.h"

int main(){
    printf("test macro compil\n");

    printf("test dans le main:\n");
    #ifdef _LINUX_
        printf("linux");
    #else
    #ifdef _WINDOWS_
        printf("windows");
    #else
        printf("other");
    #endif
    #endif
    printf("\n test dans un autre fichier:\n");
    test_macro_compil_2();
    printf("\n fin du test\n");
    return 0;
}