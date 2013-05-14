#pragma once
#pragma warning( push )
#ifndef _WORLDOBJECT_H
#define _WORLDOBJECT_H

#include "CommonCore.h"
#include "Object.h"
#include "CoreExternal.h"

/* 
 * An object that will get placed into whatever "world" is being created by the game developer.
 * Main Difference between this and an object: Has a position/orientation in some space. 
 */
class COREAPI WorldObject: public Object
{
public:
	WorldObject();
	WorldObject(glm::vec4 inPos, glm::quat inRot);
	~WorldObject(void);

	/*
	 * Accessor methods for position and rotation.
	 */
	virtual glm::vec4		GetPosition() const { return mPosition; }
	void			SetPosition(const glm::vec4& in) { mPosition = in; }

	virtual glm::fquat		GetQuaternion() const { return mRotation; }
	glm::vec3		GetEulerAngles() const { return glm::eulerAngles(mRotation); }
	glm::mat4		GetRotationMatrix() const { return glm::mat4_cast(mRotation); }
	void			SetRotation(const glm::fquat& in) { mRotation = in; }
	void			SetRotation(const glm::vec3& axis, float w) { mRotation = glm::angleAxis(w, glm::normalize(axis)); }
	void			SetRotation(const glm::vec3& in) { mRotation = glm::fquat(in); }
	void			SetRotation(const glm::mat4& in) { mRotation = glm::toQuat(in); }

	glm::mat4		GetTransformationMatrix() { return mTransformationMatrix; }

protected:
	virtual void	UpdateTransformationMatrix();

private:
	// We have accessor methods for these functions so they'll never be accessed outside of this DLL - Disable Warning C4251
#pragma warning (disable: 4251)
	glm::vec4	mPosition;
	glm::fquat	mRotation;
	glm::mat4	mTransformationMatrix;
#pragma warning (pop)
};

#endif // _WORLDOBJECT_H
