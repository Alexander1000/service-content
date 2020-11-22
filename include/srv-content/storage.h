#ifndef SRV_CONTENT_STORAGE_H
#define SRV_CONTENT_STORAGE_H

#include <srv-content/connection.h>

namespace Content {
    class Storage {
    public:
        explicit Storage(DBConn* db_conn);
        int save_content(int* content_id, char* title, char* text, int user_id);
        bool save_page(const int* pageId, const char* slug, const int* contentId);

    private:
        DBConn* db_conn;
    };
}

#endif
