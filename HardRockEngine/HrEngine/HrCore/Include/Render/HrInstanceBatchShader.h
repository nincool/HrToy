#ifndef _HR_INSTANCEBATCHSHADER_H_
#define _HR_INSTANCEBATCHSHADER_H_

#include "HrCore/Include/Render/HrInstanceBatch.h"

namespace Hr
{
	class HrInstanceBatchShader : public HrInstanceBatch
	{
	public:
		HrInstanceBatchShader();
		~HrInstanceBatchShader();

	protected:
		virtual void BuildVertices(const HrSubMeshPtr& pSubMesh) override;


	};

}



#endif
