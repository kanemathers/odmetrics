#include <stdlib.h>

#include "rts/rts.h"
#include "rts/metrics.h"
#include "rts/uthash.h"

struct metric *metrics = NULL;

int rts_add_metric(rts_t *rts, const char *key, const char *format,
                   void *value)
{

    return 0;
}

int rts_get_metric(rts_t *rts, const char *key, char *output, size_t size)
{
    return 0;
}

