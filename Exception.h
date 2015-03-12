#include <exception>
#include <stdexcept>
#include <string>
#include <sstream>
#include <string.h>
#include <errno.h>

#ifndef EXCEPTION_H
#define EXCEPTION_H

class Exception : public std::runtime_error {
public:
    Exception() : std::runtime_error("Unknown Exception") {}

    virtual ~Exception() throw() {}

    virtual const char * what() const throw() {
        return "Exception: Unknown Exception";
    }

private:
    std::string message;
    std::string className;
    std::string methodName;
    std::string fileName;
    unsigned int lineNumber;
};

class GeneralException : public Exception {
public:
    GeneralException(const std::string & message) : Exception() {
        this->message = message;
    }

    ~GeneralException() throw() {}

    const char * what() const throw() {
        std::string tmp;

        tmp = "---> GeneralException: " + message;

        return tmp.c_str();
    }

private:
    std::string message;
};

class FileIOException : public Exception {
public:
    FileIOException(const std::string & filename, const std::string & message) : Exception() {
        this->filename = filename;
        this->message = message;
    }

    FileIOException(const std::string & message) : Exception() {
        this->filename.clear();
        this->message = message;
    }

    ~FileIOException() throw() {}

    const char * what() const throw() {
        std::string tmp;
        if(!filename.empty()) {
            tmp = "---> FileIOException: Make sure file \"" + filename + "\" exists and has read permissions: " + message;
        } else {
            tmp = "---> FileIOException: Make sure file exists and has read permissions: " + message;
        }

        return tmp.c_str();
    }

private:
    std::string filename;
    std::string message;
};

class ParseException : public Exception {
public:
    ParseException(const std::string & message) : Exception() {
        this->filename.clear();
        this->message = message;
    }

    ParseException(const std::string & filename, const std::string & message) : Exception() {
        this->filename = filename;
        this->message = message;
    }

    ~ParseException() throw() {}

    const char * what() const throw() {
        std::string tmp;

        if(filename.empty()) {
            tmp = "---> ParseException: " + message;
        } else {
            tmp = "---> ParseException: File: " + filename + ": " + message;
        }

        return tmp.c_str();
    }

private:
    std::string filename;
    std::string message;
};

#endif
