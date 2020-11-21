#include <iostream>
#include <srv-content.h>

namespace Content
{
    bool Storage::save_page(int *pageId, char *slug, int *contentId) {
        pqxx::connection* conn = this->db_conn->get_conn();
        pqxx::work txn{*conn};

        if (contentId == nullptr) {
            return false;
        }

        if (pageId == nullptr && slug == nullptr) {
            return false;
        }

        char* query = new char[1024];
        memset(query, 0, sizeof(char) * 1024);

        if (pageId != nullptr) {
            sprintf(
                query,
                "update pages set slug = %s, content_id = %d where id = %d",
                slug != nullptr ? txn.quote(slug).c_str() : "NULL",
                *contentId,
                *pageId
            );
            txn.exec(query);
        } else {
            sprintf(
                query,
                "insert into pages(content_id, slug, created_at) values(%d, %s, now())",
                *contentId,
                txn.quote(slug).c_str()
            );
            txn.exec(query);
        }

        txn.commit();

        return true;
    }
}
