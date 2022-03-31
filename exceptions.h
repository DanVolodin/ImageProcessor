#pragma once

#include <exception>
#include <string>

class NotEnoughArgumentsException : public std::exception {
public:
    NotEnoughArgumentsException(const std::string &what, int argc_given, int argc_needed);

    const char *what() const noexcept override;

private:
    std::string message_;
};

class FileOpenFailedException : public std::exception {
public:
    FileOpenFailedException(const std::string &path);

    const char *what() const noexcept override;

private:
    std::string message_;
};
