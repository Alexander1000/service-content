#include <srv-content/storage.h>
#include <srv-content/connection.h>

namespace Content
{
    Storage::Storage(DBConn* db_conn)
    {
        this->db_conn = db_conn;
    }

    void Storage::save_content(int *content_id, char *title, char *text, int user_id)
    {
        // do save
    }
}
