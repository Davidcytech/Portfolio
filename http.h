#ifndef HTTP_H
#define HTTP_H

struct HttpRequest
{
    char method[16];
    char path[256];
    char version[16];
};

int parse_request(const char *buffer, struct HttpRequest *request);

#endif