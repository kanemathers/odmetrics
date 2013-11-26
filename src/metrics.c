#include <stdlib.h>
#include <stdio.h>

#include <jansson.h>

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

void rts_metrics_print(rts_t *rts)
{
    struct metric *metric;

    for (metric = rts->metrics; metric != NULL; metric = metric->hh.next)
        printf("%s: %d\n", metric->key, *metric->value);

    printf("\n");
}

char *rts_metrics_json(rts_t *rts)
{
    json_t        *j_metrics = json_object();
    struct metric *metric;
    char          *dumped;

    for (metric = rts->metrics; metric != NULL; metric = metric->hh.next)
        json_object_set_new(j_metrics, metric->key,
                            json_integer(*metric->value));

    dumped = json_dumps(j_metrics, JSON_INDENT(4));

    json_decref(j_metrics);

    return dumped;
}
