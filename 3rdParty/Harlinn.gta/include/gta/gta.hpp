/*
 * gta.hpp
 *
 * This file is part of libgta, a library that implements the Generic Tagged
 * Array (GTA) file format.
 *
 * Copyright (C) 2010, 2011, 2012, 2019
 * Martin Lambers <marlam@marlam.de>
 *
 * Libgta is free software: you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 2.1 of the License, or (at your option)
 * any later version.
 *
 * Libgta is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Libgta. If not, see <http://www.gnu.org/licenses/>.
 */


/**
 * \file gta.hpp
 * \brief The libgta C++ interface.
 *
 * This document describes the C++ language interface of libgta.
 */


#ifndef GTA_HPP
#define GTA_HPP

#include <exception>
#include <istream>
#include <ostream>
#include <vector>
#include <limits>
#include <cerrno>
#include <cstring>
#include <cstdio>

#include <gta/gta.h>

#ifdef _MSC_VER
#  pragma warning (push)
#  pragma warning (disable: 4996)	// strerror and _snprintf
#  pragma warning (disable: 4244)	// conversion from uintmax_t to unsigned int
#endif


/**
 * \brief The gta namespace.
 */
namespace gta
{
    /**
     * \brief GTA result
     *
     * This is equivalent to \a gta_result_t from the C interface.
     */
    enum result
    {
        ok = GTA_OK,
        /**<
         * \brief   Success / no error
         */
        overflow = GTA_OVERFLOW,
        /**<
         * \brief   Size overflow
         */
        unsupported_data = GTA_UNSUPPORTED_DATA,
        /**<
         * \brief   Unsupported data
         *
         * The input seems to require features that are not available in this version
         * of the library.
         */
        unexpected_eof = GTA_UNEXPECTED_EOF,
        /**<
         * \brief   Unexpected end of file
         *
         * The GTA library intended to read more data, but the input did not provide it.
         */
        invalid_data = GTA_INVALID_DATA,
        /**<
         * \brief   Invalid data
         *
         * Some data was invalid. For example, an input file is not in GTA format.
         */
        system_error = GTA_SYSTEM_ERROR
        /**<
         * \brief   System error
         *
         * A system error occured. More information is available in errno.
         * Examples: memory allocation failure (errno == ENOMEM), input/output
         * errors (errno == EIO), no space left on device (errno == ENOSPC).
         */
    };

    /**
     * \brief GTA data types
     *
     * This is equivalent to \a gta_type_t from the C interface.
     *
     * All integer types contain the exact number of bits indicated by their name
     * and use the common two's complement representation.\n
     * All floating point types contain the exact number of bits indicated by their
     * name and conform to the binary representation defined by IEEE 754.\n
     * The complex types (gta::cfloat*) consist of two floating point values with the
     * number of bits indicated by the name, as defined above. The first value is
     * the real part, the second value is the imaginary part. For example,
     * \a gta::cfloat32 consists of two \a gta::float32 values.\n
     * The name \a gta::blob can be used for data types that are not defined in this
     * list. In this case, the size of the data type must be given, and the data type
     * must be independent of endianness.
     */
    enum type
    {
        int8 = GTA_INT8,           /**< \brief int8_t */
        uint8 = GTA_UINT8,         /**< \brief uint8_t */
        int16 = GTA_INT16,         /**< \brief int16_t */
        uint16 = GTA_UINT16,       /**< \brief uint16_t */
        int32 = GTA_INT32,         /**< \brief int32_t */
        uint32 = GTA_UINT32,       /**< \brief uint32_t */
        int64 = GTA_INT64,         /**< \brief int64_t */
        uint64 = GTA_UINT64,       /**< \brief uint64_t */
        int128 = GTA_INT128,       /**< \brief int128_t (unavailable on many platforms) */
        uint128 = GTA_UINT128,     /**< \brief uint128_t (unavailable on many platforms) */
        float32 = GTA_FLOAT32,     /**< \brief IEEE 754 single precision floating point (on many platforms: float) */
        float64 = GTA_FLOAT64,     /**< \brief IEEE 754 double precision floating point (on many platforms: double) */
        float128 = GTA_FLOAT128,   /**< \brief IEEE 754 quadrupel precision floating point (unavailable on many platforms, even if long double exists) */
        cfloat32 = GTA_CFLOAT32,   /**< \brief complex (re,im) based on two \a gta::float32 */
        cfloat64 = GTA_CFLOAT64,   /**< \brief complex (re,im) based on two \a gta::float64 */
        cfloat128 = GTA_CFLOAT128, /**< \brief complex (re,im) based on two \a gta::float128 */
        blob = GTA_BLOB            /**< \brief Data blob; must be endianness-independent; user must specify the size */
    };

    /**
     * \brief GTA compression methods
     *
     * These are deprecated. Do not use them anymore, they will be removed in a future version.
     */
    enum compression
    {
        none = GTA_NONE,   /**< \brief No compression */
        zlib = GTA_ZLIB,   /**< \brief ZLIB compression (fast, moderate compression rate) */
        zlib1 = GTA_ZLIB1, /**< \brief ZLIB compression with level 1 */
        zlib2 = GTA_ZLIB2, /**< \brief ZLIB compression with level 2 */
        zlib3 = GTA_ZLIB3, /**< \brief ZLIB compression with level 3 */
        zlib4 = GTA_ZLIB4, /**< \brief ZLIB compression with level 4 */
        zlib5 = GTA_ZLIB5, /**< \brief ZLIB compression with level 5 */
        zlib6 = GTA_ZLIB6, /**< \brief ZLIB compression with level 6 */
        zlib7 = GTA_ZLIB7, /**< \brief ZLIB compression with level 7 */
        zlib8 = GTA_ZLIB8, /**< \brief ZLIB compression with level 8 */
        zlib9 = GTA_ZLIB9, /**< \brief ZLIB compression with level 9 */
        bzip2 = GTA_BZIP2, /**< \brief BZIP2 compression (moderate speed, good compression rates) */
        xz = GTA_XZ        /**< \brief XZ compression (low/moderate speed, good/very good compression rates) */
    };

    /**
     * \brief The exception class.
     *
     * The GTA C++ interface reports errors by throwing exceptions. You can use
     * them just like std::exceptions, but you can also query the original
     * \a gta::result that caused the exception.
     */
    class exception : public std::exception
    {
    private:

        static const int _whatsize = 96;
        gta::result _r;
        int _sys_errno;
        char _what[_whatsize];

    public:

        /**
         * \brief       Constructor.
         * \param s     The action that failed.
         * \param r     The GTA result.
         */
        exception(const char *s, gta::result r)
            : _r(r), _sys_errno(r == system_error ? errno : 0)
        {
            const char *w = "";
            switch (r)
            {
            case ok:
                w = "success";
                break;
            case overflow:
                w = "value too large for data type";
                break;
            case unsupported_data:
                w = "unsupported data";
                break;
            case unexpected_eof:
                w = "unexpected end of input";
                break;
            case invalid_data:
                w = "invalid data";
                break;
            case system_error:
                w = strerror(_sys_errno);
                break;
            }
#if defined _MSC_VER
            _snprintf(_what, _whatsize, "%s: %s", s, w);
#else
            snprintf(_what, _whatsize, "%s: %s", s, w);
#endif
        }

