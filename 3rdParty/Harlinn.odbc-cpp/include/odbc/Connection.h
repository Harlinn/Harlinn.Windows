#ifndef ODBC_CONNECTION_H_INCLUDED
#define ODBC_CONNECTION_H_INCLUDED
//------------------------------------------------------------------------------
#include <cstddef>
#include <odbc/Config.h>
#include <odbc/Forwards.h>
#include <odbc/Types.h>
//------------------------------------------------------------------------------
NS_ODBC_START
//------------------------------------------------------------------------------
/**
 * ODBC Connection Wrapper.
 *
 * A new Connection object can be created using Environment::createConnection().
 *
 * If a Connection object is connected to a database, it will disconnect
 * automatically when destroyed. However, it is not possible to check if an
 * error occurred during the disconnect. Therefore, it is recommended to use the
 * disconnect() member function to disconnect.
 */
class Connection : public RefCounted
{
    friend class Environment;
    friend class DatabaseMetaDataBase;
    friend class DatabaseMetaDataUnicode;

private:
    ODBC_EXPORT Connection(Environment* parent);
    ODBC_EXPORT ~Connection();

private:
    ODBC_EXPORT void setHandle(void* hdbc);

public:
    /**
     * Attempts to establish a database connection using a data source name.
     *
     * The method will throw an exception if a connection could not be
     * established.
     *
     * @param dsn       The data source name.
     * @param user      The user name to use.
     * @param password  The password to use.
     */
    ODBC_EXPORT void connect(const char* dsn, const char* user, const char* password);

    /**
     * Attempts to establish a database connection using an ODBC driver-specific
     * connection string.
     *
     * Refer to the documentation of your ODBC driver for details on the
     * connection string.
     *
     * The method will throw an exception if a connection could not be
     * established.
     *
     * @param connString  The driver-specific connection string.
     */
    ODBC_EXPORT void connect(const char* connString);

    /**
     * Disconnects from the database.
     */
    ODBC_EXPORT void disconnect();

    /**
     * Checks whether this Connection object is currently connected to the
     * database.
     *
     * This method checks only whether a successful connection has been made in
     * the past and has not been actively disconnected by the client. It will
     * not check if the connection is still alive. Use function isValid() to
     * check if a connection is still alive.
     *
     * @return  Returns true if the Connection object is connected to the
     *          database, false otherwise.
     */
    ODBC_EXPORT bool connected() const;

    /**
     * Checks whether the connection is still alive or not.
     *
     * @return  Returns true if the connection is alive, false otherwise.
     */
    ODBC_EXPORT bool isValid();

    /**
     * Gets the number of seconds that a driver can wait for any connection
     * request to complete.
     *
     * If the returned value equals 0, the driver will wait infinitely. The
     * default value is driver-specific.
     *
     * @return  Returns the connection timeout.
     */
    ODBC_EXPORT unsigned long getConnectionTimeout();

    /**
     * Sets the numer of seconds that a driver will wait for a connection
     * request to complete.
     *
     * If the value is set to 0, the driver can wait infinitely.
     *
     * @param seconds  The connection timeout.
     */
    ODBC_EXPORT void setConnectionTimeout(unsigned long seconds);

    /**
     * Gets the number of seconds that a driver can wait for a login attempt to
     * complete.
     *
     * If the returned value equals 0, the driver will wait infinitely. The
     * default value is driver-specific.
     *
     * @return  Returns the login timeout.
     */
    ODBC_EXPORT unsigned long getLoginTimeout();

    /**
     * Sets the numer of seconds that a driver will wait for a login attempt to
     * complete.
     *
     * If the value is set to 0, the driver can wait infinitely.
     *
     * @param seconds  The login timeout.
     */
    ODBC_EXPORT void setLoginTimeout(unsigned long seconds);

    /**
     * Sets a connection attribute of type integer.
     *
     * This method is intended for setting driver-specific connection
     * attributes. Generic connection attributes like the auto-commit attribute
     * should be set via the corresponding member function. Refer to your ODBC
     * driver documentation for a list of available attributes.
     *
     * Some connection attributes can only be set before a connection has been
     * made, others can only be set after a connection has been made. Refer
     * to the documentation of the attribute to find out if it must been set
     * before or after making a connection.
     *
     * @param attr   The attribute to set.
     * @param value  The value to set.
     */
    ODBC_EXPORT void setAttribute(int attr, int value);

    /**
     * Sets a connection attribute of type unsigned integer.
     *
     * This method is intended for setting driver-specific connection
     * attributes. Generic connection attributes like the auto-commit attribute
     * should be set via the corresponding member function. Refer to your ODBC
     * driver documentation for a list of available attributes.
     *
     * Some connection attributes can only be set before a connection has been
     * made, others can only be set after a connection has been made. Refer
     * to the documentation of the attribute to find out if it must been set
     * before or after making a connection.
     *
     * @param attr   The attribute to set.
     * @param value  The value to set.
     */
    ODBC_EXPORT void setAttribute(int attr, unsigned int value);

