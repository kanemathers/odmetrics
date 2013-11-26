#ifndef ODM_METRICS_H
#define ODM_METRICS_H

#include "odmetrics/odm.h"
#include "odmetrics/uthash.h"

struct metric
{
    const char     *key;
    int            *value;
    UT_hash_handle  hh;
};

int odm_metrics_add(odm_t *odm, const char *key, int *value);

void odm_metrics_free(odm_t *odm);

void odm_metrics_print(odm_t *odm);
char *odm_metrics_json(odm_t *odm);

#endif