        /**
         * \brief       Get the original GTA result.
         * \return      The original GTA result.
         */
        gta::result result() const
        {
            return _r;
        }

        /**
         * \brief       Get the original errno.
         * \return      The original errno.
         *
         * The original errno value is relevant if the original GTA result was
         * \a gta::system_error.
         */
        int sys_errno() const
        {
            return _sys_errno;
        }

        /**
         * \brief       Get a description.
         * \return      A description of the exception.
         */
        virtual const char* what() const throw ()
        {
            return _what;
        }
    };

    /**
     * \brief   Tag Lists.
     *
     * GTA stores meta information in tags.
     * Tag names are non-empty UTF-8 strings that must not contain '='.\n
     * Tag values are UTF-8 strings.\n
     * If you do not want to deal with conversions between the local character set and UTF-8,
     * you must restrict names and values to ASCII.
     */
    class taglist
    {
    private:

        gta_taglist_t *_taglist;

        /** \cond INTERNAL */
        void set(gta_taglist_t *taglist)
        {
            _taglist = taglist;
        }

        taglist()
        {
        }
        /** \endcond */

    public:

        /**
         * \brief       Get the number of tags.
         * \return      The number of tags.
         */
        uintmax_t tags() const
        {
            return gta_get_tags(_taglist);
        }

        /**
         * \brief       Get a tag name.
         * \param i     The tag index.
         * \return      The name of the tag.
         */
        const char *name(uintmax_t i) const
        {
            return gta_get_tag_name(_taglist, i);
        }

        /**
         * \brief       Get a tag value.
         * \param i     The tag index.
         * \return      The value of the tag.
         */
        const char *value(uintmax_t i) const
        {
            return gta_get_tag_value(_taglist, i);
        }

        /**
         * \brief       Get a tag value by its name.
         * \param name  The tag name.
         * \return      The tag value, or NULL if the tag name is not found.
         */
        const char *get(const char *name) const
        {
            return gta_get_tag(_taglist, name);
        }

