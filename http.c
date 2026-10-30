#include <stdio.h>
#include <string.h>

#include "http.h"

int parse_request(const char *buffer, struct HttpRequest *request)
{
    char *first_space = strchr(buffer, ' ');

    if (first_space == NULL)
    {
        return -1;
    }

    size_t method_length = first_space - buffer;

    if (method_length >= sizeof(request->method))
    {
        return -1;
    }

    memcpy(request->method, buffer, method_length);
    request->method[method_length] = '\0';

    char *path_start = first_space + 1;

    char *second_space = strchr(path_start, ' ');

    if (second_space == NULL)
    {
        return -1;
    }

    size_t path_length = second_space - path_start;

    if (path_length >= sizeof(request->path))
    {
        return -1;
    }

    memcpy(request->path, path_start, path_length);
    request->path[path_length] = '\0';

    char *version_start = second_space + 1;

    char *version_end = strchr(version_start, '\r');

    if (version_end == NULL)
    {
        return -1;
    }

    size_t version_length = version_end - version_start;

    if (version_length >= sizeof(request->version))
    {
        return -1;
    }

    memcpy(request->version, version_start, version_length);
    request->version[version_length] = '\0';

    return 0;
}