#ifndef MTLX_TO_A_EXCEPTIONS_H
#define MTLX_TO_A_EXCEPTIONS_H

#include <string>
#include <exception>
#include <stdexcept>

namespace MaterialXToArnold
{

// The base class for exceptions that are propagated from the MaterialX to
// Arnold library.
class Exception : public std::exception
{
public:
    explicit Exception(const std::string& source,
                       int line,
                       const std::string& message) noexcept;

    Exception(const Exception& e) noexcept;

    Exception& operator=(const Exception& e) noexcept;

    virtual ~Exception() noexcept;

    virtual const char* what() const noexcept;

private:
    std::string msg;

    static std::string Message(const std::string& source,
                               const int ln,
                               const std::string& message);

};

// An exception that is thrown when a general runtime error happen in the lib
class RuntimeError : public Exception
{
public:
    explicit RuntimeError(const std::string& source,
                          int line,
                          const std::string& message) noexcept;

    RuntimeError(const RuntimeError& e) noexcept;

    virtual ~RuntimeError() noexcept;
};

// An exception that is thrown when the MaterialX versions are not compatible.
class IncompatibleVersionsError : public Exception
{
public:
    explicit IncompatibleVersionsError(const std::string& source,
                                       int line,
                                       const std::string& message) noexcept;

    IncompatibleVersionsError(const IncompatibleVersionsError& e) noexcept;

    virtual ~IncompatibleVersionsError() noexcept;
};

// An exception that is thrown when a feature in the MaterialX to Arnold
// procedural is not supported. It may or may not be supported in the
// future.
class UnsupportedError : public Exception
{
public:
    explicit UnsupportedError(const std::string& source,
                                       int line,
                                       const std::string& message) noexcept;

    UnsupportedError(const UnsupportedError& e) noexcept;

    virtual ~UnsupportedError() noexcept;
};

// An exception that is thrown when a feature in the MaterialX to Arnold
// procedural has not yet been implemented, implying that we want to implement
// it in the future.
class NotImplementedError : public Exception
{
public:
    NotImplementedError() noexcept;

    explicit NotImplementedError(const std::string& message) noexcept;

    explicit NotImplementedError(const std::string& source,
                                       int line,
                                       const std::string& message) noexcept;

    NotImplementedError(const NotImplementedError& e) noexcept;

    virtual ~NotImplementedError() noexcept;
};

// An exception that is thrown when a given value is invalid.
class ValueError : public Exception
{
public:
    ValueError() noexcept;

    explicit ValueError(const std::string& message) noexcept;

    explicit ValueError(const std::string& source,
                                       int line,
                                       const std::string& message) noexcept;

    ValueError(const ValueError& e) noexcept;

    virtual ~ValueError() noexcept;
};

} // namespce MaterialXToArnold

#endif // MTLX_TO_A_EXCEPTIONS_H
