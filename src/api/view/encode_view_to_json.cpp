#include <srv-content.h>

namespace Content::API::View
{
    JsonStreamAnalyzer::Element* Handler::encode_view_to_json(Content::Model::View* view)
    {
        JsonStreamAnalyzer::Element* elView;

        auto objView = new JsonObject;

        std::string strId = std::to_string(view->id);
        auto elId = new JsonStreamAnalyzer::Element(ELEMENT_TYPE_NUMERIC, &strId);
        (*objView)["id"] = elId;

        if (view->slug != nullptr) {
            auto strSlug = new std::string(view->slug);
            auto elSlug = new JsonStreamAnalyzer::Element(ELEMENT_TYPE_TEXT, strSlug);
            (*objView)["slug"] = elSlug;
        } else {
            auto elSlug = new JsonStreamAnalyzer::Element(ELEMENT_TYPE_NULL, nullptr);
            (*objView)["slug"] = elSlug;
        }

        if (view->contentId != nullptr) {
            std::string strContentId = std::to_string(*view->contentId);
            auto elContentId = new JsonStreamAnalyzer::Element(ELEMENT_TYPE_NUMERIC, &strContentId);
            (*objView)["contentId"] = elContentId;
        } else {
            (*objView)["contentId"] = new JsonStreamAnalyzer::Element(ELEMENT_TYPE_NULL, nullptr);
        }

        if (view->title != nullptr) {
            auto strTitle = new std::string(view->title);
            auto elTitle = new JsonStreamAnalyzer::Element(ELEMENT_TYPE_TEXT, strTitle);
            (*objView)["title"] = elTitle;
        } else {
            auto elTitle = new JsonStreamAnalyzer::Element(ELEMENT_TYPE_NULL, nullptr);
            (*objView)["title"] = elTitle;
        }

        if (view->text != nullptr) {
            auto strText = new std::string(view->text);
            auto elText = new JsonStreamAnalyzer::Element(ELEMENT_TYPE_TEXT, strText);
            (*objView)["text"] = elText;
        } else {
            auto elText = new JsonStreamAnalyzer::Element(ELEMENT_TYPE_NULL, nullptr);
            (*objView)["text"] = elText;
        }

        elView = new JsonStreamAnalyzer::Element(ELEMENT_TYPE_OBJECT, objView);
        return elView;
    }
}
