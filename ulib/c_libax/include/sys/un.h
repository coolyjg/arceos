#ifndef __SYS_UN__
#define __SYS_UN__

#include "netinet/in.h"

struct sockaddr_un
  {
    __SOCKADDR_COMMON (sun_);
    char sun_path[108];		/* Path name.  */
  };

#endif