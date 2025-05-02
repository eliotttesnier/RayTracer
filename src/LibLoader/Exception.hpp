//
// Created by roussierenoa on 5/2/25.
//

#ifndef EXCEPTION_HPP

#define EXCEPTION_HPP
#include <exception>
#include <string>

class DLLException : public std::exception {
private:
    std::string _message;
public:
    DLLException(std::string const &message) : _message(message) {}
    DLLException(const char *message) : _message(message) {}

    const char *what() const noexcept override {return this->_message.c_str();};
};

#endif //EXCEPTION_HPP
