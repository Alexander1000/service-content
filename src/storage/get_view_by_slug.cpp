#include <pqxx/pqxx>
#include <srv-content.h>

namespace Content
{
    Content::Model::View* Storage::get_view_by_slug(const char *slug)
    {
        pqxx::connection* conn = this->db_conn->get_conn();
        pqxx::work txn{*conn};

        char* query = new char[1024];
        memset(query, 0, sizeof(char) * 1024);

        sprintf(
            query,
            "select p.id, p.slug, p.content_id, cv.title, cv.text "
            "from pages p "
            "left join content c on p.content_id = c.id "
            "left join content_versions cv on cv.content_id = c.id and cv.version = c.version "
            "where slug = %s",
            txn.quote(slug).c_str()
        );

        pqxx::row row = txn.exec1(query);

        return nullptr;
    }
}
