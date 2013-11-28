#include <stdlib.h>
#include <stdio.h>

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

char *odm_metrics_serialize(odm_t *odm)
{
    int            len = 0;
    char          *p;
    struct metric *metric;
    char          *output;

    for (metric = odm->metrics; metric != NULL; metric = metric->hh.next)
        len += snprintf(NULL, 0, "%s\t%d\n", metric->key, *metric->value);

    output = malloc(sizeof len);
    len    = 0;

    if (!output)
        return NULL;

    p = output;

    for (metric = odm->metrics; metric != NULL; metric = metric->hh.next)
    {
        len += sprintf(p, "%s\t%d\n", metric->key, *metric->value);
        p   += len;
    }

    return output;
}
