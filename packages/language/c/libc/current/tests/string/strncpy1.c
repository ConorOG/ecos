//=================================================================
//
//        strncpy1.c
//
//        Testcase for C library strncpy()
//
//=================================================================
//####COPYRIGHTBEGIN####
//                                                                          
// -------------------------------------------                              
// The contents of this file are subject to the Red Hat eCos Public License 
// Version 1.0 (the "License"); you may not use this file except in         
// compliance with the License.  You may obtain a copy of the License at    
// http://sourceware.cygnus.com/ecos                                        
//                                                                          
// Software distributed under the License is distributed on an       
// basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See the 
// License for the specific language governing rights and limitations under 
// the License.                                                             
//                                                                          
// The Original Code is eCos - Embedded Configurable Operating System,      
// released September 30, 1998.                                             
//                                                                          
// The Initial Developer of the Original Code is Red Hat.                   
// Portions created by Red Hat are                                          
// Copyright (C) 1998, 1999, 2000 Red Hat, Inc.                             
// All Rights Reserved.                                                     
// -------------------------------------------                              
//                                                                          
//####COPYRIGHTEND####
//=================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):     ctarpy, jlarmour
// Contributors:  jlarmour
// Date:          1998/6/3
// Description:   Contains testcode for C library strncpy() function
//
//
//####DESCRIPTIONEND####

// Declarations for test system:
//
// TESTCASE_TYPE=CYG_TEST_MODULE
// COMPOUND_TESTCASE


// CONFIGURATION

#include <pkgconf/libc.h>   // Configuration header

// INCLUDES

#include <string.h>
#include <cyg/infra/testcase.h>
#include <sys/cstartup.h>          // C library initialisation


// FUNCTIONS


externC void
cyg_package_start( void )
{
#ifdef CYGPKG_LIBC
    cyg_iso_c_start();
#else
    (void)main(0, NULL);
#endif
} // cyg_package_start()



// Functions to avoid having to use libc strings

#ifdef CYGPKG_LIBC
static int my_strlen(const char *s)
{
    const char *ptr;

    ptr = s;
    for ( ptr=s ; *ptr != '\0' ; ptr++ )
        ;

    return (int)(ptr-s);
} // my_strlen()


static int my_strncmp(const char *s1, const char *s2, size_t n)
{
    if (n==0)
        return 0;
    
    while (n-- != 0 && *s1 == *s2)
    {
        if (n == 0 || *s1 == '\0' || *s2 == '\0')
            break;
        s1++;
        s2++;
    }
    
    return (*s1 - *s2);
} // my_strncmp()


static int my_strcmp(const char *s1, const char *s2)
{
    for ( ; *s1 == *s2 ; s1++,s2++ )
    {
        if ( *s1 == '\0' )
            break;
    } // for

    return (*s1 - *s2);
} // my_strcmp()


static char *my_strcpy(char *s1, const char *s2)
{
    while (*s2 != '\0') {
        *(s1++) = *(s2++);
    }
    *s1 = '\0';

    return s1; 
} // my_strcpy()
#endif // ifdef CYGPKG_LIBC


int
main( int argc, char *argv[] )
{
#ifdef CYGPKG_LIBC
    char x[300];
    char y[300];
    char *ret;
#endif

    CYG_TEST_INIT();

    CYG_TEST_INFO("Starting tests from testcase " __FILE__ " for C library "
                  "strncpy() function");
    CYG_TEST_INFO("This testcase provides simple basic tests");

#ifdef CYGPKG_LIBC

    // Check 1
    my_strcpy(x, "Nine rings for men doomed to die");
    ret = strncpy(y, "Nine rings for men doomed to die", my_strlen(x));
    CYG_TEST_PASS_FAIL( (my_strncmp(x, y, my_strlen(x)) == 0),
                        "Simple copy" );
    // Check return value
    CYG_TEST_PASS_FAIL( (y == ret), "Simple copy return value" );


    // Check 2
    my_strcpy(x, "");
    my_strcpy(y, "Seven rings for the dwarves in their halls of stone");
    ret = strncpy(y, x, 1);
    CYG_TEST_PASS_FAIL( (my_strcmp(y, "") == 0), "Copy empty string" );
    // Check return value
    CYG_TEST_PASS_FAIL( (y == ret), "Copy empty string return value" );

    // Check 3
    my_strcpy(x, "");
    my_strcpy(y, "Seven rings for the dwarves in their halls of stone");
    ret = strncpy(y, x, 0);
    if (my_strcmp(y, "Seven rings for the dwarves "
                     "in their halls of stone") == 0)
        CYG_TEST_PASS("Copy 0 characters");
    else
        CYG_TEST_FAIL("Copy 0 characters");
    // Check return value
    CYG_TEST_PASS_FAIL( (y == ret), "Copy empty string return value" );


#else // ifndef CYGPKG_LIBC
    CYG_TEST_NA("Testing is not applicable to this configuration");
#endif // ifndef CYGPKG_LIBC

    CYG_TEST_FINISH("Finished tests from testcase " __FILE__ " for C library "
                    "strncpy() function");

} // main()

// EOF strncpy1.c
