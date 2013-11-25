#ifndef RTS_METRICS_H
#define RTS_METRICS_H

#include "rts/rts.h"
#include "rts/uthash.h"

struct metric
{
    const char     *key;
    void           *value;
    const char     *format;
    UT_hash_handle  hh;
};

int rts_add_metric(rts_t *rts, const char *key, const char *format,
                   void *value);

int rts_get_metric(rts_t *rts, const char *key, char *output, size_t size);

#endif
