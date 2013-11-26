#ifndef RTS_METRICS_H
#define RTS_METRICS_H

#include "rts/rts.h"
#include "rts/uthash.h"

struct metric
{
    const char     *key;
    int            *value;
    UT_hash_handle  hh;
};

int rts_metrics_add(rts_t *rts, const char *key, int *value);

void rts_metrics_free(rts_t *rts);

void rts_metrics_print(rts_t *rts);
char *rts_metrics_json(rts_t *rts);

#endif
