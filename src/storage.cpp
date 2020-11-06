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

    void Storage::save_content(int* content_id, char* title, char* text, int user_id)
    {
        pqxx::connection* conn = this->db_conn->get_conn();
        pqxx::work txn{*conn};

        int version = 0;

        if (content_id == nullptr) {
            // create new content
            content_id = new int;

            pqxx::row row = txn.exec1("insert into content(version) values(0) returning id");

            auto column = row.begin();
            *content_id = column.as<int>();
        } else {
            char* query = new char[128];
            memset(query, 0, sizeof(char) * 128);
            sprintf(query, "select version from content where id = %d", *content_id);
            pqxx::row r = txn.exec1(query);
            auto column = r.begin();
            version = column.as<int>(); // current version
            version++; // new version
        }

        char* query = new char[1024];
        memset(query, 0, sizeof(char) * 1024);
        sprintf(
            query,
            "insert into content_versions(content_id, title, text, user_id, version) values (%d, %s, %s, %d, %d)",
            *content_id,
            txn.quote(title).c_str(),
            txn.quote(text).c_str(),
            user_id,
            version
        );

        txn.exec0(query);

        memset(query, 0, sizeof(char) * 1024);
        sprintf(
            query,
            "update content set version = %d where id = %d",
            version,
            *content_id
        );

        txn.exec0(query);

        txn.commit();
    }
}
