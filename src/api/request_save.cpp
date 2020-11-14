#include <srv-content.h>

namespace Content::API
{
    RequestSave::RequestSave() {
        this->id = nullptr;
        this->title = nullptr;
        this->text = nullptr;
        this->user_id = 0;
    }
}
