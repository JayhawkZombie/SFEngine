#pragma once

#include "BasicIncludes.h"
#include "Engine\BaseEngineInterface.h"

namespace Engine
{

  class LevelObject;

  class EquippableBase : public BaseEngineInterface
  {
  public:
    EquippableBase();
    ~EquippableBase();

    virtual void OnEquipped(LevelObject *EquippedOn) = 0;
    virtual void OnUnequipped(LevelObject *EquippedOff) = 0;

    virtual std::string GetEquipType() const;
    virtual void SetEquipType(const std::string &Type);

  protected:
    std::string m_EquipType;

    LevelObject *m_ObjectAttachedTo;

  };

}
