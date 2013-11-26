#include <stdlib.h>

#include "rts/rts.h"
#include "rts/metrics.h"

int rts_metrics_add(rts_t *rts, const char *key, int *value)
{
    struct metric *metric;

    HASH_FIND(hh, rts->metrics, key, strlen(key), metric);

    if (!metric)
    {
        metric = malloc(sizeof *metric);

        if (!metric)
            return -1;

        metric->key   = key;
        metric->value = value;

        HASH_ADD_KEYPTR(hh, rts->metrics, key, strlen(key), metric);
    }
    else
    {
        metric->value = value;
    }

    return 0;
}
