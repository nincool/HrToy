#ifndef _HR_GEOMETRYBOX_H_
#define _HR_GEOMETRYBOX_H_

#include "HrCore/Include/Render/HrRenderable.h"

namespace Hr
{
	class HrGeometryBox : public HrRenderable
	{
	public:
		HrGeometryBox(uint32 nLength, uint32 nWidth, uint32 nHeight);
		~HrGeometryBox();

		virtual HrRenderLayout* GetRenderLayout() override;
	private:
		void InitRenderLayout();
		void BindVertexStream();
	private:
		HrMesh* m_pMesh;

		uint32 m_nLength;
		uint32 m_nWidth;
		uint32 m_nHeight;
	};
}

#endif



