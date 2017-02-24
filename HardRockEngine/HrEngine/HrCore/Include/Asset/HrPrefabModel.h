#ifndef _HR_PREFEBMODEL_H_
#define _HR_PREFEBMODEL_H_

#include "HrCore/Include/Asset/HrResource.h"

namespace Hr
{
	class HrPrefabModel : public HrResource
	{
	public:
		HrPrefabModel();
		~HrPrefabModel();
		
		/**
		 @Comment: Create HashName [2/20/2017 By Hr]
		 @Param: full path of the res
		 @Return: HashName
		*/
		static size_t CreateHashName(const std::string& strFullFilePath);

		virtual void DeclareResource(const std::string& strFileName, const std::string& strFilePath) override;

		HrMesh* GetMesh()
		{
			return m_pMesh;
		}

	protected:
		virtual bool LoadImpl() override;
		virtual bool UnloadImpl() override;
	protected:
		HrMesh* m_pMesh;
		std::vector<HrMaterial*> m_vecMaterial;
		std::vector<HrTexture*> m_vecTexture;
	};
}

#endif

