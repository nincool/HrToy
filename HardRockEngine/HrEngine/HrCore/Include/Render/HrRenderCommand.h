#ifndef _HR_RENDERCOMMAND_H_
#define _HR_RENDERCOMMAND_H_

#include "HrCore/Include/HrCorePrerequisite.h"

namespace Hr
{
	class HR_CORE_API HrRenderCommand
	{
	public:
		/**Enum the type of render command. */
		enum class EnumRenderCommand
		{
			/** Reserved type.*/
			UNKNOWN_COMMAND,
			/** Quad command, used for draw quad.*/
			QUAD_COMMAND,
			/**Custom command, used for calling callback for rendering.*/
			CUSTOM_COMMAND,
			/**Batch command, used for draw batches in texture atlas.*/
			BATCH_COMMAND,
			/**Group command, which can group command in a tree hierarchy.*/
			GROUP_COMMAND,
			/**Mesh command, used to draw 3D meshes.*/
			MESH_COMMAND,
			/**Primitive command, used to draw primitives such as lines, points and triangles.*/
			PRIMITIVE_COMMAND,
			/**Triangles command, used to draw triangles.*/
			TRIANGLES_COMMAND
		};

	public:
		HrRenderCommand(std::function<void()> funcRenderBegin, std::function<void()> funcRenderEnd);

		void SetGlobalOrder(float fGlobalOrder);
		float GetGlobalOrder();

		void SetDepth(float fDepth);
		float GetDepth();

		void SetTransform(HrTransform* pTransfrom);
		HrTransform* GetTransform();

		void SetMaterial(HrMaterial* pMaterial);
		HrMaterial* GetMaterial();
		
		void SetRenderLayout(HrRenderLayout* pRenderLayout);
		HrRenderLayout* GetRenderLayout();

		void SetRenderEffect(HrRenderEffect* pRenderEffect);
		HrRenderEffect* GetRenderEffect() const;
		
		void SetRenderTechnique(HrRenderTechnique* pRenderTechnique);
		HrRenderTechnique* GetRenderTechnique();

		void OnRenderBegin();
		void OnRenderEnd();
	protected:
		EnumRenderCommand m_type;

		float m_fGlobalOrder;
		float m_fDepth;

		HrTransform* m_pTransform;
		HrMaterial* m_pMaterial;
		HrRenderLayout* m_pRenderLayout;
		
		HrRenderEffect* m_pRenderEffect;
		HrRenderTechnique* m_pRenderTechnique;

		std::function<void()> m_funcRenderBegin;
		std::function<void()> m_funcRenderEnd;
	};

	class HR_CORE_API HrMeshRenderCommand : public HrRenderCommand
	{
	public:
	protected:

	};
}



#endif



