#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rts/rts.h"
#include "rts/metrics.h"
#include "rts/server.h"

/* test */
#include <unistd.h>

int rts_init(rts_t *rts)
{
    memset(rts, 0, sizeof *rts);

    rts->metrics = NULL;

    return 0;
}

void rts_destroy(rts_t *rts)
{
}

int main()
{
    rts_t rts;
    int   test = 10;
    char  output[10];
    int   i;

    rts_init(&rts);

    rts_add_metric(&rts, "test", "%d", &test);
    rts_get_metric(&rts, "test", output, sizeof output);

    rts_serve(&rts, "127.0.0.1", "8000");

    for (i = 0; i < 10; i++)
        sleep(1);

    rts_destroy(&rts);

    return 0;
}
