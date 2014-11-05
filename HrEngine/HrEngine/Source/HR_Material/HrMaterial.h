#ifndef _HR_MATERIAL_H_
#define _HR_MATERIAL_H_

#include "HrCommon.h"

namespace HR
{
	class CHrMaterial
	{
	public:
		CHrMaterial();
		~CHrMaterial();

	public:
		D3DMATERIAL9*   GetMaterial();

		void            ResetMaterial();

		void            SetDiffuseColor(D3DXCOLOR color);
		void            SetAmbientColor(D3DXCOLOR color);
		void            SetSpecularColor(D3DXCOLOR color);
		void            SetEmissiveColor(D3DXCOLOR color);
		void            SetPower(float fPower);

	private:
		D3DMATERIAL9        m_stD3DMaterial;
	};
}

#endif // !_HR_MATERIAL_H_

