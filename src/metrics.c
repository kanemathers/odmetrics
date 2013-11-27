#include <stdlib.h>
#include <stdio.h>

#include <jansson.h>

#include "odmetrics/odm.h"
#include "odmetrics/metrics.h"
#include "odmetrics/uthash.h"

int odm_metrics_add(odm_t *odm, const char *key, int *value)
{
    struct metric *metric;

    HASH_FIND(hh, odm->metrics, key, strlen(key), metric);

    if (!metric)
    {
        metric = malloc(sizeof *metric);

        if (!metric)
            return -1;

        metric->key   = key;
        metric->value = value;

        HASH_ADD_KEYPTR(hh, odm->metrics, key, strlen(key), metric);
    }
    else
    {
        metric->value = value;
    }

    return 0;
}

void odm_metrics_free(odm_t *odm)
{
    struct metric *metric;
    struct metric *tmp;

    HASH_ITER(hh, odm->metrics, metric, tmp)
    {
        HASH_DEL(odm->metrics, metric);
        free(metric);
    }
}

void odm_metrics_print(odm_t *odm)
{
    struct metric *metric;

    for (metric = odm->metrics; metric != NULL; metric = metric->hh.next)
        printf("%s: %d\n", metric->key, *metric->value);

    printf("\n");
}

char *odm_metrics_json(odm_t *odm)
{
    json_t        *j_metrics = json_object();
    struct metric *metric;
    char          *dumped;

    for (metric = odm->metrics; metric != NULL; metric = metric->hh.next)
        json_object_set_new(j_metrics, metric->key,
                            json_integer(*metric->value));

    dumped = json_dumps(j_metrics, JSON_INDENT(4));

    json_decref(j_metrics);

    return dumped;
}
