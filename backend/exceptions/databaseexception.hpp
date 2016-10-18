#ifndef DATABASEEXCEPTION_HPP
#define DATABASEEXCEPTION_HPP

#include <exception>
#include <string>

// # Database exception
class DatabaseException : public std::exception
{
    // ## Private
private:

    // ### fields

    // #### Statement
    std::string _message;


    // ## Public
public:

    // ### Constructors

    // #### Values Constructor
    explicit DatabaseException(const std::string& statement, const std::string& table, const std::string& error) :
      _message("Error in database call " + statement + " in table " + table + ": " + error) { }

    // ### override

    // #### what
    virtual const char* what() const noexcept override
    {
        return _message.c_str();
    }
};

#endif // DATABASEEXCEPTION_HPP
