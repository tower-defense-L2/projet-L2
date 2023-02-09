#include "../include/test_macro_compil_2.h"

void test_macro_compil_2(void){
    #ifdef _LINUX_
    printf("linux");
#else
#ifdef _WINDOWS_
    printf("windows");
#else
    printf("other");
#endif
#endif
}
