//
// Created by adrien_bedel on 16/09/19.
//

#ifndef SOLVEUR_SLREXCEPTION_H
#define SOLVEUR_SLREXCEPTION_H

#include <exception>
#include <string>

class SLRException
{
private:

    std::string _message;
    std::string _where;
    int         _errorCode;

public:

    SLRException(int errorCode = 0) throw();
    SLRException(int , const std::string &, const std::string &) throw();

    const std::string   getMessage() const;
    const std::string   getLocation() const;
    int                 getErrorCode() const;
    const std::string   fullErrorInfos() const ;
};

#endif //SOLVEUR_SLREXCEPTION_H
