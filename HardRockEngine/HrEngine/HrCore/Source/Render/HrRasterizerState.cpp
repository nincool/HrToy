#include "Render/HrRasterizerState.h"
#include <boost/functional/hash.hpp>

using namespace Hr;

HrRasterizerState::HrRasterizerState()
{
}

HrRasterizerState::~HrRasterizerState()
{
}

size_t HrRasterizerState::GetRasterizerStateKey(RasterizerStateDesc& desc)
{
	size_t nKey = 0;
	boost::hash_combine(nKey, desc.fillMode);
	boost::hash_combine(nKey, desc.cullMode);
	boost::hash_combine(nKey, desc.bfrontCounterClockWise);
	boost::hash_combine(nKey, desc.bDepthClipEnable);

	return nKey;
}
