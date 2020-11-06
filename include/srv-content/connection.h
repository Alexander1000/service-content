#ifndef SRV_CONTENT_CONNECTION_H
#define SRV_CONTENT_CONNECTION_H

#include <pqxx/pqxx>

namespace Content
{
    class DBConn {
    public:
        DBConn(const char* host, int port, const char* db_user, const char* db_password, const char* db_name);
        pqxx::connection* conn;
    };
}

#endif
