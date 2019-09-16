//
// Created by adrien_bedel on 16/09/19.
//

#include "SLRException.h"

SLRException::SLRException(int errorCode) throw()
: _errorCode(errorCode), _where("?"),_message("?")
{}

SLRException::SLRException(int errorCode, const std::string &where, const std::string &message) throw()
: _errorCode(errorCode), _where(where), _message(message) {}

int                 SLRException::getErrorCode() const
{ return (_errorCode); }

const std::string   SLRException::getMessage() const
{ return (_message); }

const std::string   SLRException::getLocation() const
{ return (_where); }

const std::string   SLRException::fullErrorInfos() const
{
    std::string fullMessage = "Error code : ";
    fullMessage += std::to_string(_errorCode);
    fullMessage += ", at : ";
    fullMessage += _where;
    fullMessage += ", because : ";
    fullMessage += _message;
    return (fullMessage);
}


