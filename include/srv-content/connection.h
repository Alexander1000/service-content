#ifndef SRV_CONTENT_CONNECTION_H
#define SRV_CONTENT_CONNECTION_H

#include <pqxx/pqxx>

namespace Content
{
    class DBConn {
    public:
        DBConn(const char* host, int port, const char* db_user, const char* db_password, const char* db_name);
        pqxx::connection* get_conn();
    private:
        char* host;
        int port;
        char* db_user;
        char* db_password;
        char* db_name;
    };
}

#endif
