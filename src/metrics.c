#include <stdlib.h>

#include "rts/metrics.h"

#include <stdio.h>

struct metric *metrics = NULL;

int rts_add_metric(const char *key, int *value)
{
    struct metric *metric;

    HASH_FIND(hh, metrics, key, strlen(key), metric);

    if (!metric)
    {
        metric = malloc(sizeof *metric);

        if (!metric)
            return -1;

        metric->key   = key;
        metric->value = value;

        HASH_ADD_KEYPTR(hh, metrics, key, strlen(key), metric);
    }
    else
    {
        metric->value = value;
    }

    return 0;
}
