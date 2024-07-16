#ifndef ODBC_EXCEPTION_H_INCLUDED
#define ODBC_EXCEPTION_H_INCLUDED
//------------------------------------------------------------------------------
#include <stdexcept>
#include <string>
#include <odbc/Config.h>
#include <odbc/Forwards.h>
#include <odbc/Types.h>
//------------------------------------------------------------------------------
NS_ODBC_START
//------------------------------------------------------------------------------
/**
 * ODBC-related exception.
 */
class Exception : public std::exception
{
private:
    friend class Batch;
    friend class Connection;
    friend class DatabaseMetaData;
    friend class DatabaseMetaDataBase;
    friend class DatabaseMetaDataUnicode;
    friend class date;
    friend class decimal;
    friend class Environment;
    friend class ParameterMetaData;
    friend class PreparedStatement;
    friend class ResultSet;
    friend class ResultSetMetaData;
    friend class ResultSetMetaDataBase;
    friend class ResultSetMetaDataUnicode;
    friend class Statement;
    friend class StatementBase;
    friend class StringConverter;
    friend class time;
    friend class timestamp;
    friend class ValueBuffer;
    friend class Util;

    ODBC_EXPORT static void checkForError(short rc, short handleType, void* handle);
    ODBC_EXPORT static Exception create(short handleType, void* handle);

    ODBC_EXPORT Exception(const char* s);
    ODBC_EXPORT Exception(const std::string& s);

public:
    /**
     * Describes the reason of the exception.
     *
     * @return  Returns a description of the error that occurred.
     */
    ODBC_EXPORT const char* what() const noexcept override;

private:
    std::string msg_;
};
//------------------------------------------------------------------------------
NS_ODBC_END
//------------------------------------------------------------------------------
#endif
