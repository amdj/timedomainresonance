#pragma once
#ifndef _SOLUTION_H_
#define _SOLUTION_H_




#include "vtypes.h"

namespace td{
  SPOILNAMESPACE

  class Solution{

    vd rho;
    vd u;
    vd e;
    vd p;
  public:
    Solution(){}
    ~Solution(){}
  };

} // namespace td
#endif /* _SOLUTION_H_ */
