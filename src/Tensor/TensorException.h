#pragma once

#include <stdexcept>
#include <string>

namespace tens
{

class tensor_rank_error : public std::range_error
{
public:
explicit tensor_rank_error(const std::string& _Message) : range_error(_Message.c_str()) {}
explicit tensor_rank_error(const char *_Message) : range_error(_Message) {}

};

class tensor_dimension_error : public std::range_error
{
public:
explicit tensor_dimension_error(const std::string& _Message) : range_error(_Message.c_str()) {}
explicit tensor_dimension_error(const char *_Message) : range_error(_Message) {}

};

class numeric_range_error : public std::range_error
{
public:
explicit numeric_range_error(const std::string& _Message) : range_error(_Message.c_str()) {}
explicit numeric_range_error(const char *_Message) : range_error(_Message) {}

};


class size_nomatch_error : public std::range_error
{
public:
explicit size_nomatch_error(const std::string& _Message) : range_error(_Message.c_str()) {}
explicit size_nomatch_error(const char *_Message) : range_error(_Message) {}
};

inline void ErrIfNot(bool expr, const std::string & msg)
{
	if (!expr)
		throw std::exception();
}

template <typename ErrType>
inline void ErrIfNot(bool expr, const std::string & msg)
{
	if (!expr)
		throw ErrType(msg);
}



}
 