

#ifndef COMMON_H__
#define COMMON_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <string>
#include "global.h"
#include "reactor.h"

extern bool IsValidHandle(handle_t handle)
{
	return handle >= 0;
}

extern void ReportSocketError(const char * msg)
{
    fprintf(stderr, "%s error: %s\n", msg, strerror(errno));
}
#endif
