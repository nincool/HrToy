#ifndef _HR_COMPONENT_H_
#define _HR_COMPONENT_H_

class HrComponent
{
public:
	virtual ~HrComponent() {};

	virtual bool InitComponent() = 0;

	virtual bool Update(float fDelta) = 0;
};

#endif
