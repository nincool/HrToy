#include "Asset/HrResource.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

using namespace Hr;

HrResource::HrResource() : m_resType(RT_UNKNOWN), m_resStatus(RS_UNKNOWN)
{
	boost::uuids::random_generator rGenUUID;
	boost::uuids::uuid ranUUID = rGenUUID();
	m_strUUID = boost::uuids::to_string(ranUUID);
}

HrResource::~HrResource()
{

}

bool HrResource::Load()
{
	if (IsLoaded() || !IsDeclared())
	{
		return true;
	}
	if (!LoadImpl())
	{
		return false;
	}
	m_resStatus = RS_LOADED;

	return true;
}

bool HrResource::Unload()
{
	if (!IsLoaded())
	{
		return true;
	}
	UnloadImpl();
	m_resStatus = RS_DECLARED;

	return true;
}

