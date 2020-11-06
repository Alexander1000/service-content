#include <srv-content/connection.h>
#include <pqxx/pqxx>

namespace Content
{
    DBConn::DBConn(const char *host, int port, const char *db_user, const char *db_password, const char *db_name)
    {
        this->host = (char*) host;
        this->port = port;
        this->db_user = (char*) db_user;
        this->db_password = (char*) db_password;
        this->db_name = (char*) db_name;
    }

    pqxx::connection* DBConn::get_conn()
    {
        char* conn_str = new char[128];
        memset(conn_str, 0, sizeof(char) * 128);
        sprintf(conn_str, "postgres://%s@%s:%d/%s", this->db_user, this->host, this->port, this->db_name);
        return new pqxx::connection(conn_str);
    }
}
