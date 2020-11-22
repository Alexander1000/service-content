#include <srv-content.h>

namespace Content::API::View
{
    Handler::Handler(Content::Storage *storage) {
        this->storage = storage;
    }
}
