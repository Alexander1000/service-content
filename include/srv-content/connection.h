#ifndef SRV_CONTENT_CONNECTION_H
#define SRV_CONTENT_CONNECTION_H

#include <pqxx/pqxx>
#include <string>

namespace Content
{
    class DBConn {
    public:
        DBConn(std::string host, int port, std::string db_user, std::string* db_password, std::string db_name);
        pqxx::connection* get_conn();
    private:
        std::string host;
        int port;
        std::string db_user;
        std::string* db_password;
        std::string db_name;

        pqxx::connection* conn;
    };
}

#endif
