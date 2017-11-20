#ifndef __ALADDIN_2D_CAMERA_PREFAB_H__
#define __ALADDIN_2D_CAMERA_PREFAB_H__

#include "2dInclude.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1 ( CameraPrefab, Prefab )
public:
  CameraPrefab()
    : Prefab( ALA_MAIN_CAMERA ) {}

protected:
  void doInstantiate( ala::GameObject* object ) const override;
};
}

#endif //!__ALADDIN_2D_CAMERA_PREFAB_H__
