#ifndef ODM_SERVER_H
#define ODM_SERVER_H

#include "odmetrics/odm.h"

int odm_serve(odm_t *odm, const char *hostname, const char *port);

#endif
