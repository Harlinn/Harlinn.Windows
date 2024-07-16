#ifndef ODBC_PARAMETERMETADATA_H_INCLUDED
#define ODBC_PARAMETERMETADATA_H_INCLUDED
//------------------------------------------------------------------------------
#include <odbc/Config.h>
#include <odbc/Forwards.h>
//------------------------------------------------------------------------------
NS_ODBC_START
//------------------------------------------------------------------------------
/**
 * Metadata on parameters in a prepared statement.
 */
class ParameterMetaData : public RefCounted
{
    friend class PreparedStatement;

private:
    ODBC_EXPORT ParameterMetaData(PreparedStatement* ps);

public:
    /**
     * Retrieves the number of parameters in the associated PreparedStatement
     * object.
     *
     * @return  The number of parameters.
     */
    ODBC_EXPORT unsigned short getParameterCount();

    /**
     * Retrieves the SQL type of the specified parameter.
     *
     * @param paramIndex  The parameter index starting from 1.
     * @return            The SQL type.
     */
    ODBC_EXPORT short getParameterType(unsigned short paramIndex);

    /**
     * Retrieves the size of the column or expression measured in characters.
     *
     * @param paramIndex  The parameter index starting from 1.
     * @return            The size in characters.
     */
    ODBC_EXPORT std::size_t getParameterSize(unsigned short paramIndex);

    /**
     * Retrieves the precision of the type assigned to the parameter.
     *
     * For numeric data, the returned value denotes the maximum number of digits
     * in a number. For character data, this is the length of a character
     * sequence. For date, time and timestamp types, this is the length of their
     * string representation.
     *
     * @param paramIndex  The parameter index starting from 1.
     * @return            The precision value.
     */
    ODBC_EXPORT unsigned short getPrecision(unsigned short paramIndex);

    /**
     * Retrieves the scale of numeric data, which is the maximum number of
     * decimal digits.
     *
     * The function returns 0 for non-numeric data.
     *
     * @param paramIndex  The parameter index starting from 1.
     * @return            The scale value.
     */
    ODBC_EXPORT unsigned short getScale(unsigned short paramIndex);

    /**
     * Determines whether the corresponding column accepts null values or not.
     *
     * @param paramIndex  The parameter index starting from 1.
     * @return            True if the parameter accepts nulls, false otherwise.
     */
    ODBC_EXPORT bool isNullable(unsigned short paramIndex);

private:
    PreparedStatementRef ps_;
};
//------------------------------------------------------------------------------
NS_ODBC_END
//------------------------------------------------------------------------------
#endif
