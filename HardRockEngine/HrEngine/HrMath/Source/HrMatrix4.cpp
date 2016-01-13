#include "HrMatrix4.h"

using namespace Hr;

const HrMatrix4 HrMatrix4::ZERO(
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0);
const HrMatrix4 HrMatrix4::IDENTITY(
	1, 0, 0, 0, 
	0, 1, 0, 0, 
	0, 0, 1, 0,
	0, 0, 0, 1);