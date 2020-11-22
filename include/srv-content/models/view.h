#ifndef SRV_CONTENT_MODEL_VIEW_H
#define SRV_CONTENT_MODEL_VIEW_H

namespace Content::Model
{
    class View
    {
    public:
        int id;
        char* slug;
        int* contentId;
        char* title;
        char* text;
    };
}

#endif
