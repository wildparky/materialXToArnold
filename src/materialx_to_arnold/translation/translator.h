#ifndef MTLX_TO_A_TRANSLATION_TRANSLATOR_H
#define MTLX_TO_A_TRANSLATION_TRANSLATOR_H

#include <tuple>
#include <sstream>

#include "exceptions.h"
#include "configuration.h"
#include "translation/dispatcher.h"

namespace MaterialXToArnold
{

template<typename AFT,     // Arnold Facade Type
         typename MFT>     // MaterialX Facade Type
class Translator
{
public:
    Translator(const AFT& arnold_facade,
               const MFT& materialx_facade,
               Configuration& config,
               typename AFT::AtNodeTDeleterFncPtrT node_deleter):
        af_ (arnold_facade),
        mf_ (materialx_facade),
        config_ (config),
        node_deleter_ (node_deleter),
        doc_ () { }

    void Translate()
    {
        Read();
        CheckVersions();

        Dispatcher<AFT, MFT> d(af_, mf_, config_, node_deleter_);

        // Traverse the document tree in depth-first order.
        for (typename MFT::ElementPtrT elem : doc_->traverseTree())
        {
            d.dispatch(elem);
        }
    }

private:

    // Try to read the MaterialX document from disk that is specified in the
    // Configuration object.
    void Read()
    {
        doc_ = mf_.createDocument();
        MSG_DEBUG(af_, "Attempting to find and read a MaterialX file \"%s\" "
                  "along search path(s) \"%s\" given on a node named \"%s\" "
                  "...", config_.materialx_file_name_.c_str(),
                  config_.materialx_search_path_.c_str(),
                  config_.procedural_node_name_);

        mf_.readFromXmlFile(doc_,
                            std::string(config_.materialx_file_name_),
                            std::string(config_.materialx_search_path_));

        MSG_INFO(af_, "Read a MaterialX file \"%s\" for the node named \"%s\".",
                 doc_->getSourceUri().c_str(), config_.procedural_node_name_);
    }

    void CheckVersions()
    {
        const std::pair<int, int> doc_version = doc_->getVersionIntegers();
        const int doc_major = doc_version.first;
        const int doc_minor = doc_version.second;

        const std::tuple<int, int, int> lib_version = mf_.getVersionIntegers();
        const int lib_major = std::get<0>(lib_version);
        const int lib_minor = std::get<1>(lib_version);

        if ((doc_major > lib_major) ||
            (doc_major == lib_major && doc_minor > lib_minor))
        {
            std::stringstream ss;
            ss << "The MaterialX document's version (" << doc_version.first <<
                  "." << doc_version.second <<
                  ") greater than the library's version (" <<
                  lib_major << "." << lib_minor << ")";
            throw IncompatibleVersionsError(__FILE__, __LINE__, ss.str());
        }

        MSG_DEBUG(af_, "The MaterialX docuement's version is %d.%d and the "
                  "library's version is a matching %d.%d.", doc_major,
                  doc_minor, lib_major, lib_minor);
    }

private:
    const AFT& af_;
    const MFT& mf_;
    Configuration& config_;
    typename AFT::AtNodeTDeleterFncPtrT node_deleter_;
    typename MFT::DocumentPtrT doc_;
};


} // namespce MaterialXToArnold

#endif // MTLX_TO_A_TRANSLATION_TRANSLATOR_H
