#ifndef _I_RENDERDEMO_H_
#define _I_RENDERDEMO_H_

#include "HrRendererDemoPrerequisites.h"

namespace Hr
{
	class HR_RENDERDEMO_API IRenderDemo
	{
	public:
		~IRenderDemo(){}

		virtual void SetD3DDevice(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContex) = 0;

		virtual bool Init() = 0;

		virtual bool Render() = 0;

		virtual void Release() = 0;
	};
}


#endif