#include <socketer.h>
#include <srv-content.h>
#include <list>

namespace Content::Middleware
{
    Chain::Chain()
    {
        this->chain = std::list<Content::Middleware::Middleware*>();
    }

    void Chain::on_request(Socketer::Request *req, Socketer::Response *resp)
    {
        for (auto it = chain.begin(); it != chain.end(); it++) {
            (*it)->on_request(req, resp);
        }
    }
}
