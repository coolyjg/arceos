#ifndef _SYS_FILE_H
#define _SYS_FILE_H

#define	LOCK_UN	8	/* Unlock.  */

int flock(int __fd, int __operation);

/* Can be OR'd in to one of the above.  */
#define	LOCK_NB	4	/* Don't block when locking.  */


#endif