#include <pqxx/pqxx>
#include <srv-content/storage.h>
#include <srv-content/connection.h>
#include <iostream>

namespace Content
{
    Storage::Storage(DBConn* db_conn)
    {
        this->db_conn = db_conn;
    }

    void Storage::save_content(int* content_id, char *title, char *text, int user_id)
    {
        pqxx::connection* conn = this->db_conn->get_conn();
        pqxx::work txn{*conn};

        if (content_id == nullptr) {
            // create new content
            content_id = new int;

            pqxx::row row = txn.exec1("insert into content(version) values(0) returning id");

            for (auto column = row.begin(); column != row.end(); column++) {
                *content_id = column.as<int>();
                break;
            }
        }

        txn.commit();
    }
}
