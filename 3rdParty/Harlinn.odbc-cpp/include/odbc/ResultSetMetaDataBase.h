#ifndef ODBC_RESULTSETMETADATABASE_H_INCLUDED
#define ODBC_RESULTSETMETADATABASE_H_INCLUDED
//------------------------------------------------------------------------------
#include <odbc/Config.h>
#include <odbc/Forwards.h>
#include <odbc/Types.h>
//------------------------------------------------------------------------------
NS_ODBC_START
//------------------------------------------------------------------------------
/**
 * Metadata on a result set.
 */
class ResultSetMetaDataBase : public RefCounted
{
protected:
    ODBC_EXPORT ResultSetMetaDataBase(StatementBase* parent);

public:
    /**
     * Returns the number of columns in the result set.
     *
     * @return  Returns the number of columns in the result set.
     */
    ODBC_EXPORT unsigned short getColumnCount();

    /**
     * Returns a column's data type.
     *
     * See SQLDataTypes for a list of data type constants.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column's data type.
     */
    ODBC_EXPORT short getColumnType(unsigned short columnIndex);

    /**
     * Returns a column's length.
     *
     * This is usually the maximum length of a value measured in characters for
     * strings and measured in bytes for binary data.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column's length.
     */
    ODBC_EXPORT std::size_t getColumnLength(unsigned short columnIndex);

    /**
     * Returns a column's octet length.
     *
     * This is usually the maximum length of a value measured in bytes.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column's octet length.
     */
    ODBC_EXPORT std::size_t getColumnOctetLength(unsigned short columnIndex);

    /**
     * Returns a column's display size.
     *
     * This is the maximum number of characters to display a value.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column's display size.
     */
    ODBC_EXPORT std::size_t getColumnDisplaySize(unsigned short columnIndex);

    /**
     * Returns a column's precision in case of decimal types.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column's precision in case of decimal
     *                     types.
     */
    ODBC_EXPORT unsigned short getPrecision(unsigned short columnIndex);

    /**
     * Returns a column's scale in case of decimal types.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column's scale in case of decimal
     *                     types.
     */
    ODBC_EXPORT unsigned short getScale(unsigned short columnIndex);

    /**
     * Checks whether a column is auto-incrementing.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns true if the column is auto-incrementing,
     *                     false otherwise.
     */
    ODBC_EXPORT bool isAutoIncrement(unsigned short columnIndex);

    /**
     * Checks whether a column is case sensitive.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns true if the column is case-sensitive, false
     *                     otherwise.
     */
    ODBC_EXPORT bool isCaseSensitive(unsigned short columnIndex);

    /**
     * Checks whether a column is named.
     *
     * If a column is named, its name can be retrieved with the getColumnName()
     * function.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns true if the column is named, false otherwise.
     */
    ODBC_EXPORT bool isNamed(unsigned short columnIndex);

    /**
     * Checks whether a column can contain NULL values.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns true if the column can contain NULL values,
     *                     false otherwise.
     */
    ODBC_EXPORT bool isNullable(unsigned short columnIndex);

    /**
     * Checks whether a column in a result set is read-only.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns true if the column is read-only, false
     *                     otherwise.
     */
    ODBC_EXPORT bool isReadOnly(unsigned short columnIndex);

    /**
     * Checks whether a column can be used in WHERE-clauses with any comparison
     * operator.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns true if the column is searchable, false
     *                     otherwise.
     */
    ODBC_EXPORT bool isSearchable(unsigned short columnIndex);

    /**
     * Checks whether a column can contain signed numbers.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns true if the column can contain signed
     *                     numbers, false otherwise.
     */
    ODBC_EXPORT bool isSigned(unsigned short columnIndex);

protected:
    StatementBaseRef stmt_;
};
//------------------------------------------------------------------------------
NS_ODBC_END
//------------------------------------------------------------------------------
#endif
