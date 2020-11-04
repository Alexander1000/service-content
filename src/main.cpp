#include <evhttp.h>

int main() {
    event_base* serv_base = (event_base*) event_init();

    evhttp * http_server = evhttp_new(serv_base);

    // evhttp_accept_socket(http_server, server_sock);

    return 0;
}
