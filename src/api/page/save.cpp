#include <srv-content.h>

namespace Content::API::Page
{
    SaveHandler::SaveHandler(Content::Storage *storage)
    {
        this->storage = storage;
    }

    void SaveHandler::on_request(Socketer::Request *request, Socketer::Response *resp) {

    }
}
