#ifndef _HR_GIRLFRIEND_H_
#define _HR_GIRLFRIEND_H_

#include "HrCore/Include/Asset/HrResource.h"

namespace Hr
{
	class HR_CORE_API HrPrefabData : public HrResource
	{
	public:
		HrPrefabData();
		~HrPrefabData();

		class HrPrefabModelInfo
		{
		public:
			HrPrefabModelInfo(const HrMeshModelPtr& pMeshModel, const Vector3& vPosition, const Vector3& vRotate, const Vector3& vScale)
			{
				m_pMeshModel = pMeshModel;
				m_vPosition = vPosition;
				m_vRotate = vRotate;
				m_vScale = vScale;
			}

			HrMeshModelPtr m_pMeshModel;
			Vector3 m_vPosition;
			Vector3 m_vRotate;
			Vector3 m_vScale;
		};

		static size_t CreateHashName(const std::string& strHashValue);

		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath) override;

		const HrSceneNodePtr CreateSceneNode();
	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;

	private:
		std::vector<HrPrefabModelInfo> m_vecPrefabModelInfo;
	};
}

#endif
