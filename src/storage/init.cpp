#include <srv-content/storage.h>
#include <srv-content/connection.h>

namespace Content
{
    Storage::Storage(DBConn* db_conn)
    {
        this->db_conn = db_conn;
    }
}
