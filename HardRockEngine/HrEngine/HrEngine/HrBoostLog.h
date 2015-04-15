/*
*  FILE: boost.log.init.hpp
*  INSTRUCTION: ����ļ����ڳ�ʼ��boost.log
*  DETAIL: �������¶�������־����Ͷ�Ӧ���ı�����.
*          �ļ���С���Ƶ���Ϣ��Ӳ������cpp�ļ��У�������������޸ġ�
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
