#include <emscripten/bind.h>
#include <unicode/unistr.h>
#include <unicode/brkiter.h>
#include <unicode/translit.h>
#include <unicode/uchar.h>
#include <unicode/udata.h>
#include <vector>
#include <iostream>
using namespace emscripten;
using namespace icu;

void printRegistrationError(std::string id, UParseError pError, UErrorCode status)
{
    std::cout << "Registration Error, " << u_errorName(status) << ": " << id << std::endl;
    std::cout << "Line: " << pError.line << std::endl;
    std::cout << "Offset: " << pError.offset << std::endl;
    std::string preContext, postContext;
    ((UnicodeString)pError.preContext).toUTF8String(preContext);
    ((UnicodeString)pError.postContext).toUTF8String(postContext);
    std::cout << "Pre-context: " << std::endl
              << preContext << std::endl;
    std::cout << "Post-context: " << std::endl
              << postContext << std::endl;
}

void registerTransliterator(std::string id, std::string inverseId, std::string rules)
{
    auto urules = UnicodeString(rules.c_str());
    UParseError pError;
    UErrorCode status = U_ZERO_ERROR;
    Transliterator *t = Transliterator::createFromRules(UnicodeString(id.c_str()), urules, UTRANS_FORWARD, pError, status);
    if (U_FAILURE(status))
    {
        printRegistrationError(id, pError, status);
    }
    else
    {
        Transliterator::registerInstance(t);
        // std::cout << "Registration Success: " << id << std::endl;
    }
    if (inverseId != "")
    {
        Transliterator *it = Transliterator::createFromRules(UnicodeString(inverseId.c_str()), urules, UTRANS_REVERSE, pError, status);
        if (U_FAILURE(status))
        {
            printRegistrationError(inverseId, pError, status);
        }
        else
        {
            Transliterator::registerInstance(it);
            // std::cout << "Registration Success: " << inverseId << std::endl;
        }
    }
}

std::map<std::string, Transliterator *> transliteratorCache;

std::string transliterate(std::string text, std::string id)
{
    UErrorCode status = U_ZERO_ERROR;
    UTransDirection dir = UTRANS_FORWARD;
    Transliterator *t;
    if (transliteratorCache.count(id))
    {
        t = transliteratorCache[id];
    }
    else
    {
        auto uid = UnicodeString(id.c_str());
        t = Transliterator::createInstance(uid, dir, status);
        if (U_FAILURE(status))
        {
            std::string err(u_errorName(status));
            std::cout << "Transliteration Error, " << err << ": " << id << std::endl;
            return "";
        }

        transliteratorCache[id] = t;
    }
    std::string output = "";
    auto uoutput = UnicodeString(text.c_str());
    t->transliterate(uoutput);
    uoutput.toUTF8String(output);
    return output;
}

std::string transliterateFromRules(std::string text, std::string rules)
{
    auto urules = UnicodeString(rules.c_str());
    UParseError pError;
    UErrorCode status = U_ZERO_ERROR;
    Transliterator *t = Transliterator::createFromRules("d043ee511848f159595e1ba250a0f1d8", urules, UTRANS_FORWARD, pError, status);
    if (U_FAILURE(status))
    {
        printRegistrationError("d043ee511848f159595e1ba250a0f1d8", pError, status);
        return "";
    }
    else
    {
        std::cout << "Transliterator registered" << std::endl;
        std::string output = "";
        auto uoutput = UnicodeString(text.c_str());
        t->transliterate(uoutput);
        uoutput.toUTF8String(output);
        return output;
    }
}

void getAvailableIDs()
{
    UErrorCode status = U_ZERO_ERROR;
    StringEnumeration *availableIds = Transliterator::getAvailableIDs(status);
    const UnicodeString *availableId = availableIds->snext(status);
    while (availableId != NULL && status == U_ZERO_ERROR)
    {
        std::string availableIdString;
        availableId->toUTF8String(availableIdString);
        std::cout << availableIdString << std::endl;
        availableId = availableIds->snext(status);
    }
}

EMSCRIPTEN_BINDINGS(transliterator)
{
    function("registerTransliterator", &registerTransliterator);
    function("transliterate", &transliterate);
    function("transliterateFromRules", &transliterateFromRules);
    function("getAvailableIDs", &getAvailableIDs);
}
