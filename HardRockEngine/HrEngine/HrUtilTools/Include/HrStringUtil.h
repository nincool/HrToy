#ifndef _HR_STRINGUTIL_H_
#define _HR_STRINGUTIL_H_

#include <string>
#include <cctype>
#include <algorithm>
#include <locale>
#include <codecvt>
#include <memory>
#include <HrMath/Include/HrMath.h>
#include <boost/lexical_cast.hpp> 
#include "HrUtilTools/Include/HrTinyFormat.h"

namespace Hr
{
	class HrStringUtil
	{
	public:
		template<typename... Args>
		static std::string StringFormat(const char* formatString, Args&&... args)
		{
			return tfm::format(formatString, std::forward<Args>(args)...);
		}

		static std::string WstringToUtf8(const std::wstring& str)
		{
			std::wstring_convert<std::codecvt_utf8<wchar_t> > strCnv;
			return strCnv.to_bytes(str);
		}

		static std::wstring Utf8ToWstring(const std::string& str)
		{
			std::wstring_convert< std::codecvt_utf8<wchar_t> > strCnv;
			return strCnv.from_bytes(str);
		}

		static void ToLowerCase(std::string& s)
		{
			std::locale loc;
			std::transform(s.begin(), s.end(), s.begin(),
				[&](unsigned char c) { return std::tolower(c, loc); });
		}

		static void ToUpperCase(std::string& s)
		{
			std::locale loc;
			std::transform(s.begin(), s.end(), s.begin(),
				[&](unsigned char c) { return std::toupper(c, loc); });
		}

		static float2 GetFloat2FromString(const std::string& strContent, const char* p1 = "|")
		{
			std::vector<float> vecElement = GetFloatVectorFromString(strContent, p1);
			return float2(vecElement[0], vecElement[1]);
		}

		static float3 GetFloat3FromString(const std::string& strContent, const char* p1 = "|")
		{
			std::vector<float> vecElement = GetFloatVectorFromString(strContent, p1);
			return float3(vecElement[0], vecElement[1], vecElement[2]);
		}

		static float4 GetFloat4FromString(const std::string& strContent, const char* p1 = "|")
		{
			std::vector<float> vecElement = GetFloatVectorFromString(strContent, p1);
			return float4(vecElement[0], vecElement[1], vecElement[2], vecElement[3]);
		}
		
		template<typename T>
		static std::vector<T> GetTVectorFromString(const std::string& strContent, const char* p1 = "|")
		{
			std::vector<T> result;
			std::vector<std::string> temp = GetVector(strContent, p1);
			for (int i = 0; i < temp.size(); ++i)
			{
				result.push_back(boost::lexical_cast<T>(temp[i].c_str()));
			}
			return result;
		}

		static std::vector<float> GetFloatVectorFromString(const std::string& strContent, const char* p1 = "|")
		{
			std::vector<float> result;
			std::vector<std::string> temp = GetVector(strContent, p1);
			for (int i = 0; i < temp.size(); ++i)
			{
				result.push_back(boost::lexical_cast<float>(temp[i].c_str()));
			}
			return result;
		}

		static std::vector<uint8> GetUInt8VectorFromString(const std::string& strContent, const char* p1 = "|")
		{
			std::vector<uint8> result;
			std::vector<std::string> temp = GetVector(strContent, p1);
			for (int i = 0; i < temp.size(); ++i)
			{
				result.push_back(static_cast<uint8>(boost::lexical_cast<unsigned int>(temp[i].c_str())));
			}
			return result;
		}

		static std::vector<int> GetIntVectorFromString(const std::string& strContent, const char* p1 = "|")
		{
			std::vector<int> result;
			std::vector<std::string> temp = GetVector(strContent, p1);
			for (int i = 0; i < temp.size(); ++i)
			{
				result.push_back(boost::lexical_cast<int>(temp[i].c_str()));
			}
			return result;
		}

		static std::vector<int64> GetInt64VectorFromString(const std::string& strContent, const char* p1)
		{
			std::vector<int64> result;
			std::vector<std::string> temp = GetVector(strContent, p1);
			for (int i = 0; i < temp.size(); ++i)
			{
				result.push_back(boost::lexical_cast<int64>(temp[i].c_str()));
			}
			return result;
		}

		static std::vector<Vector2> GetVectorFloat2FromString(const std::string& strContent, const char* p1, const char* p2)
		{
			std::vector<float2> result;
			std::vector<std::string> temp = GetVector(strContent, p1);
			for (size_t i = 0; i < temp.size(); ++i)
			{
				result.push_back(GetFloat2FromString(temp[i], p2));
			}
			return result;
		}

		static std::vector<Vector3> GetVectorFloat3FromString(const std::string& strContent, const char* p1, const char* p2)
		{
			std::vector<Vector3> result;
			std::vector<std::string> temp = GetVector(strContent, p1);
			for (size_t i = 0; i < temp.size(); ++i)
			{
				result.push_back(GetFloat3FromString(temp[i], p2));
			}
			return result;
		}

		static std::vector<std::string> GetVector(const std::string& strContent, const char* p1)
		{
			std::vector<std::string> result;
			if (strContent == "")
			{
				return result;
			}

			char* c = new char[strContent.length()+1];
			char *resource = const_cast<char*>(strContent.data());
			strcpy(c, resource);

			char *p;
			strtok(c, p1);
			result.push_back(c);
			while ((p = strtok(NULL, p1)))
				result.push_back(p);

			delete c;

			return result;
		}
		
		//static std::vector<std::string> GetVector(const std::string& strContent, const std::string& strDelim)
		//{
		//	std::string strReDelim = "[" + strDelim + "]";
		//	std::regex re{ strReDelim };
		//	// 调用 std::vector::vector (InputIterator first, InputIterator last,const allocator_type& alloc = allocator_type())
		//	// 构造函数,完成字符串分割
		//	return std::vector<std::string> {
		//		std::sregex_token_iterator(strContent.begin(), strContent.end(), re, -1),
		//			std::sregex_token_iterator()
		//	};
		//}

		static std::string& ReplaceAll(std::string& str, const std::string& strOldValue, const std::string& strNewValue)
		{
			while (true)
			{
				std::string::size_type pos(0);
				if ((pos = str.find(strOldValue)) != std::string::npos)
				{
					str.replace(pos, strOldValue.length(), strNewValue);
				}
				else
				{
					break;
				}
			}

			return str;
		}

		static std::string& ReplaceAllDistinct(std::string& str, const std::string& strOldValue, const std::string& strNewValue)
		{
			for (std::string::size_type pos(0); pos != std::string::npos; pos += strNewValue.length())
			{
				if ((pos = str.find(strOldValue, pos)) != std::string::npos)
				{
					str.replace(pos, strOldValue.length(), strNewValue);
				}
				else
				{
					break;
				}
			}

			return str;
		}
	};

}


#endif



