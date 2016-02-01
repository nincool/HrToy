#include "Asset/HrGeometryFactory.h"
#include "HrUtilTools/Include/HrUtil.h"

using namespace Hr;

HrGeometryFactoryPtr HrGeometryFactory::m_s_pUniqueFactory;

HrGeometryFactory::HrGeometryFactory()
{

}

HrGeometryFactory::~HrGeometryFactory()
{

}

HrGeometryFactory& HrGeometryFactory::GetInstance()
{
	if (!m_s_pUniqueFactory)
	{
		m_s_pUniqueFactory = MakeUniquePtr<HrGeometryFactory>();
	}

	return *m_s_pUniqueFactory;
}