    /**
     * Sets a connection attribute of type string.
     *
     * This method is intended for setting driver-specific connection
     * attributes. Generic connection attributes like the auto-commit attribute
     * should be set via the corresponding member function. Refer to your ODBC
     * driver documentation for a list of available attributes.
     *
     * Some connection attributes can only be set before a connection has been
     * made, others can only be set after a connection has been made. Refer
     * to the documentation of the attribute to find out if it must been set
     * before or after making a connection.
     *
     * @param attr   The attribute to set.
     * @param value  The value to set.
     */
    ODBC_EXPORT void setAttribute(int attr, const char* value);

    /**
     * Sets a connection attribute of type string.
     *
     * This method is intended for setting driver-specific connection
     * attributes. Generic connection attributes like the auto-commit attribute
     * should be set via the corresponding member function. Refer to your ODBC
     * driver documentation for a list of available attributes.
     *
     * Some connection attributes can only be set before a connection has been
     * made, others can only be set after a connection has been made. Refer
     * to the documentation of the attribute to find out if it must been set
     * before or after making a connection.
     *
     * @param attr    The attribute to set.
     * @param value   The value to set.
     * @param length  The length of the string.
     */
    ODBC_EXPORT void setAttribute(int attr, const char* value, std::size_t length);

    /**
     * Sets a connection attribute of type binary.
     *
     * This method is intended for setting driver-specific connection
     * attributes. Generic connection attributes like the auto-commit attribute
     * should be set via the corresponding member function. Refer to your ODBC
     * driver documentation for a list of available attributes.
     *
     * Some connection attributes can only be set before a connection has been
     * made, others can only be set after a connection has been made. Refer
     * to the documentation of the attribute to find out if it must been set
     * before or after making a connection.
     *
     * @param attr   The attribute to set.
     * @param value  The value to set.
     * @param size   The size of the binary data in bytes.
     */
    ODBC_EXPORT void setAttribute(int attr, const void* value, std::size_t size);

    /**
     * Checks whether auto-commit mode is enabled.
     *
     * @return  Returns true if auto-commit is enabled, false otherwise.
     */
    ODBC_EXPORT bool getAutoCommit() const;

    /**
     * Enables or disables auto-commit mode for this connection.
     *
     * @param autoCommit  Set to true to enable auto-commit, set to false to
     *                    disable auto-commit.
     */
    ODBC_EXPORT void setAutoCommit(bool autoCommit);

    /**
     * Commits all changes made since the previous commit or rollback.
     */
    ODBC_EXPORT void commit();

    /**
     * Undoes all changes made since the previous commit or rollback.
     */
    ODBC_EXPORT void rollback();

    /**
     * Checks whether the Connection object allows statements performing any
     * updates on data.
     *
     * @return  Returns true if the Connection is in read only mode.
     */
    ODBC_EXPORT bool isReadOnly();

    /**
     * Sets the Connection object either in read-only or read-write mode.
     *
     * By default, the read-only mode is set to false.
     *
     * @param readOnly  The value indicating read-only mode.
     */
    ODBC_EXPORT void setReadOnly(bool readOnly);

    /**
     * Retrieves the transaction isolation level of this Connection object.
     *
     * @return   Returns the transaction isolation level.
     */
    ODBC_EXPORT TransactionIsolationLevel getTransactionIsolation();

    /**
     * Attempts to set the isolation level on which the transactions should be
     * executed.
     *
     * This method can be called only if there are no open transactions on the
     * current Connection object.
     *
     * @param level   The transaction isolation level.
     */
    ODBC_EXPORT void setTransactionIsolation(TransactionIsolationLevel level);

    /**
     * Creates a new Statement object.
     *
     * @return  Returns a reference to the newly created Statement object.
     */
    ODBC_EXPORT StatementRef createStatement();

    /**
     * Creates a new PreparedStatement object.
     *
     * @param sql  The SQL statement to prepare. Use '?' for placeholders.
     * @return     Returns a reference to the newly created PreparedStatement
     *             object.
     */
    ODBC_EXPORT PreparedStatementRef prepareStatement(const char* sql);

    /**
     * Creates a new PreparedStatement object.
     *
     * @param sql  The SQL statement to prepare. Use '?' for placeholders.
     * @return     Returns a reference to the newly created PreparedStatement
     *             object.
     */
    ODBC_EXPORT PreparedStatementRef prepareStatement(const char16_t* sql);

    /**
     * Retrieves metadata information of the database.
     *
     * @return  Returns a reference to the DatabaseMetaData object.
     */
    ODBC_EXPORT DatabaseMetaDataRef getDatabaseMetaData();

    /**
     * Retrieves metadata information of the database.
     *
     * @return  Returns a reference to the DatabaseMetaDataUnicode object.
     */
    ODBC_EXPORT DatabaseMetaDataUnicodeRef getDatabaseMetaDataUnicode();

private:
    EnvironmentRef parent_;
    void* hdbc_;
    bool connected_;
};
//------------------------------------------------------------------------------
NS_ODBC_END
//------------------------------------------------------------------------------
#endif
