#ifndef BINLOG_TO_STRING_VISITOR_HPP
#define BINLOG_TO_STRING_VISITOR_HPP

#include <binlog/Range.hpp>
#include <binlog/detail/OstreamBuffer.hpp>

#include <mserialize/Visitor.hpp>

#include <cstdint>

namespace binlog {

class PrettyPrinter;

/**
 * Convert serialized values to string.
 *
 * Writes the result to the given stream.
 * Models the mserialize::Visitor concept
 *
 * Usage:
 *
 *    std::ostringstream str;
 *    binlog::detail::OstreamBuffer buf(str);
 *    ToStringVisitor visitor(buf);
 *    mserialize::visit(tag, visitor, istream);
 */
class ToStringVisitor
{
public:
  HBINLOG_EXPORT explicit ToStringVisitor(detail::OstreamBuffer& out, const PrettyPrinter* pp = nullptr);

  // catch all for arithmetic types
  template <typename T>
  void visit(T v)
  {
    comma();
    _out << v;
  }

  HBINLOG_EXPORT void visit(std::int8_t);
  HBINLOG_EXPORT void visit(std::uint8_t);

  HBINLOG_EXPORT bool visit(mserialize::Visitor::SequenceBegin, Range&);
  HBINLOG_EXPORT void visit(mserialize::Visitor::SequenceEnd);

  HBINLOG_EXPORT bool visit(mserialize::Visitor::TupleBegin, const Range&);
  HBINLOG_EXPORT void visit(mserialize::Visitor::TupleEnd);

  bool visit(mserialize::Visitor::VariantBegin, const Range&) { return false; }
  void visit(mserialize::Visitor::VariantEnd) {}
  HBINLOG_EXPORT void visit(mserialize::Visitor::Null);

  HBINLOG_EXPORT void visit(mserialize::Visitor::Enum);

  HBINLOG_EXPORT bool visit(mserialize::Visitor::StructBegin, Range&);
  HBINLOG_EXPORT void visit(mserialize::Visitor::StructEnd);

  HBINLOG_EXPORT void visit(mserialize::Visitor::FieldBegin);
  HBINLOG_EXPORT void visit(mserialize::Visitor::FieldEnd);

  HBINLOG_EXPORT void visit(mserialize::Visitor::RepeatBegin);
  HBINLOG_EXPORT void visit(mserialize::Visitor::RepeatEnd);

private:
  HBINLOG_EXPORT void comma();

  HBINLOG_EXPORT void enterSeq();

  HBINLOG_EXPORT void leaveSeq();

  // In sequences (sequence, tuple, structure fields)
  // add a comma between each element.
  enum class State { Normal, SeqBegin, Seq };

  State _state;
  int _seqDepth;
  bool _emptyStruct;
  detail::OstreamBuffer& _out;
  const PrettyPrinter* _pp;
};

} // namespace binlog

#endif // BINLOG_TO_STRING_VISITOR_HPP
