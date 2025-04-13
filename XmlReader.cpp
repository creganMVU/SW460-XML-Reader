#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>

#include <iostream>
#include <string>

using namespace xercesc;

void printBookTitles(DOMDocument* doc) {
    DOMElement* root = doc->getDocumentElement();

    // Get all <book> elements
    DOMNodeList* bookList = root->getElementsByTagName(XMLString::transcode("book"));

    for (XMLSize_t i = 0; i < bookList->getLength(); ++i) {
        DOMElement* book = dynamic_cast<DOMElement*>(bookList->item(i));
        DOMNodeList* titleList = book->getElementsByTagName(XMLString::transcode("title"));

        if (titleList->getLength() > 0) {
            DOMElement* titleElement = dynamic_cast<DOMElement*>(titleList->item(0));
            char* titleText = XMLString::transcode(titleElement->getTextContent());
            std::cout << "Title: " << titleText << std::endl;
            XMLString::release(&titleText);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./BookParser <xml-file>" << std::endl;
        return 1;
    }

    const char* xmlFile = argv[1];

    XMLPlatformUtils::Initialize();

    XercesDOMParser parser;
    parser.setValidationScheme(XercesDOMParser::Val_Always);
    parser.setDoNamespaces(true);

    parser.parse(xmlFile);
    DOMDocument* doc = parser.getDocument();
    printBookTitles(doc);

    XMLPlatformUtils::Terminate();
    return 0;
}
