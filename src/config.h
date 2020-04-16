#pragma once

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdbool.h>
#include <stdint.h>

#define ENGLISH_LANGUAGE
#include <english.h>

#define PRINTL(a)wprintf(L"%ls",a);
#define PRINTL_S(a,b)wprintf(L"%ls %ls\n", a, b);
#define PRINTL_ASCII(a,b){wprintf(L"%ls", a);printf("%s\n", b);}
#define PRINTL_UINT32(a,b){wprintf(L"%ls", a);printf("%u\n", b);}
#define PRINT_LOG_INDEX(a,b,c,d){wprintf(a, b, c, d);}
#define PRINT_DATA(a,b,c){wprintf(DATAONBEGIN, a);for(int i=0;i<b;i++)\
{unsigned char* byte = (unsigned char*)c;printf("%x (%d) - ", byte[i], byte[i]);}\
wprintf(DATAONEND);}

#define PRINT(a)printf("%s",a);
#define PRINT_S(a,b)printf("%s %s\n", a, b);



