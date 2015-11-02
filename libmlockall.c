#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>



#ifndef MAX_UID
#define MAX_UID 999
#endif
#ifndef LIB_NAME
#define LIB_NAME "libmlockall.so"
#endif
#ifndef LIB_VER
#define LIB_VER ".0.0"
#endif



void __attribute__((constructor)) init() {
   if (getuid () <= MAX_UID) {
      if (mlockall (MCL_CURRENT|MCL_FUTURE) ) {
         perror ("mlockall");
      } else {
         //printf ("memory locked\n");

         // Append library to LD_PRELOAD
         char   *library    = LIB_NAME LIB_VER ":";
         size_t  llen       = strnlen (library, 255);
         size_t  olen       = 0;
         char   *preload    = NULL;
         char   *oldPreload = getenv ("LD_PRELOAD");


         if (oldPreload) {   // getenv returns a NULL pointer and strnlen/strncpy cannot handle it
            olen = strnlen (oldPreload, 10000);

            if (strstr (oldPreload, LIB_NAME) ) return;   // Check if library is allready a part of LD_PRELOAD
         }

         preload = (char*)malloc (olen + llen + 1);   //TODO check memory

         strncpy (preload, library, llen);

         if (oldPreload) {
            strncpy (&(preload[llen]), oldPreload, olen);
         }

         preload[llen + olen] = 0;

         printf ("preload: %s\n", preload);

         setenv ("LD_PRELOAD", preload, 1);

         free (preload);
      }
   } //else { printf ("getuid above %i\n", MAX_UID); }
}
