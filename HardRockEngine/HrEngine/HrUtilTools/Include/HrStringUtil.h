#ifndef _HR_STRINGUTIL_H_
#define _HR_STRINGUTIL_H_

#include <string>
#include <cctype>
#include <algorithm>

#include <boost/lexical_cast.hpp> 

namespace Hr
{
	class HrStringUtil
	{
	public:
		static void ToLowerCase(std::string& s)
		{
			std::transform(s.begin(), s.end(), s.begin(),
				[](unsigned char c) { return std::tolower(c); });
		}

		static void ToUpperCase(std::string& s)
		{
			std::transform(s.begin(), s.end(), s.begin(),
				[](unsigned char c) { return std::toupper(c); });
		}

		static float3 GetFloat3FromString(const std::string& strContent, const char* p1 = "|")
		{
			std::vector<float> vecElement = GetFloatVectorFromString(strContent);
			return float3(vecElement[0], vecElement[1], vecElement[2]);
		}

		static float4 GetFloat4FromString(const std::string& strContent, const char* p1 = "|")
		{
			std::vector<float> vecElement = GetFloatVectorFromString(strContent);
			return float4(vecElement[0], vecElement[1], vecElement[2], vecElement[3]);
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

		static std::vector<uint8> GetUInt8VectorFromString(const std::string& strContent, const char* p1 = "|")
		{
			std::vector<uint8> result;
			std::vector<std::string> temp = GetVector(strContent, p1);
			for (int i = 0; i < temp.size(); ++i)
			{
				result.push_back(boost::lexical_cast<unsigned int>(temp[i].c_str()));
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

		static std::vector<std::string> GetVector(const std::string& strContent, const char* p1)
		{
			std::vector<std::string> result;
			if (strContent == "")
			{
				return result;
			}

			char c[20480];
			char *resource = const_cast<char*>(strContent.data());
			strcpy(c, resource);

			char *p;
			strtok(c, p1);
			result.push_back(c);
			while ((p = strtok(NULL, p1)))
				result.push_back(p);

			return result;
		}
		
	};

}


#endif



