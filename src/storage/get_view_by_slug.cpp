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

        auto result = txn.exec(query);

        auto row = result.begin();

        if (row == result.end()) {
            return nullptr;
        }

        auto column = row.begin();

        auto view = new Content::Model::View;

        view->id = column.as<int>();

        column++;
        if (!column.is_null()) {
            const char* srcSlug = column.c_str();
            view->slug = new char[strlen(srcSlug) + 1];
            memset(view->slug, 0, (strlen(srcSlug) + 1) * sizeof(char));
            memcpy(view->slug, srcSlug, strlen(srcSlug));
        }

        column++;
        if (!column.is_null()) {
            view->contentId = new int;
            *view->contentId = column.as<int>();
        }

        column++;
        if (!column.is_null()) {
            const char* srcTitle = column.c_str();
            view->title = new char[strlen(srcTitle) + 1];
            memset(view->title, 0, (strlen(srcTitle) + 1) * sizeof(char));
            memcpy(view->title, srcTitle, strlen(srcTitle));
        }

        column++;
        if (!column.is_null()) {
            const char* strText = column.c_str();
            view->text = new char[strlen(strText) + 1];
            memset(view->text, 0, (strlen(strText) + 1) * sizeof(char));
            memcpy(view->text, strText, strlen(strText));
        }

        return view;
    }
}
