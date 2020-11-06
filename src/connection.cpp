#include <srv-content/connection.h>
#include <pqxx/pqxx>

namespace Content
{
    DBConn::DBConn(std::string host, int port, std::string db_user, std::string* db_password, std::string db_name)
    {
        this->host = host;
        this->port = port;
        this->db_user = db_user;
        this->db_password = db_password;
        this->db_name = db_name;

        this->conn = nullptr;
    }

    pqxx::connection* DBConn::get_conn()
    {
        if (this->conn == nullptr) {
            char *conn_str = new char[128];
            memset(conn_str, 0, sizeof(char) * 128);
            if (this->db_password == nullptr) {
                sprintf(
                    conn_str,
                    "postgres://%s@%s:%d/%s",
                    this->db_user.c_str(),
                    this->host.c_str(),
                    this->port,
                    this->db_name.c_str()
                );
            } else {
                sprintf(
                    conn_str,
                    "postgres://%s:%s@%s:%d/%s",
                    this->db_user.c_str(),
                    this->db_password->c_str(),
                    this->host.c_str(),
                    this->port,
                    this->db_name.c_str()
                );
            }
            this->conn = new pqxx::connection(conn_str);
        }

        return this->conn;
    }
}
