#include "exceptions.h"

NotEnoughArgumentsException::NotEnoughArgumentsException(const std::string &what, int argc_given, int argc_needed)
        : message_(
        "Not enough arguments for " + what + ": " + std::to_string(argc_given) + " (" +
        std::to_string(argc_needed) + " expected)") {}

const char *NotEnoughArgumentsException::what() const noexcept {
    return message_.c_str();
}

FileOpenFailedException::FileOpenFailedException(const std::string &path) : message_(
        "Failed to open file: " + path) {}

const char *FileOpenFailedException::what() const noexcept {
    return message_.c_str();
}
