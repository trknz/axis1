#ifndef __COMMONCHEADERFILE
#define __COMMONCHEADERFILE

/* need to resolve, but we cannot include stdlib.h when running
 * calculatordoc tests because div() is already defined. So we
 * hard-code the malloc prototype.
 */

#include <stdio.h>

#define C_BOOL  int
#define C_FALSE (int)0
#define C_TRUE  (int)1 

extern void *malloc(unsigned int);
char *c_strdup(char *s)
{
    char * ret = (char *)malloc(strlen(s)+1);
    strcpy(ret, s);
    return ret;
}

#ifdef WIN32
      #define LONGLONGVALUE(value) value##I64
      #define UNSIGNED_LONGLONGVALUE(value) value##UI64
#else
      #define LONGLONGVALUE(value) value##LL
      #define UNSIGNED_LONGLONGVALUE(value) value##ULL
#endif

// ==========================================================
// Following code is to take care of ebcdic/ascii issues.
// Some test cases relating to hex and binary and attachement
// send text strings. In order for these test cases to 
// pass we need to ensure that the data is in ascii. 
// In addition, if we are going to print out the data to cout,
// then we need to convert to ebcdic. For ascii-based systems,
// the macros used to do the conversions are identity macros. 
// ==========================================================
#ifdef __OS400__

/* conversion table generated by ebcdic 37 -> ascii 819 */
const char EBCDICtoASCII[256] = {
/* 0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F */
   0,   1,   2,   3, 156,   9, 134, 127, 151, 141, 142,  11,  12,  13,  14,  15,    
  16,  17,  18,  19, 157, 133,   8, 135,  24,  25, 146, 143,  28,  29,  30,  31,    
 128, 129, 130, 131, 132,  10,  23,  27, 136, 137, 138, 139, 140,   5,   6,   7,    
 144, 145,  22, 147, 148, 149, 150,   4, 152, 153, 154, 155,  20,  21, 158,  26,    
  32, 160, 226, 228, 224, 225, 227, 229, 231, 241, 162,  46,  60,  40,  43, 124,    
  38, 233, 234, 235, 232, 237, 238, 239, 236, 223,  33,  36,  42,  41,  59, 172,    
  45,  47, 194, 196, 192, 193, 195, 197, 199, 209, 166,  44,  37,  95,  62,  63,    
  248, 201, 202, 203, 200, 205, 206, 207, 204,  96,  58,  35,  64,  39,  61,  34,   
  216,  97,  98,  99, 100, 101, 102, 103, 104, 105, 171, 187, 240, 253, 254, 177,   
  176, 106, 107, 108, 109, 110, 111, 112, 113, 114, 170, 186, 230, 184, 198, 164,   
  181, 126, 115, 116, 117, 118, 119, 120, 121, 122, 161, 191, 208, 221, 222, 174,   
   94, 163, 165, 183, 169, 167, 182, 188, 189, 190,  91,  93, 175, 168, 180, 215,   
  123,  65,  66,  67,  68,  69,  70,  71,  72,  73, 173, 244, 246, 242, 243, 245,   
  125,  74,  75,  76,  77,  78,  79,  80,  81,  82, 185, 251, 252, 249, 250, 255,   
   92, 247,  83,  84,  85,  86,  87,  88,  89,  90, 178, 212, 214, 210, 211, 213,   
   48,  49,  50,  51,  52,  53,  54,  55,  56,  57, 179, 219, 220, 217, 218, 159
};
 
/* conversion table generated by ascii 819 -> ebcdic 37 */
const char ASCIItoEBCDIC[256] = {
/* 0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F */
   0,   1,   2,   3,  55,  45,  46,  47,  22,   5,  37,  11,  12,  13,  14,  15,      
  16,  17,  18,  19,  60,  61,  50,  38,  24,  25,  63,  39,  28,  29,  30,  31,
  64,  90, 127, 123,  91, 108,  80, 125,  77,  93,  92,  78, 107,  96,  75,  97,
 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 122,  94,  76, 126, 110, 111,
 124, 193, 194, 195, 196, 197, 198, 199, 200, 201, 209, 210, 211, 212, 213, 214,
 215, 216, 217, 226, 227, 228, 229, 230, 231, 232, 233, 186, 224, 187, 176, 109,      
 121, 129, 130, 131, 132, 133, 134, 135, 136, 137, 145, 146, 147, 148, 149, 150,
 151, 152, 153, 162, 163, 164, 165, 166, 167, 168, 169, 192,  79, 208, 161,   7,
  32,  33,  34,  35,  36,  21,   6,  23,  40,  41,  42,  43,  44,   9,  10,  27,      
  48,  49,  26,  51,  52,  53,  54,   8,  56,  57,  58,  59,   4,  20,  62, 255,      
  65, 170,  74, 177, 159, 178, 106, 181, 189, 180, 154, 138,  95, 202, 175, 188,      
 144, 143, 234, 250, 190, 160, 182, 179, 157, 218, 155, 139, 183, 184, 185, 171,      
 100, 101,  98, 102,  99, 103, 158, 104, 116, 113, 114, 115, 120, 117, 118, 119,      
 172, 105, 237, 238, 235, 239, 236, 191, 128, 253, 254, 251, 252, 173, 174,  89,      
  68,  69,  66,  70,  67,  71, 156,  72,  84,  81,  82,  83,  88,  85,  86,  87,      
 140,  73, 205, 206, 203, 207, 204, 225, 112, 221, 222, 219, 220, 141, 142, 223   
};

static char* stringToAscii( char *string )
{
   char* pch = string;
   if( string == NULL ) return NULL;
 
   /* while not EOL... */
   while( *pch != (char)0 )
   {
         *pch = EBCDICtoASCII[*pch];
         pch++;
   }
   return string;
}

static char* asciiToString( char *string )
{
   char* pch = string;
   if( string == NULL ) return NULL;
 
   /* while not EOL... */
   while( *pch != (char)0 )
   {
         *pch = ASCIItoEBCDIC[*pch];
         pch++;
   }
   return string;
}

static char * asciiToStringOfLength( char * pString, int iLength)
{
   int iCount = 0;
   char * pch = pString;

   if( pString == NULL)
       return NULL;
 
   /* while not EOL... */
   while( *pch != '\0' && iCount < iLength)
   {
         *pch = ASCIItoEBCDIC[*pch];
         pch++;
         iCount++;
   }

   *pch = '\0';
   return pString;
}

#else

#define asciiToString( x ) ( x )
#define stringToAscii( x ) ( x )

char * asciiToStringOfLength( char * pString, int iLength)
{
   if( pString == NULL)
       return NULL;
 
   pString[iLength] = '\0';
   return pString;
}

#endif

static C_BOOL exceptionOccurred = C_FALSE;
void exceptionHandler(int errorCode, const char *errorString, void *pSoapFault, void *pSoapFaultDetail)
{
    exceptionOccurred = C_TRUE;    
    printf("AxisException : %s\n", errorString);
}

#endif