        /**
         * \brief       Set a tag.
         * \param name  The tag name.
         * \param value The tag value.
         *
         * Sets the given tag, possibly overwriting an existing tag with the same name.
         * The name and value must be valid UTF-8 strings without control characters.
         * Additionally, the name must not contain the equal sign and must not be empty.
         */
        void set(const char *name, const char *value)
        {
            gta_result_t r = gta_set_tag(_taglist, name, value);
            if (r != GTA_OK)
            {
                throw exception("Cannot set GTA tag", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief       Unset a tag.
         * \param name  The tag name.
         *
         * Removes the tag with the given name, if it exists.
         */
        void unset(const char *name)
        {
            gta_result_t r = gta_unset_tag(_taglist, name);
            if (r != GTA_OK)
            {
                throw exception("Cannot unset GTA tag", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief       Unset all tags.
         *
         * Removes all tags.
         */
        void unset_all()
        {
            gta_unset_all_tags(_taglist);
        }

        /**
         * \brief       Assignment operator.
         * \param tl    The tag list to copy.
         */
        const taglist &operator=(const taglist &tl)
        {
            gta_result_t r = gta_clone_taglist(_taglist, tl._taglist);
            if (r != GTA_OK)
            {
                throw exception("Cannot clone GTA taglist", static_cast<gta::result>(r));
            }
            return *this;
        }

        friend class header;
    };

    /**
     * \brief Class for custom input/output.
     *
     * You can define your own custom input/output media by implementing this interface.
     * The seek function is only required if you want to use the out-of-core data access
     * funtions \a header::read_block() or \a header::write_block().
     */
    class custom_io
    {
    public:

        /**
         * \brief               Custom read function.
         * \param buffer        The destionation buffer.
         * \param size          The number of bytes to read.
         * \param error         The error flag.
         *
         * This function must read the given number of bytes into the given buffer.\n
         * Its return value must be the number of bytes successfully read.\n
         * If an error occured, the error flag must be set to true.
         * The function must set errno to indicate the type of error. If the
         * error type is unknown, errno should be set to EIO.
         */
        virtual size_t read(void *buffer GTA_ATTR_UNUSED, size_t size GTA_ATTR_UNUSED, bool *error)
        {
            errno = ENOSYS;
            *error = true;
            return 0;
        }

        /**
         * \brief               Custom write function.
         * \param buffer        The source buffer.
         * \param size          The number of bytes to write.
         * \param error         The error flag.
         *
         * This function must write the given number of bytes from the given buffer.\n
         * Its return value must be the number of bytes successfully written.\n
         * If an error occured, the error flag must be set to true.
         * The function must set errno to indicate the type of error. If the
         * error type is unknown, errno should be set to EIO.
         */
        virtual size_t write(const void *buffer GTA_ATTR_UNUSED, size_t size GTA_ATTR_UNUSED, bool *error)
        {
            errno = ENOSYS;
            *error = true;
            return 0;
        }

        /**
         * \brief               Tell if this object is seekable.
         * \return              Whether this object is seekable.
         *
         * This function must return true if the object is seekable, i.e. if the
         * \a seek function can be used. Otherwise, it must return false.
         */
        virtual bool seekable()
        {
            return false;
        }

        /**
         * \brief               Custom seek function.
         * \param offset        The position offset.
         * \param whence        SEEK_SET or SEEK_CUR.
         * \param error         The error flag.
         *
         * This function must change the position indicator as indicated by the parameters \a
         * offset and \a whence, just like fseeko() and lseek() do. The parameter \a whence
         * can be SEEK_SET or SEEK_CUR (SEEK_END is never used).\n
         * If an error occured, the error flag must be set to true.
         * The function must set errno to indicate the type of error. If the
         * error type is unknown, errno should be set to EIO.
         */
        virtual void seek(intmax_t offset GTA_ATTR_UNUSED, int whence GTA_ATTR_UNUSED, bool *error)
        {
            errno = ENOSYS;
            *error = true;
        }
    };

    /** \cond INTERNAL */
    class istream_io : public custom_io
    {
    private:

        std::istream &_is;

    public:

        istream_io(std::istream &is)
            : _is(is)
        {
        }

        virtual size_t read(void *buffer, size_t size, bool *error)
        {
            try
            {
                _is.read(static_cast<char *>(buffer), size);
            }
            catch (...)
            {
                _is.setstate(std::ios::failbit);
            }
            if (!_is.good())
            {
                errno = EIO;
                *error = true;
            }
            return size;
        }

        virtual bool seekable()
        {
            return (_is.tellg() != static_cast<std::streampos>(-1));
        }

        virtual void seek(intmax_t offset, int whence, bool *error)
        {
            if (offset > std::numeric_limits<std::streamoff>::max())
            {
#ifdef EOVERFLOW
                errno = EOVERFLOW;
#else
                errno = EFBIG;
#endif
                *error = true;
                return;
            }
            try
            {
                _is.seekg(offset, whence == SEEK_SET ? std::ios_base::beg : std::ios_base::cur);
            }
            catch (...)
            {
                _is.setstate(std::ios::failbit);
            }
            if (!_is.good())
            {
                errno = EIO;
                *error = true;
            }
        }
    };
    /** \endcond */

    /** \cond INTERNAL */
    class ostream_io : public custom_io
    {
    private:

        std::ostream &_os;

    public:

        ostream_io(std::ostream &os)
            : _os(os)
        {
        }

        virtual size_t write(const void *buffer, size_t size, bool *error)
        {
            try
            {
                _os.write(static_cast<const char *>(buffer), size);
            }
            catch (...)
            {
                _os.setstate(std::ios::failbit);
            }
            if (!_os.good())
            {
                errno = EIO;
                *error = true;
            }
            return size;
        }

        virtual bool seekable()
        {
            return (_os.tellp() != static_cast<std::streampos>(-1));
        }

        virtual void seek(intmax_t offset, int whence, bool *error)
        {
            if (offset > std::numeric_limits<std::streamoff>::max())
            {
#ifdef EOVERFLOW
                errno = EOVERFLOW;
#else
                errno = EFBIG;
#endif
                *error = true;
                return;
            }
            try
            {
                _os.seekp(offset, whence == SEEK_SET ? std::ios_base::beg : std::ios_base::cur);
            }
            catch (...)
            {
                _os.setstate(std::ios::failbit);
            }
            if (!_os.good())
            {
                errno = EIO;
                *error = true;
            }
        }
    };
    /** \endcond */

    /** \cond INTERNAL */
    inline size_t read_custom_io(intptr_t userdata, void *buffer, size_t size, int *error)
    {
        custom_io *io = reinterpret_cast<custom_io *>(userdata);
        bool tmp_error = false;
        size_t r = io->read(buffer, size, &tmp_error);
        if (tmp_error)
        {
            *error = 1;
        }
        return r;
    }
    /** \endcond */

    /** \cond INTERNAL */
    inline size_t write_custom_io(intptr_t userdata, const void *buffer, size_t size, int *error)
    {
        custom_io *io = reinterpret_cast<custom_io *>(userdata);
        bool tmp_error = false;
        size_t r = io->write(buffer, size, &tmp_error);
        if (tmp_error)
        {
            *error = 1;
        }
        return r;
    }
    /** \endcond */

    /** \cond INTERNAL */
    inline void seek_custom_io(intptr_t userdata, intmax_t offset, int whence, int *error)
    {
        custom_io *io = reinterpret_cast<custom_io *>(userdata);
        bool tmp_error = false;
        io->seek(offset, whence, &tmp_error);
        if (tmp_error)
        {
            *error = 1;
        }
    }
    /** \endcond */

    /**
     * \brief   State for element-based input and output.
     *
     * See gta::header::read_elements() and gta::header::write_elements().
     */
    class io_state
    {
    private:

        gta_io_state_t *_state;

    public:

        io_state()
        {
            gta_result_t r = gta_create_io_state(&_state);
            if (r != GTA_OK)
            {
                throw exception("Cannot initialize GTA i/o state", static_cast<gta::result>(r));
            }
        }

        /** \cond INTERNAL */
        io_state(const io_state &s)
        {
            gta_result_t r = gta_create_io_state(&_state);
            if (r != GTA_OK)
            {
                throw exception("Cannot initialize GTA i/o state", static_cast<gta::result>(r));
            }
            r = gta_clone_io_state(_state, s._state);
            if (r != GTA_OK)
            {
                throw exception("Cannot clone GTA i/o state", static_cast<gta::result>(r));
            }
        }
        /** \endcond */

        ~io_state()
        {
            if (_state)
            {
                gta_destroy_io_state(_state);
            }
        }

        /** \cond INTERNAL */
        io_state &operator=(const io_state &s)
        {
            gta_result_t r = gta_clone_io_state(_state, s._state);
            if (r != GTA_OK)
            {
                throw exception("Cannot clone GTA i/o state", static_cast<gta::result>(r));
            }
            return *this;
        }
        /** \endcond */

        friend class header;
    };

    /**
     * \brief   The GTA header.
     *
     * Each GTA file is described by its header. It stores information about the
     * array elements and the dimensions, and the various tag lists.
     * Using the header, one can access the data in a GTA file, either by
     * managaing the complete data in memory (if it fits), or by using
     * out-of-core data read/write functions. There are also functions that help
     * the application to implement its own data access scheme, if that is necessary.
     */
    class header
    {
    private:

        gta_header_t *_header;
        taglist _global_taglist;
        std::vector<taglist> _dimension_taglists;
        std::vector<taglist> _component_taglists;

        void reset_global_taglist()
        {
            _global_taglist.set(gta_get_global_taglist(_header));
        }

        void reset_component_taglists()
        {
            _component_taglists.resize(gta_get_components(_header), taglist());
            for (uintmax_t i = 0; i < _component_taglists.size(); i++)
            {
                _component_taglists[i].set(gta_get_component_taglist(_header, i));
            }
        }

        void reset_dimension_taglists()
        {
            _dimension_taglists.resize(gta_get_dimensions(_header), taglist());
            for (size_t i = 0; i < _dimension_taglists.size(); i++)
            {
                _dimension_taglists[i].set(gta_get_dimension_taglist(_header, i));
            }
        }

        void reset_taglists()
        {
            reset_global_taglist();
            reset_component_taglists();
            reset_dimension_taglists();
        }

    public:

        /**
         * \name Constructor / Destructor & Co.
         */

        /*@{*/

        /**
         * \brief       Constructor.
         */
        header()
        {
            gta_result_t r = gta_create_header(&_header);
            if (r != GTA_OK)
            {
                throw exception("Cannot initialize GTA header", static_cast<gta::result>(r));
            }
            reset_taglists();
        }

        /**
         * \brief       Copy constructor.
         * \param hdr   The header to copy.
         */
        header(const header &hdr)
        {
            gta_result_t r;
            r = gta_create_header(&_header);
            if (r != GTA_OK)
            {
                throw exception("Cannot initialize GTA header", static_cast<gta::result>(r));
            }
            r = gta_clone_header(_header, hdr._header);
            if (r != GTA_OK)
            {
                throw exception("Cannot clone GTA header", static_cast<gta::result>(r));
            }
            reset_taglists();
        }

        /**
         * \brief       Destructor.
         */
        ~header()
        {
            if (_header)
            {
                gta_destroy_header(_header);
            }
        }

        /**
         * \brief       Assignment operator.
         * \param hdr   The header to copy.
         */
        const header &operator=(const header &hdr)
        {
            gta_result_t r = gta_clone_header(_header, hdr._header);
            if (r != GTA_OK)
            {
                throw exception("Cannot clone GTA header", static_cast<gta::result>(r));
            }
            reset_taglists();
            return *this;
        }

        /*@}*/

        /**
         * \name Read and Write a Header
         */

        /*@{*/

        /**
         * \brief       Read a header.
         * \param io    Custom input object.
         */
        void read_from(custom_io &io)
        {
            gta_result_t r = gta_read_header(_header, read_custom_io, reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot read GTA header", static_cast<gta::result>(r));
            }
            reset_taglists();
        }

        /**
         * \brief       Read a header.
         * \param is    Input stream.
         */
        void read_from(std::istream &is)
        {
            istream_io io(is);
            gta_result_t r = gta_read_header(_header, read_custom_io, reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot read GTA header", static_cast<gta::result>(r));
            }
            reset_taglists();
        }

        /**
         * \brief       Read a header.
         * \param f     Input C stream.
         */
        void read_from(FILE *f)
        {
            gta_result_t r = gta_read_header_from_stream(_header, f);
            if (r != GTA_OK)
            {
                throw exception("Cannot read GTA header", static_cast<gta::result>(r));
            }
            reset_taglists();
        }

        /**
         * \brief       Read a header.
         * \param fd    Input file descriptor.
         */
        void read_from(int fd)
        {
            gta_result_t r = gta_read_header_from_fd(_header, fd);
            if (r != GTA_OK)
            {
                throw exception("Cannot read GTA header", static_cast<gta::result>(r));
            }
            reset_taglists();
        }

        /**
         * \brief       Write a header.
         * \param io    Custom output object.
         */
        void write_to(custom_io &io) const
        {
            gta_result_t r = gta_write_header(_header, write_custom_io, reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot write GTA header", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief       Write a header.
         * \param os    Output stream.
         */
        void write_to(std::ostream &os) const
        {
            ostream_io io(os);
            gta_result_t r = gta_write_header(_header, write_custom_io, reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot write GTA header", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief       Write a header.
         * \param f     Output C stream.
         */
        void write_to(FILE *f) const
        {
            gta_result_t r = gta_write_header_to_stream(_header, f);
            if (r != GTA_OK)
            {
                throw exception("Cannot write GTA header", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief       Write a header.
         * \param fd    Output file descriptor.
         */
        void write_to(int fd) const
        {
            gta_result_t r = gta_write_header_to_fd(_header, fd);
            if (r != GTA_OK)
            {
                throw exception("Cannot write GTA header", static_cast<gta::result>(r));
            }
        }

        /*@}*/

        /**
         * \name Access Header Information
         */

        /*@{*/

        /**
         * \brief       Get the global tag list.
         * \return      The global tag list.
         */
        const taglist &global_taglist() const
        {
            return _global_taglist;
        }

        /**
         * \brief       Get the global tag list.
         * \return      The global tag list.
         */
        taglist &global_taglist()
        {
            return _global_taglist;
        }

        /**
         * \brief       Get the element size.
         * \return      The size of an array element.
         */
        uintmax_t element_size() const
        {
            return gta_get_element_size(_header);
        }

        /**
         * \brief       Get the number of components.
         * \return      The number of components.
         */
        uintmax_t components() const
        {
            return gta_get_components(_header);
        }

        /**
         * \brief       Get the component type.
         * \param i     The component index.
         * \return      The type of the component.
         */
        type component_type(uintmax_t i) const
        {
            return static_cast<type>(gta_get_component_type(_header, i));
        }

        /**
         * \brief       Get the component size.
         * \param i     The component index.
         * \return      The size of the component.
         */
        uintmax_t component_size(uintmax_t i) const
        {
            return gta_get_component_size(_header, i);
        }

        /**
         * \brief       Get the component tag list.
         * \param i     The component index.
         * \return      The tag list of the component.
         */
        const taglist &component_taglist(uintmax_t i) const
        {
            return _component_taglists[i];
        }

        /**
         * \brief       Get the component tag list.
         * \param i     The component index.
         * \return      The tag list of the component.
         */
        taglist &component_taglist(uintmax_t i)
        {
            return _component_taglists[i];
        }

        /**
         * \brief       Get the number of dimensions.
         * \return      The number of dimensions.
         */
        uintmax_t dimensions() const
        {
            return gta_get_dimensions(_header);
        }

        /**
         * \brief       Get the size in a dimension.
         * \param i     The dimension index.
         * \return      The size in the dimension.
         */
        uintmax_t dimension_size(uintmax_t i) const
        {
            return gta_get_dimension_size(_header, i);
        }

        /**
         * \brief       Get the dimension tag list.
         * \param i     The dimension index.
         * \return      The tag list of the dimension.
         */
        const taglist &dimension_taglist(uintmax_t i) const
        {
            return _dimension_taglists[i];
        }

        /**
         * \brief       Get the dimension tag list.
         * \param i     The dimension index.
         * \return      The tag list of the dimension.
         */
        taglist &dimension_taglist(uintmax_t i)
        {
            return _dimension_taglists[i];
        }

        /**
         * \brief       Get the total number of elements in the array.
         * \return      The total number of elements in the array.
         */
        uintmax_t elements() const
        {
            return gta_get_elements(_header);
        }

        /**
         * \brief       Get the total size of the array.
         * \return      The size (in bytes) of the complete array.
         */
        uintmax_t data_size() const
        {
            return gta_get_data_size(_header);
        }

        /**
         * \brief               Get the compression.
         * \return              The compression type.
         *
         * Gets the compression type for the header and data.\n
         * Compression is deprecated so the return value should always be gta::none,
         * unless you read legacy files.
         * This function will be removed in a future version.
         */
        gta::compression compression() const
        {
            return static_cast<gta::compression>(gta_get_compression(_header));
        }

        /**
         * \brief               Set the compression.
         * \param compression   The compression type.
         *
         * Sets the compression type for writing the header and data.
         * Compression is deprecated and this function actually does nothing.
         * This function will be removed in a future version.
         */
        void set_compression(gta::compression compression)
        {
            gta_set_compression(_header, static_cast<gta_compression_t>(compression));
        }

        /*@}*/

        /**
         * \name        Define an Array
         */

        /*@{*/

        /**
         * \brief        Set the components of an array element.
         * \param n      The number of components.
         * \param types  The types of the \a n components.
         * \param sizes  NULL, or the sizes of the components that have type \a gta::blob.
         *
         * Set the components of the array elements.\n
         * The \a sizes parameter can be NULL if no components have the type \a gta::blob.
         * Otherwise, it must point to a list that contains the sizes of these components (and only
         * these components). For example, if there are five components, but only two have the type
         * \a gta::blob, then the \a sizes list must contain two size values.\n
         * All components will initially have an empty tag list.\n
         */
        void set_components(uintmax_t n, const type *types, const uintmax_t *sizes = NULL)
        {
            gta_result_t r = gta_set_components(_header, n, reinterpret_cast<const gta_type_t *>(types), sizes);
            if (r != GTA_OK)
            {
                throw exception("Cannot set GTA components", static_cast<gta::result>(r));
            }
            reset_component_taglists();
        }

        /**
         * \brief       Set the components of an array element (variant for elements with a single component).
         * \param type  The type of the component.
         * \param size  The size of the component, in case the type is \a gta::blob.
         */
        void set_components(type type, uintmax_t size = 0)
        {
            gta::type types[] = { type };
            uintmax_t sizes[] = { size };
            gta_result_t r = gta_set_components(_header, 1, reinterpret_cast<gta_type_t *>(types), sizes);
            if (r != GTA_OK)
            {
                throw exception("Cannot set GTA components", static_cast<gta::result>(r));
            }
            reset_component_taglists();
        }

        /**
         * \brief       Set the components of an array element (variant for elements with two components).
         * \param type0 The type of the first component.
         * \param type1 The type of the second component.
         * \param size0 The size of the first component, in case its type is \a gta::blob.
         * \param size1 The size of the second component, in case its type is \a gta::blob.
         */
        void set_components(type type0, type type1,
                uintmax_t size0 = 0, uintmax_t size1 = 0)
        {
            type types[] = { type0, type1 };
            uintmax_t sizes[] = { size0, size1 };
            gta_result_t r = gta_set_components(_header, 2, reinterpret_cast<gta_type_t *>(types), sizes);
            if (r != GTA_OK)
            {
                throw exception("Cannot set GTA components", static_cast<gta::result>(r));
            }
            reset_component_taglists();
        }

        /**
         * \brief       Set the components of an array element (variant for elements with three components).
         * \param type0 The type of the first component.
         * \param type1 The type of the second component.
         * \param type2 The type of the third component.
         * \param size0 The size of the first component, in case its type is \a gta::blob.
         * \param size1 The size of the second component, in case its type is \a gta::blob.
         * \param size2 The size of the third component, in case its type is \a gta::blob.
         */
        void set_components(type type0, type type1, type type2,
                uintmax_t size0 = 0, uintmax_t size1 = 0, uintmax_t size2 = 0)
        {
            type types[] = { type0, type1, type2 };
            uintmax_t sizes[] = { size0, size1, size2 };
            gta_result_t r = gta_set_components(_header, 3, reinterpret_cast<gta_type_t *>(types), sizes);
            if (r != GTA_OK)
            {
                throw exception("Cannot set GTA components", static_cast<gta::result>(r));
            }
            reset_component_taglists();
        }

        /**
         * \brief       Set the components of an array element (variant for elements with four components).
         * \param type0 The type of the first component.
         * \param type1 The type of the second component.
         * \param type2 The type of the third component.
         * \param type3 The type of the fourth component.
         * \param size0 The size of the first component, in case its type is \a gta::blob.
         * \param size1 The size of the second component, in case its type is \a gta::blob.
         * \param size2 The size of the third component, in case its type is \a gta::blob.
         * \param size3 The size of the fourth component, in case its type is \a gta::blob.
         */
        void set_components(type type0, type type1, type type2, type type3,
                uintmax_t size0 = 0, uintmax_t size1 = 0, uintmax_t size2 = 0, uintmax_t size3 = 0)
        {
            type types[] = { type0, type1, type2, type3 };
            uintmax_t sizes[] = { size0, size1, size2, size3 };
            gta_result_t r = gta_set_components(_header, 4, reinterpret_cast<gta_type_t *>(types), sizes);
            if (r != GTA_OK)
            {
                throw exception("Cannot set GTA components", static_cast<gta::result>(r));
            }
            reset_component_taglists();
        }

        /**
         * \brief       Set the dimensions.
         * \param n     The number of dimensions.
         * \param sizes The array sizes in each of the \n dimensions.
         *
         * Sets the array dimensions.\n
         * All dimensions will initially have an empty tag list.
         */
        void set_dimensions(uintmax_t n, const uintmax_t *sizes)
        {
            gta_result_t r = gta_set_dimensions(_header, n, sizes);
            if (r != GTA_OK)
            {
                throw exception("Cannot set GTA dimensions", static_cast<gta::result>(r));
            }
            reset_dimension_taglists();
        }

        /**
         * \brief       Set the dimensions (variant for one-dimensional arrays).
         * \param size  The size in the single dimension.
         */
        void set_dimensions(uintmax_t size)
        {
            uintmax_t sizes[] = { size };
            gta_result_t r = gta_set_dimensions(_header, 1, sizes);
            if (r != GTA_OK)
            {
                throw exception("Cannot set GTA dimensions", static_cast<gta::result>(r));
            }
            reset_dimension_taglists();
        }

        /**
         * \brief       Set the dimensions (variant for two-dimensional arrays).
         * \param size0 The size in the first dimension.
         * \param size1 The size in the second dimension.
         */
        void set_dimensions(uintmax_t size0, uintmax_t size1)
        {
            uintmax_t sizes[] = { size0, size1 };
            gta_result_t r = gta_set_dimensions(_header, 2, sizes);
            if (r != GTA_OK)
            {
                throw exception("Cannot set GTA dimensions", static_cast<gta::result>(r));
            }
            reset_dimension_taglists();
        }

        /**
         * \brief       Set the dimensions (variant for three-dimensional arrays).
         * \param size0 The size in the first dimension.
         * \param size1 The size in the second dimension.
         * \param size2 The size in the third dimension.
         */
        void set_dimensions(uintmax_t size0, uintmax_t size1, uintmax_t size2)
        {
            uintmax_t sizes[] = { size0, size1, size2 };
            gta_result_t r = gta_set_dimensions(_header, 3, sizes);
            if (r != GTA_OK)
            {
                throw exception("Cannot set GTA dimensions", static_cast<gta::result>(r));
            }
            reset_dimension_taglists();
        }

        /**
         * \brief       Set the dimensions (variant for four-dimensional arrays).
         * \param size0 The size in the first dimension.
         * \param size1 The size in the second dimension.
         * \param size2 The size in the third dimension.
         * \param size3 The size in the fourth dimension.
         */
        void set_dimensions(uintmax_t size0, uintmax_t size1, uintmax_t size2, uintmax_t size3)
        {
            uintmax_t sizes[] = { size0, size1, size2, size3 };
            gta_result_t r = gta_set_dimensions(_header, 4, sizes);
            if (r != GTA_OK)
            {
                throw exception("Cannot set GTA dimensions", static_cast<gta::result>(r));
            }
            reset_dimension_taglists();
        }

        /*@}*/

        /**
         * \name Read and Write Complete Arrays
         */

        /*@{*/

        /**
         * \brief       Read the complete data.
         * \param io    Custom input object.
         * \param data  Data buffer.
         *
         * Reads the complete data into the given buffer. The buffer must be large enough.
         */
        void read_data(custom_io &io, void *data) const
        {
            gta_result_t r = gta_read_data(_header, data, read_custom_io, reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot read GTA data", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief       Read the complete data.
         * \param is    Input stream.
         * \param data  Data buffer.
         *
         * Reads the complete data into the given buffer. The buffer must be large enough.
         */
        void read_data(std::istream &is, void *data) const
        {
            istream_io io(is);
            gta_result_t r = gta_read_data(_header, data, read_custom_io, reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot read GTA data", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief       Read the complete data.
         * \param f     Input C stream.
         * \param data  Data buffer.
         *
         * Reads the complete data into the given buffer. The buffer must be large enough.
         */
        void read_data(FILE *f, void *data) const
        {
            gta_result_t r = gta_read_data_from_stream(_header, data, f);
            if (r != GTA_OK)
            {
                throw exception("Cannot read GTA data", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief       Read the complete data.
         * \param fd    Input file descriptor.
         * \param data  Data buffer.
         *
         * Reads the complete data into the given buffer. The buffer must be large enough.
         */
        void read_data(int fd, void *data) const
        {
            gta_result_t r = gta_read_data_from_fd(_header, data, fd);
            if (r != GTA_OK)
            {
                throw exception("Cannot read GTA data", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief       Skip the complete data.
         * \param io    Custom input object.
         *
         * Skips the complete data, so that the next GTA header can be read.
         */
        void skip_data(custom_io &io) const
        {
            gta_result_t r = gta_skip_data(_header, read_custom_io,
                    (io.seekable() ? seek_custom_io : NULL),
                    reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot skip GTA data", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief       Skip the complete data.
         * \param is    Input stream.
         *
         * Skips the complete data, so that the next GTA header can be read.
         */
        void skip_data(std::istream &is) const
        {
            istream_io io(is);
            gta_result_t r = gta_skip_data(_header, read_custom_io,
                    (io.seekable() ? seek_custom_io : NULL),
                    reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot skip GTA data", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief       Skip the complete data.
         * \param f     Input C stream.
         *
         * Skips the complete data, so that the next GTA header can be read.
         */
        void skip_data(FILE *f) const
        {
            gta_result_t r = gta_skip_data_from_stream(_header, f);
            if (r != GTA_OK)
            {
                throw exception("Cannot skip GTA data", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief       Skip the complete data.
         * \param fd    Input file descriptor.
         *
         * Skips the complete data, so that the next GTA header can be read.
         */
        void skip_data(int fd) const
        {
            gta_result_t r = gta_skip_data_from_fd(_header, fd);
            if (r != GTA_OK)
            {
                throw exception("Cannot skip GTA data", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief       Write the complete data.
         * \param io    Custom output object.
         * \param data  Data buffer.
         */
        void write_data(custom_io &io, const void *data) const
        {
            gta_result_t r = gta_write_data(_header, data, write_custom_io, reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot write GTA data", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief       Write the complete data.
         * \param os    Output stream.
         * \param data  Data buffer.
         */
        void write_data(std::ostream &os, const void *data) const
        {
            ostream_io io(os);
            gta_result_t r = gta_write_data(_header, data, write_custom_io, reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot write GTA data", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief       Write the complete data.
         * \param f     Output C stream.
         * \param data  Data buffer.
         */
        void write_data(FILE *f, const void *data) const
        {
            gta_result_t r = gta_write_data_to_stream(_header, data, f);
            if (r != GTA_OK)
            {
                throw exception("Cannot write GTA data", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief       Write the complete data.
         * \param fd    Output file descriptor.
         * \param data  Data buffer.
         */
        void write_data(int fd, const void *data) const
        {
            gta_result_t r = gta_write_data_to_fd(_header, data, fd);
            if (r != GTA_OK)
            {
                throw exception("Cannot write GTA data", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief               Copy the complete data.
         * \param read_io       Custom input object.
         * \param write_header  Output header.
         * \param write_io      Custom output object.
         */
        void copy_data(custom_io &read_io, const header &write_header, custom_io &write_io) const
        {
            gta_result_t r = gta_copy_data(_header,
                    read_custom_io, reinterpret_cast<intptr_t>(&read_io),
                    write_header._header,
                    write_custom_io, reinterpret_cast<intptr_t>(&write_io));
            if (r != GTA_OK)
            {
                throw exception("Cannot copy GTA data", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief               Copy the complete data.
         * \param is            Input stream.
         * \param write_header  Output header.
         * \param os            Output stream.
         */
        void copy_data(std::istream &is, const header &write_header, std::ostream &os) const
        {
            istream_io read_io(is);
            ostream_io write_io(os);
            gta_result_t r = gta_copy_data(_header,
                    read_custom_io, reinterpret_cast<intptr_t>(&read_io),
                    write_header._header,
                    write_custom_io, reinterpret_cast<intptr_t>(&write_io));
            if (r != GTA_OK)
            {
                throw exception("Cannot copy GTA data", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief               Copy the complete data.
         * \param fi            Input C stream.
         * \param write_header  Output header.
         * \param fo            Output C stream.
         */
        void copy_data(FILE *fi, const header &write_header, FILE *fo) const
        {
            gta_result_t r = gta_copy_data_stream(_header, fi, write_header._header, fo);
            if (r != GTA_OK)
            {
                throw exception("Cannot copy GTA data", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief               Copy the complete data.
         * \param fdi           Input file descriptor.
         * \param write_header  Output header.
         * \param fdo           Output file descriptor.
         */
        void copy_data(int fdi, const header &write_header, int fdo) const
        {
            gta_result_t r = gta_copy_data_fd(_header, fdi, write_header._header, fdo);
            if (r != GTA_OK)
            {
                throw exception("Cannot copy GTA data", static_cast<gta::result>(r));
            }
        }

        /*@}*/

        /**
         * \name In-Memory Data Access
         */

        /*@{*/

        /**
         * \brief               Transform a linear index to array indices.
         * \param index         The linear index.
         * \param indices       The array indices.
         */
        void linear_index_to_indices(uintmax_t index, uintmax_t *indices) const
        {
            gta_linear_index_to_indices(_header, index, indices);
        }

        /**
         * \brief               Transform array indices to a linear index.
         * \param indices       The array indices.
         * \return              The linear index.
         */
        uintmax_t indices_to_linear_index(const uintmax_t *indices) const
        {
            return gta_indices_to_linear_index(_header, indices);
        }

        /**
         * \brief               Get an array element.
         * \param data          Data Buffer.
         * \param indices       Indices for each dimension of the array.
         * \return              A pointer to the element.
         */
        const void *element(const void *data, const uintmax_t *indices) const
        {
            return gta_get_element_const(_header, data, indices);
        }

        /**
         * \brief               Get an array element.
         * \param data          Data Buffer.
         * \param indices       Indices for each dimension of the array.
         * \return              A pointer to the element.
         */
        void *element(void *data, const uintmax_t *indices) const
        {
            return gta_get_element(_header, data, indices);
        }

        /**
         * \brief               Get an array element via a linear index.
         * \param data          Data Buffer.
         * \param index         Index of the element.
         * \return              A pointer to the element.
         *
         * This function not only works for one-dimensional arrays in the obvious way,
         * but also for multidimensional arrays by using \a index as a linear index to
         * the array data.
         */
        const void *element(const void *data, uintmax_t index) const
        {
            return gta_get_element_linear_const(_header, data, index);
        }

        /**
         * \brief               Get an array element via a linear index.
         * \param data          Data Buffer.
         * \param index         Index of the element.
         * \return              A pointer to the element.
         *
         * This function not only works for one-dimensional arrays in the obvious way,
         * but also for multidimensional arrays by using \a index as a linear index to
         * the array data.
         */
        void *element(void *data, uintmax_t index) const
        {
            return gta_get_element_linear(_header, data, index);
        }

        /**
         * \brief               Get an array element (variant for two-dimensional arrays).
         * \param data          Data Buffer.
         * \param index0        Index of the element in the first dimension.
         * \param index1        Index of the element in the second dimension.
         * \return              A pointer to the element.
         */
        const void *element(const void *data, uintmax_t index0, uintmax_t index1) const
        {
            uintmax_t indices[] = { index0, index1 };
            return gta_get_element_const(_header, data, indices);
        }

        /**
         * \brief               Get an array element (variant for two-dimensional arrays).
         * \param data          Data Buffer.
         * \param index0        Index of the element in the first dimension.
         * \param index1        Index of the element in the second dimension.
         * \return              A pointer to the element.
         */
        void *element(void *data, uintmax_t index0, uintmax_t index1) const
        {
            uintmax_t indices[] = { index0, index1 };
            return gta_get_element(_header, data, indices);
        }

        /**
         * \brief               Get an array element (variant for three-dimensional arrays).
         * \param data          Data Buffer.
         * \param index0        Index of the element in the first dimension.
         * \param index1        Index of the element in the second dimension.
         * \param index2        Index of the element in the third dimension.
         * \return              A pointer to the element.
         */
        const void *element(const void *data, uintmax_t index0, uintmax_t index1, uintmax_t index2) const
        {
            uintmax_t indices[] = { index0, index1, index2 };
            return gta_get_element_const(_header, data, indices);
        }

        /**
         * \brief               Get an array element (variant for three-dimensional arrays).
         * \param data          Data Buffer.
         * \param index0        Index of the element in the first dimension.
         * \param index1        Index of the element in the second dimension.
         * \param index2        Index of the element in the third dimension.
         * \return              A pointer to the element.
         */
        void *element(void *data, uintmax_t index0, uintmax_t index1, uintmax_t index2) const
        {
            uintmax_t indices[] = { index0, index1, index2 };
            return gta_get_element(_header, data, indices);
        }

        /**
         * \brief               Get an array element (variant for four-dimensional arrays).
         * \param data          Data Buffer.
         * \param index0        Index of the element in the first dimension.
         * \param index1        Index of the element in the second dimension.
         * \param index2        Index of the element in the third dimension.
         * \param index3        Index of the element in the fourth dimension.
         * \return              A pointer to the element.
         */
        const void *element(const void *data, uintmax_t index0, uintmax_t index1, uintmax_t index2, uintmax_t index3) const
        {
            uintmax_t indices[] = { index0, index1, index2, index3 };
            return gta_get_element_const(_header, data, indices);
        }

        /**
         * \brief               Get an array element (variant for four-dimensional arrays).
         * \param data          Data Buffer.
         * \param index0        Index of the element in the first dimension.
         * \param index1        Index of the element in the second dimension.
         * \param index2        Index of the element in the third dimension.
         * \param index3        Index of the element in the fourth dimension.
         * \return              A pointer to the element.
         */
        void *element(void *data, uintmax_t index0, uintmax_t index1, uintmax_t index2, uintmax_t index3) const
        {
            uintmax_t indices[] = { index0, index1, index2, index3 };
            return gta_get_element(_header, data, indices);
        }

        /**
         * \brief               Get a component of an array element.
         * \param element       Element.
         * \param i             Component index.
         * \return              A pointer to the component.
         */
        const void *component(const void *element, uintmax_t i) const
        {
            return gta_get_component_const(_header, element, i);
        }

        /**
         * \brief               Get a component of an array element.
         * \param element       Element.
         * \param i             Component index.
         * \return              A pointer to the component.
         */
        void *component(void *element, uintmax_t i) const
        {
            return gta_get_component(_header, element, i);
        }

        /*@}*/

        /**
         * \name Read and Write Array Elements
         *
         * These functions are intended to be used for filtering a complete array on a per-element basis.
         * They read or write a given number of elements, and it is expected that they are used
         * repeatedly until all elements of an array have been read or written.
         * Theses function work for all GTAs, and the input and output streams
         * do not need to be seekable.
         *
         * Element-based input/output needs a state object gta::io_state. The same state object must be
         * used until all elements are read or written, or until an error occurs.
         */

        /*@{*/

        /**
         * \brief               Read array elements.
         * \param state         The input/output state.
         * \param io            Custom input object.
         * \param n             The number of elements to read.
         * \param buf           The buffer for the elements.
         *
         * Reads the given number of elements into the given buffer, which must be large enough.
         */
        void read_elements(io_state &state, custom_io &io, uintmax_t n, void *buf) const
        {
            gta_result_t r = gta_read_elements(_header, state._state, n, buf, read_custom_io, reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot read GTA data elements", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief               Read array elements.
         * \param state         The input/output state.
         * \param is            Input stream.
         * \param n             The number of elements to read.
         * \param buf           The buffer for the elements.
         *
         * Reads the given number of elements into the given buffer, which must be large enough.
         */
        void read_elements(io_state &state, std::istream &is, uintmax_t n, void *buf) const
        {
            istream_io io(is);
            gta_result_t r = gta_read_elements(_header, state._state, n, buf, read_custom_io, reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot read GTA data elements", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief               Read array elements.
         * \param state         The input/output state.
         * \param f             Input stream.
         * \param n             The number of elements to read.
         * \param buf           The buffer for the elements.
         *
         * Reads the given number of elements into the given buffer, which must be large enough.
         */
        void read_elements(io_state &state, FILE *f, uintmax_t n, void *buf) const
        {
            gta_result_t r = gta_read_elements_from_stream(_header, state._state, n, buf, f);
            if (r != GTA_OK)
            {
                throw exception("Cannot read GTA data elements", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief               Read array elements.
         * \param state         The input/output state.
         * \param fd            Input file descriptor.
         * \param n             The number of elements to read.
         * \param buf           The buffer for the elements.
         *
         * Reads the given number of elements into the given buffer, which must be large enough.
         */
        void read_elements(io_state &state, int fd, uintmax_t n, void *buf) const
        {
            gta_result_t r = gta_read_elements_from_fd(_header, state._state, n, buf, fd);
            if (r != GTA_OK)
            {
                throw exception("Cannot read GTA data elements", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief               Write array elements.
         * \param state         The input/output state.
         * \param io            Custom output object.
         * \param n             The number of elements to write.
         * \param buf           The buffer for the elements.
         *
         * Writes the given number of elements from the given buffer.
         */
        void write_elements(io_state &state, custom_io &io, uintmax_t n, const void *buf) const
        {
            gta_result_t r = gta_write_elements(_header, state._state, n, buf, write_custom_io, reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot write GTA data elements", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief               Write array elements.
         * \param state         The input/output state.
         * \param os            Output stream.
         * \param n             The number of elements to write.
         * \param buf           The buffer for the elements.
         *
         * Writes the given number of elements from the given buffer.
         */
        void write_elements(io_state &state, std::ostream &os, uintmax_t n, const void *buf) const
        {
            ostream_io io(os);
            gta_result_t r = gta_write_elements(_header, state._state, n, buf, write_custom_io, reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot write GTA data elements", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief               Write array elements.
         * \param state         The input/output state.
         * \param f             Output stream.
         * \param n             The number of elements to write.
         * \param buf           The buffer for the elements.
         *
         * Writes the given number of elements from the given buffer.
         */
        void write_elements(io_state &state, FILE *f, uintmax_t n, const void *buf) const
        {
            gta_result_t r = gta_write_elements_to_stream(_header, state._state, n, buf, f);
            if (r != GTA_OK)
            {
                throw exception("Cannot write GTA data elements", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief               Write array elements.
         * \param state         The input/output state.
         * \param fd            Output file descriptor.
         * \param n             The number of elements to write.
         * \param buf           The buffer for the elements.
         *
         * Writes the given number of elements from the given buffer.
         */
        void write_elements(io_state &state, int fd, uintmax_t n, const void *buf) const
        {
            gta_result_t r = gta_write_elements_to_fd(_header, state._state, n, buf, fd);
            if (r != GTA_OK)
            {
                throw exception("Cannot write GTA data elements", static_cast<gta::result>(r));
            }
        }

        /*@}*/

        /**
         * \name Read and Write Array Blocks
         *
         * These functions can only be used if the input/output is seekable.\n
         * They are suitable for applications that do not want to store the complete array data in
         * memory.\n
         * A block is given by the lowest and highest element coordinates in each dimension.
         * For example, for a 2D array from which we want a rectangle of 20x10 elements starting at
         * element (5,3), we would store the values (5,3) in \a lower_coordinates and (24, 12) in
         * \a higher_coordinates.
         */

        /*@{*/

        /**
         * \brief                       Read an array block.
         * \param io                    Custom input object.
         * \param data_offset           Offset of the first data byte.
         * \param lower_coordinates     Coordinates of the lower corner element of the block.
         * \param higher_coordinates    Coordinates of the higher corner element of the block.
         * \param block                 Block buffer.
         *
         * Reads the given array block and copies it to the given block buffer, which must be large enough.\n
         * This function modifies the file position indicator of the input.
         */
        void read_block(custom_io &io, uintmax_t data_offset,
                const uintmax_t *lower_coordinates, const uintmax_t *higher_coordinates,
                void *block) const
        {
            gta_result_t r = gta_read_block(_header, data_offset,
                    lower_coordinates, higher_coordinates, block,
                    read_custom_io, seek_custom_io, reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot read GTA data block", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief                       Read an array block.
         * \param is                    Input stream.
         * \param data_offset           Offset of the first data byte.
         * \param lower_coordinates     Coordinates of the lower corner element of the block.
         * \param higher_coordinates    Coordinates of the higher corner element of the block.
         * \param block                 Block buffer.
         *
         * Reads the given array block and copies it to the given block buffer, which must be large enough.\n
         * This function modifies the file position indicator of the input.
         */
        void read_block(std::istream &is, uintmax_t data_offset,
                const uintmax_t *lower_coordinates, const uintmax_t *higher_coordinates,
                void *block) const
        {
            istream_io io(is);
            gta_result_t r = gta_read_block(_header, data_offset,
                    lower_coordinates, higher_coordinates, block,
                    read_custom_io, seek_custom_io, reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot read GTA data block", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief                       Read an array block.
         * \param f                     Input C stream.
         * \param data_offset           Offset of the first data byte.
         * \param lower_coordinates     Coordinates of the lower corner element of the block.
         * \param higher_coordinates    Coordinates of the higher corner element of the block.
         * \param block                 Block buffer.
         *
         * Reads the given array block and copies it to the given block buffer, which must be large enough.\n
         * This function modifies the file position indicator of the input.
         */
        void read_block(FILE *f, uintmax_t data_offset,
                const uintmax_t *lower_coordinates, const uintmax_t *higher_coordinates,
                void *block) const
        {
            gta_result_t r = gta_read_block_from_stream(_header, data_offset,
                    lower_coordinates, higher_coordinates, block, f);
            if (r != GTA_OK)
            {
                throw exception("Cannot read GTA data block", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief                       Read an array block.
         * \param fd                    Input file descriptor.
         * \param data_offset           Offset of the first data byte.
         * \param lower_coordinates     Coordinates of the lower corner element of the block.
         * \param higher_coordinates    Coordinates of the higher corner element of the block.
         * \param block                 Block buffer.
         *
         * Reads the given array block and copies it to the given block buffer, which must be large enough.\n
         * This function modifies the file position indicator of the input.
         */
        void read_block(int fd, uintmax_t data_offset,
                const uintmax_t *lower_coordinates, const uintmax_t *higher_coordinates,
                void *block) const
        {
            gta_result_t r = gta_read_block_from_fd(_header, data_offset,
                    lower_coordinates, higher_coordinates, block, fd);
            if (r != GTA_OK)
            {
                throw exception("Cannot read GTA data block", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief                       Write an array block.
         * \param io                    Custom output object.
         * \param data_offset           Offset of the first data byte.
         * \param lower_coordinates     Coordinates of the lower corner element of the block.
         * \param higher_coordinates    Coordinates of the higher corner element of the block.
         * \param block                 Block buffer.
         *
         * This function modifies the file position indicator of the output.
         */
        void write_block(custom_io &io, uintmax_t data_offset,
                const uintmax_t *lower_coordinates, const uintmax_t *higher_coordinates,
                const void *block) const
        {
            gta_result_t r = gta_write_block(_header, data_offset,
                    lower_coordinates, higher_coordinates, block,
                    write_custom_io, seek_custom_io, reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot write GTA data block", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief                       Write an array block.
         * \param os                    Output stream.
         * \param data_offset           Offset of the first data byte.
         * \param lower_coordinates     Coordinates of the lower corner element of the block.
         * \param higher_coordinates    Coordinates of the higher corner element of the block.
         * \param block                 Block buffer.
         *
         * This function modifies the file position indicator of the output.
         */
        void write_block(std::ostream &os, uintmax_t data_offset,
                const uintmax_t *lower_coordinates, const uintmax_t *higher_coordinates,
                const void *block) const
        {
            ostream_io io(os);
            gta_result_t r = gta_write_block(_header, data_offset,
                    lower_coordinates, higher_coordinates, block,
                    write_custom_io, seek_custom_io, reinterpret_cast<intptr_t>(&io));
            if (r != GTA_OK)
            {
                throw exception("Cannot write GTA data block", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief                       Write an array block.
         * \param f                     Output C stream.
         * \param data_offset           Offset of the first data byte.
         * \param lower_coordinates     Coordinates of the lower corner element of the block.
         * \param higher_coordinates    Coordinates of the higher corner element of the block.
         * \param block                 Block buffer.
         *
         * This function modifies the file position indicator of the output.
         */
        void write_block(FILE *f, uintmax_t data_offset,
                const uintmax_t *lower_coordinates, const uintmax_t *higher_coordinates,
                const void *block) const
        {
            gta_result_t r = gta_write_block_to_stream(_header, data_offset,
                    lower_coordinates, higher_coordinates, block, f);
            if (r != GTA_OK)
            {
                throw exception("Cannot write GTA data block", static_cast<gta::result>(r));
            }
        }

        /**
         * \brief                       Write an array block.
         * \param fd                    Output file descriptor.
         * \param data_offset           Offset of the first data byte.
         * \param lower_coordinates     Coordinates of the lower corner element of the block.
         * \param higher_coordinates    Coordinates of the higher corner element of the block.
         * \param block                 Block buffer.
         *
         * This function modifies the file position indicator of the output.
         */
        void write_block(int fd, uintmax_t data_offset,
                const uintmax_t *lower_coordinates, const uintmax_t *higher_coordinates,
                const void *block) const
        {
            gta_result_t r = gta_write_block_to_fd(_header, data_offset,
                    lower_coordinates, higher_coordinates, block, fd);
            if (r != GTA_OK)
            {
                throw exception("Cannot write GTA data block", static_cast<gta::result>(r));
            }
        }

        /*@}*/
    };


    /**
     * \name Version information
     */

    /*@{*/

    /**
     * \brief   Get the version string.
     * \return  The version string "MAJOR.MINOR.PATCH"
     */
    inline const char *version()
    {
        return gta_version(NULL, NULL, NULL);
    }

    /**
     * \brief   Get the major version number.
     * \return  The major version number.
     */
    inline int version_major()
    {
        int major;
        gta_version(&major, NULL, NULL);
        return major;
    }

    /**
     * \brief   Get the minor version number.
     * \return  The minor version number.
     */
    inline int version_minor()
    {
        int minor;
        gta_version(NULL, &minor, NULL);
        return minor;
    }

    /**
     * \brief   Get the patch version number.
     * \return  The patch version number.
     */
    inline int version_patch()
    {
        int patch;
        gta_version(NULL, NULL, &patch);
        return patch;
    }

    /*@}*/
}

#ifdef _MSC_VER
#  pragma warning (pop)
#endif

#endif
