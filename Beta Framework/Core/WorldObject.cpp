#include "WorldObject.h"

WorldObject::WorldObject(): mPosition(glm::vec4()), mRotation(glm::quat()) {
}

WorldObject::WorldObject(glm::vec4 inPos, glm::quat inRot): mPosition(inPos), mRotation(inRot) {
}


WorldObject::~WorldObject(void) {
}
