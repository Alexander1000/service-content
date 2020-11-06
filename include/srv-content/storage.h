#ifndef SRV_CONTENT_STORAGE_H
#define SRV_CONTENT_STORAGE_H

#include <srv-content/connection.h>

namespace Content {
    class Storage {
    public:
        Storage(DBConn* db_conn);
        void save_content(int* content_id, char* title, char* text, int user_id);

    private:
        DBConn* db_conn;
    };
}

#endif
