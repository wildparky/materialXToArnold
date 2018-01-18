#include "exceptions.h"

#include <string>
#include <sstream>

namespace MaterialXToArnold
{

// Exception

Exception::Exception(const std::string& source,
                     int line,
                     const std::string& message) noexcept :
    std::exception(),
    msg(Message(source, line, message)) {}

Exception::Exception(const Exception& e) noexcept :
    std::exception(),
    msg(e.msg) {}

Exception::~Exception() noexcept {}

Exception& Exception::operator=(const Exception& e) noexcept
{
    msg = e.msg;
    return *this;
}

const char* Exception::what() const noexcept
{
    return msg.c_str();
}

std::string Exception::Message(const std::string& source,
                               const int line,
                               const std::string& message)
{
    std::stringstream ss;
#ifdef NDEBUG
    ss << message;
#else
    ss << message  << " (" << source << ":" << line << ")";
#endif
    return ss.str();
}

// RuntimeError

RuntimeError::RuntimeError(
        const std::string& source,
        int line,
        const std::string& message) noexcept :
    Exception(source, line, message) {}

RuntimeError::RuntimeError(
        const RuntimeError& e) noexcept :
    Exception(e) {}

RuntimeError::~RuntimeError() noexcept {}

// IncompatibleVersionsError

IncompatibleVersionsError::IncompatibleVersionsError(
        const std::string& source,
        int line,
        const std::string& message) noexcept :
    Exception(source, line, message) {}

IncompatibleVersionsError::IncompatibleVersionsError(
        const IncompatibleVersionsError& e) noexcept :
    Exception(e) {}

IncompatibleVersionsError::~IncompatibleVersionsError() noexcept {}

// UnsupportedError

UnsupportedError::UnsupportedError(
        const std::string& source,
        int line,
        const std::string& message) noexcept :
    Exception(source, line, message) {}

UnsupportedError::UnsupportedError(
        const UnsupportedError& e) noexcept :
    Exception(e) {}

UnsupportedError::~UnsupportedError() noexcept {}

// NotImplementedError

NotImplementedError::NotImplementedError(
        const std::string& source,
        int line,
        const std::string& message) noexcept :
    Exception(source, line, message) {}

NotImplementedError::NotImplementedError(
        const NotImplementedError& e) noexcept :
    Exception(e) {}

NotImplementedError::~NotImplementedError() noexcept {}

// ValueError

ValueError::ValueError(
        const std::string& source,
        int line,
        const std::string& message) noexcept :
    Exception(source, line, message) {}

ValueError::ValueError(
        const ValueError& e) noexcept :
    Exception(e) {}

ValueError::~ValueError() noexcept {}

} // namespce MaterialXToArnold
