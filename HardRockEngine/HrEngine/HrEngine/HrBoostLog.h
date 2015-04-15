/*
*  FILE: boost.log.init.hpp
*  INSTRUCTION: 这个文件用于初始化boost.log
*  DETAIL: 这里重新定义了日志级别和对应的文本内容.
*          文件大小限制等信息被硬编码在cpp文件中，如有需求可以修改。
*/
#ifndef BOOST_LOG_INIT_TAIRAN_HPP
#define BOOST_LOG_INIT_TAIRAN_HPP

#include <iostream>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>

#include <boost/log/sources/logger.hpp>

#include <boost/log/support/date_time.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

using boost::shared_ptr;

enum severity_level
{
	normal,
	notification,
	warning,
	error,
	critical
};

// The formatting logic for the severity level
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
	std::basic_ostream< CharT, TraitsT >& strm, severity_level lvl)
{
	static const char* const str[] =
	{
		"normal",
		"notification",
		"warning",
		"error",
		"critical"
	};
	if (static_cast<std::size_t>(lvl) < (sizeof( str ) / sizeof( *str )))
		strm << str[lvl];
	else
		strm << static_cast<int>(lvl);
	return strm;
}

// Declare attribute keywords
BOOST_LOG_ATTRIBUTE_KEYWORD( _severity, "Severity", severity_level )
BOOST_LOG_ATTRIBUTE_KEYWORD( _timestamp, "TimeStamp", boost::posix_time::ptime )
BOOST_LOG_ATTRIBUTE_KEYWORD( _uptime, "Uptime", attrs::timer::value_type )
BOOST_LOG_ATTRIBUTE_KEYWORD( _scope, "Scope", attrs::named_scope::value_type )

inline void InitLog()
{

}

#endif
