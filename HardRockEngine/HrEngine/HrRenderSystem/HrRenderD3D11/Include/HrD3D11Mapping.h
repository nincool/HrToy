#ifndef _HR_D3D11MAPPING_H_
#define _HR_D3D11MAPPING_H_

#include "HrRenderSystem/HrRenderD3D11/Include/HrD3D11RenderPrerequisite.h"
#include "HrCore/Include/Render/HrVertext.h"
#include "HrD3D11Device.h"

namespace Hr
{
	class HrD3D11Mapping
	{
	public:
		//InputElement SemanticName×ª»¯
		static LPCSTR GetInputElementSemanticName(HrVertextElement::EnumVertextElementUsage usage);
		static DXGI_FORMAT GetInputElementFormat(HrVertextElement::EnumVertexElementType type);
	};
}

#endif




