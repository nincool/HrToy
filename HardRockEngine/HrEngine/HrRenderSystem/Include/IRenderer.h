/************************************************************************
*
* @Comment��
*
* @Author: Hr
* @Date: [10/28/2015 By Hr]
*
************************************************************************/  

#ifndef _I_RENDERER_H_
#define _I_RENDERER_H_

namespace Hr
{
	class IRenderer
	{
	public:
		virtual ~IRenderer(){};

		/**
		 *	@Brief:  ������Ⱦ��[10/28/2015 By Hr]
		 *	@Param:
		 *	@Return:
		*/
		virtual void Create(unsigned int nWidth, unsigned int nHeight) = 0;
		
		/**
		*	@Brief:  �ݻ���Ⱦ��[10/28/2015 By Hr]
		*	@Param:
		*	@Return:
		*/
		virtual void Destroy() = 0;
	};
}


#endif


