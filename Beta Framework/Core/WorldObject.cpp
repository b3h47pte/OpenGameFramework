#include "WorldObject.h"

WorldObject::WorldObject(): mPosition(glm::vec4()), mRotation(glm::quat()) {
}

WorldObject::WorldObject(glm::vec4 inPos, glm::quat inRot): mPosition(inPos), mRotation(inRot) {
}


WorldObject::~WorldObject(void) {
}

/*
 * Update the transformation matrix so we can easily query the object to get a matrix that represents the orientation of the object.
 */
void WorldObject::UpdateTransformationMatrix() {
	mTransformationMatrix = glm::lookAt(glm::vec3(mPosition), glm::vec3(mPosition + GetForwardDirection()), glm::vec3(GetUpDirection()));
}