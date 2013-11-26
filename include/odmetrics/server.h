/**
 * @file server.h
 */

#ifndef ODM_SERVER_H
#define ODM_SERVER_H

#include "odmetrics/odm.h"

/**
 * Start the odmetrics server.
 *
 * When a client connects to the server, odmetrics will return the JSON
 * encoded metrics and then disconnect.
 *
 * @param hostname Hostname to bind the server to.
 * @param port Port number to bind the server to.
 *
 * @return Returns 0 on success and -1 on failure.
 */
int odm_serve(odm_t *odm, const char *hostname, const char *port);

#endif
