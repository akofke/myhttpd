#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

struct stat *get_stat(char *path) {
    /*
     * allocate memory for the stat buffer since we will be storing the pointer
     * to it in the http request struct
     */
    struct stat *stat_buf = malloc(sizeof(struct stat));

    stat(path, stat_buf);

    return stat;
}

char *expand_path(char *req_path) {
    /*
     * expand exact matches of "~/" at the beginning of the path according to the
     * project specification.
     * e.g. ~/index.html to /home/<user>/myhttpd/
     */

    // not the prettiest way to do this
    if(req_path[0] != '~' || req_path[1] != '/') {
        return req_path;
    }

    char *expanded = getenv("HOME");
    strcat(expanded, "/myhttpd/");

    /*
     * concat from the third char onwards, i.e. ~/index.html
     *                                            ^
     */
    strcat(expanded, &req_path[2]);
    return expanded;
}
