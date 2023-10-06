#ifndef BINLOG_DETAIL_OSTREAM_BUFFER_HPP
#define BINLOG_DETAIL_OSTREAM_BUFFER_HPP

#include <mserialize/string_view.hpp>

#include <array>
#include <cstdint>
#include <ostream>
#include <binlog/binlogexports.h>

namespace binlog {
namespace detail {

/**
 * A faster way to write an ostream.
 *
 * Takes an ostream (the underlying device),
 * and buffers the result of unformatted
 * and formatted write operations locally.
 *
 * Before the local buffer overflows,
 * flushes it to the underlying device.
 *
 * This avoids repeated construction/destruction
 * of stream sentries.
 *
 * The number-to-string operations are
 * more efficient than the equivalent
 * ostream formatted operations.
 */
class OstreamBuffer
{
public:
  HBINLOG_EXPORT explicit OstreamBuffer(std::ostream& out);
  HBINLOG_EXPORT ~OstreamBuffer();

  OstreamBuffer(const OstreamBuffer&) = delete;
  void operator=(const OstreamBuffer&) = delete;

  OstreamBuffer(OstreamBuffer&&) = delete;
  void operator=(OstreamBuffer&&) = delete;

  HBINLOG_EXPORT void put(char c);

  HBINLOG_EXPORT void write(const char* buf, std::size_t size);

  HBINLOG_EXPORT OstreamBuffer& operator<<(bool);
  OstreamBuffer& operator<<(char c) { put(c); return *this; }

  OstreamBuffer& operator<<(std::int8_t   v) { writeSigned(v); return *this; }
  OstreamBuffer& operator<<(std::int16_t  v) { writeSigned(v); return *this; }
  OstreamBuffer& operator<<(std::int32_t  v) { writeSigned(v); return *this; }
  OstreamBuffer& operator<<(std::int64_t  v) { writeSigned(v); return *this; }
  OstreamBuffer& operator<<(std::uint8_t  v) { writeUnsigned(v); return *this; }
  OstreamBuffer& operator<<(std::uint16_t v) { writeUnsigned(v); return *this; }
  OstreamBuffer& operator<<(std::uint32_t v) { writeUnsigned(v); return *this; }
  OstreamBuffer& operator<<(std::uint64_t v) { writeUnsigned(v); return *this; }

  HBINLOG_EXPORT OstreamBuffer& operator<<(double);
  HBINLOG_EXPORT OstreamBuffer& operator<<(long double);

  OstreamBuffer& operator<<(mserialize::string_view str)
  {
    write(str.data(), str.size());
    return *this;
  }

  OstreamBuffer& operator<<(const char* str)
  {
    return *this << mserialize::string_view(str);
  }

  template <std::size_t N>
  OstreamBuffer& operator<<(const char (&array)[N])
  {
    write(array, N-1);
    return *this;
  }

  void flush();

private:
  void writeSigned(std::int64_t);
  void writeUnsigned(std::uint64_t);

  /** @pre n <= _buf.size() */
  void reserve(std::size_t n);

  std::ostream& _out;
  std::array<char, 1024> _buf;
  char* _p;
};

} // namespace detail
} // namespace binlog

#endif // BINLOG_DETAIL_OSTREAM_BUFFER_HPP
