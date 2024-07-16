#ifndef ODBC_RESULTSET_H_INCLUDED
#define ODBC_RESULTSET_H_INCLUDED
//------------------------------------------------------------------------------
#include <odbc/Config.h>
#include <odbc/Forwards.h>
#include <odbc/Types.h>
//------------------------------------------------------------------------------
NS_ODBC_START
//------------------------------------------------------------------------------
/**
 * Represents the result set of a SQL query.
 */
class ResultSet : public RefCounted
{
    friend class DatabaseMetaData;
    friend class DatabaseMetaDataBase;
    friend class DatabaseMetaDataUnicode;
    friend class PreparedStatement;
    friend class Statement;

public:
    /**
     * Data length constant that signals that the data is NULL.
     */
    constexpr static std::size_t NULL_DATA = (std::size_t)-1;

    /**
     * Data length constant that signals that the database could not determine
     * the length of the data.
     */
    constexpr static std::size_t UNKNOWN_LENGTH = (std::size_t)-2;

private:
    ODBC_EXPORT ResultSet(StatementBase* parent);
    ODBC_EXPORT ~ResultSet();

public:
    /**
     * Advances the cursor to the next row of the ResultSet object and fetches
     * data for all bound columns.
     *
     * @return  Returns true if the current row is valid, false otherwise.
     */
    ODBC_EXPORT bool next();

    /**
     * Closes the cursor associated with the current Statement object and
     * discards all pending results.
     */
    ODBC_EXPORT void close();

    /**
     * Retrieves a ResultSetMetaData object that contains information about the
     * number, types and properties of the columns in this ResultSet object.
     *
     * @return  Returns a ResultSetMetaData object.
     */
    ODBC_EXPORT ResultSetMetaDataRef getMetaData();

    /**
     * Retrieves a ResultSetMetaDataUnicode object that contains information
     * about the number, types and properties of the columns in this ResultSet
     * object.
     *
     * @return  Returns a ResultSetMetaDataUnicode object.
     */
    ODBC_EXPORT ResultSetMetaDataUnicodeRef getMetaDataUnicode();

    /**
     * Retrieves the value of the specified column in the current row as
     * a boolean.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT Boolean getBoolean(unsigned short columnIndex);

    /**
     * Retrieves the value of the specified column in the current row as
     * a signed byte.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT Byte getByte(unsigned short columnIndex);

    /**
     * Retrieves the value of the specified column in the current row as
     * an unsigned byte.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT UByte getUByte(unsigned short columnIndex);

    /**
     * Retrieves the value of the specified column in the current row as
     * a signed short integer.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT Short getShort(unsigned short columnIndex);

    /**
     * Retrieves the value of the specified column in the current row as
     * an unsigned short integer.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT UShort getUShort(unsigned short columnIndex);

    /**
     * Retrieves the value of the specified column in the current row as
     * a signed integer.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT Int getInt(unsigned short columnIndex);

    /**
     * Retrieves the value of the specified column in the current row as
     * an unsigned integer.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT UInt getUInt(unsigned short columnIndex);

    /**
     * Retrieves the value of the specified column in the current row as
     * a signed long integer.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT Long getLong(unsigned short columnIndex);

    /**
     * Retrieves the value of the specified column in the current row as
     * an unsigned long integer.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT ULong getULong(unsigned short columnIndex);

    /**
     * Retrieves the value of the specified column in the current row as
     * a decimal object.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT Decimal getDecimal(unsigned short columnIndex);

    /**
     * Retrieves the value of the specified column in the current row as
     * a floating point type with single precision.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT Float getFloat(unsigned short columnIndex);

    /**
     * Retrieves the value of the specified column in the current row as
     * a floating point type with double precision.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT Double getDouble(unsigned short columnIndex);

    /**
     * Retrieves the value of the specified column in the current row as
     * a date object.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT Date getDate(unsigned short columnIndex);

    /**
     * Retrieves the value of the specified column in the current row as
     * a time object.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT Time getTime(unsigned short columnIndex);

    /**
     * Retrieves the value of the specified column in the current row as
     * a timestamp object.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT Timestamp getTimestamp(unsigned short columnIndex);

    /**
     * Retrieves the value of the specified column in the current row as
     * a string object.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT String getString(unsigned short columnIndex);

    /**
     * Retrieves the value of the specified column in the current row as
     * a string with 16-bit characters.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT NString getNString(unsigned short columnIndex);

    /**
     * Retrieves the value of the specified column in the current row as
     * an object with binary data.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the column value.
     */
    ODBC_EXPORT Binary getBinary(unsigned short columnIndex);

    /**
     * Retrieves the length of the binary data stored in the specified column of
     * the current row.
     *
     * If the binary data is NULL, the constant NULL_DATA is returned. If the
     * database cannot determine the length, the constant UNKNOWN_LENGTH is
     * returned.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             Returns the length of binary data, NULL_DATA or
     *                     UNKNOWN_LENGTH.
     */
    ODBC_EXPORT std::size_t getBinaryLength(unsigned short columnIndex);

    /**
     * Retrieves the binary data stored in the specified column of the current
     * row.
     *
     * The total length of the binary data can be found by calling
     * the getBinaryLength() function.
     *
     * @param columnIndex  The column index starting from 1.
     * @param data         The pointer to a buffer where the read data will be
     *                     stored.
     * @param size  The maximum number of bytes to be read.
     */
    ODBC_EXPORT void getBinaryData(unsigned short columnIndex, void* data,
        std::size_t size);

    /**
     * Retrieves the lengh of the string stored in the specified column of
     * the current row.
     *
     * If the string is NULL, the constant NULL_DATA is returned. If the
     * database cannot determine the length, the constant UNKNOWN_LENGTH is
     * returned.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             The length of a string in characters, NULL_DATA or
     *                     UNKNOWN_LENGTH.
     */
    ODBC_EXPORT std::size_t getStringLength(unsigned short columnIndex);

    /**
     * Retrieves the string data stored in the specified column of the current
     * row.
     *
     * The total length of the string can be found by calling the
     * getStringLength() function.
     *
     * @param columnIndex  The column index starting from 1.
     * @param[out] data  The pointer to a buffer where the read data will be
     *                   stored.
     * @param size  The maximum number of bytes to be read.
     */
    ODBC_EXPORT void getStringData(unsigned short columnIndex, void* data,
        std::size_t size);

    /**
     * Retrieves the length of the string with 16-bit characters stored in the
     * specified column of the current row.
     *
     * If the string is NULL, the constant NULL_DATA is returned. If the
     * database cannot determine the length, the constant UNKNOWN_LENGTH is
     * returned.
     *
     * @param columnIndex  The column index starting from 1.
     * @return             The length of a string in characters, NULL_DATA or
     *                     UNKNOWN_LENGTH.
     */
    ODBC_EXPORT std::size_t getNStringLength(unsigned short columnIndex);

    /**
     * Retrieves the 16-bit character string data stored in the specified column
     * of the current row.
     *
     * The total length of the string can be found by calling the
     * getNStringLength() function.
     *
     * @param columnIndex  The column index starting from 1.
     * @param data         The pointer to a buffer where read data will be
                           stored.
     * @param size         The maximum number of 16-bit characters to be read.
     */
    ODBC_EXPORT void getNStringData(unsigned short columnIndex, void* data,
        std::size_t size);

private:
    StatementBaseRef parent_;
};
//------------------------------------------------------------------------------
NS_ODBC_END
//------------------------------------------------------------------------------
#endif
