/*
 * DPRINTF.C: print debug messages, if requested debug level high enough
 *
 * xx-Mar-88  Peter Teuben: created
 * 14-Jun-88  Josh Barnes: moved to seperate source file.
 * 10-sep-90  PJT: routines to set_ and get_ the debug level
 *  8-jul-91  pjt: using VFPRINTF now - gcc should work again
 * 12-oct-91  pjt: added __BORLANDC__ to vfprintf users
 * 25-feb-92  pjt: happy gcc2.0
 *  6-apr-93  pjt: took debug_level back into this routine
 * 21-sep-93  pjt: ANSI
 *  4-mar-96  pjt: format string now a 'const'
 * 20-jun-01  pjt: gcc0, no more non-ansi code
 *
 */

#include <stdinc.h>
#include <stdarg.h>

int debug_level=0;	/* needs to be global; see also getparam.c */


/*
 * DPRINTF: printf-style debugging messages, controlled by debug_level
 *	    as set by the user interface (debug=)
 */

int dprintf(int debug, const string fmt, ...)
{
    va_list ap;
    int nret = 0;

    if (debug <= debug_level) {		/* print this debug message? */
        va_start(ap, fmt);	
#if defined(NEED_DOPRNT)
	_doprnt(fmt, ap, stderr);	/*   use low-level interface */
#else
	nret = vfprintf(stderr, fmt, ap);/* this should be ok on sun for now */
#endif
					/*   may become vprintf in ANSI C */
	fflush(stderr);			/*   drain std error buffer */
        va_end(ap);
    }
    return nret;
}
