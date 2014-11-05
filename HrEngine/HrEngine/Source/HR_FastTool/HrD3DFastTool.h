#ifndef _HR_D3DFASTTOOL_H_
#define _HR_D3DFASTTOOL_H_

namespace HR
{
	class CHrMaterial;
	class CHrLight;
	class CHrD3DFastTool
	{
	public:
		CHrD3DFastTool();
		~CHrD3DFastTool();

		enum _HR_MATERIAL_
		{
			MATERIAL_RED,
			MATERIAL_GREEN,
			MATERIAL_BLUE,
			MATERIAL_WHITE,
		};

		//创建的都是平行光
		enum struct _HR_DIRECTLIGHT_
		{
			LIGHT_WHITE,
			LIGHT_RED,
			LIGHT_GREEN,
			LIGHT_BLUE,
			LIGHT_DARK,
		};

		enum struct _HR_SPOTLIGHT_
		{

		};
	public:
		static CHrD3DFastTool*   Instance();
	public:
		CHrMaterial*      CreateMaterial(_HR_MATERIAL_ eMaterialType);
		CHrLight*         CreateLight(_HR_DIRECTLIGHT_ eLightType);

	private:
		static CHrD3DFastTool m_s_hrD3DFastTool;
	};
}


#endif

