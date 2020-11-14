#include <string.h>
#include <iostream>
#include <srv-content.h>
#include <socketer.h>

Content::Config* config = nullptr;

Content::API::SaveHandler* saveHandler = nullptr;

void on_request(Socketer::Request* request, Socketer::Response* resp);

int main(int argc, char** argv) {
    config = new Content::Config(argc, argv);

    if (config->isHelp()) {
        std::cout << "It is help message" << std::endl;
        return 0;
    }

    // initialize DB
    Content::DBConn db_conn(
        config->getDbHost(),
        config->getDbPort(),
        config->getDbUser(),
        config->getDbPassword(),
        config->getDbName()
    );
    Content::Storage s(&db_conn);

    // initialize server
    Socketer::Socketer server;

    server.listen(config->get_listen(), config->get_port());

    server.addMiddleware(Content::Middleware::add_server);

    saveHandler = new Content::API::SaveHandler(&s);
    server.addHandler(
        "/v1/save",
        [](Socketer::Request* request, Socketer::Response* resp) {
            // call api handler
            saveHandler->on_request(request, resp);
        }
    );

    server.setDefaultHandler(
        [](Socketer::Request* request, Socketer::Response* resp) {
            // run default handler
            on_request(request, resp);
        }
    );

    server.dispatch();

    return 0;
}

void on_request(Socketer::Request* request, Socketer::Response* resp) {
    std::cout << request->raw_body << std::endl;

    std::string method(request->method);
    std::string uri(request->uri);

    std::cout << "URI: [" << uri << "]" << std::endl;
    std::cout << "Method: [" << method << "]" << std::endl;

    Content::DBConn db_conn(
        config->getDbHost(),
        config->getDbPort(),
        config->getDbUser(),
        config->getDbPassword(),
        config->getDbName()
    );
    Content::Storage s(&db_conn);

    int content_id = 7;
    s.save_content(&content_id, (char*) "test title", (char*) "text of content", 1);

    resp->writeHead("HTTP/1.1 204 No Content");
    resp->reply();
}
