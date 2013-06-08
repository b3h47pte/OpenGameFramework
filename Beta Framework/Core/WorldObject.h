#pragma once
#ifndef _WORLDOBJECT_H
#define _WORLDOBJECT_H

#include "CommonCore.h"
#include "Object.h"
#include "CoreExternal.h"

/* 
 * An object that will get placed into whatever "world" is being created by the game developer.
 * Main Difference between this and an object: Has a position/orientation in some space. 
 * Assumes that the default "Forward" direction is down the -Z axis.
 * Right direction is then the positive X axis.
 * Up direction is the positive Y axis.
 */
class  WorldObject: public Object
{
public:
	WorldObject();
	WorldObject(glm::vec4 inPos, glm::quat inRot);
	~WorldObject(void);

	/*
	 * Accessor methods for position and rotation.
	 */
	virtual glm::vec4		GetPosition() const { return mPosition; }
	void			SetPosition(const glm::vec4& in) { mPosition = in; UpdateTransformationMatrix(); }

	virtual glm::fquat		GetQuaternion() const { return mRotation; }
	glm::vec3		GetEulerAngles() const { return glm::eulerAngles(mRotation); }
	glm::mat4		GetRotationMatrix() const { return glm::mat4_cast(mRotation); }
	void			SetRotation(const glm::fquat& in) { mRotation = in; UpdateTransformationMatrix(); }
	void			SetRotation(const glm::vec3& axis, float w) { mRotation = glm::angleAxis(w, glm::normalize(axis)); UpdateTransformationMatrix();}
	void			SetRotation(const glm::vec3& in) { mRotation = glm::fquat(in); UpdateTransformationMatrix(); }
	void			SetRotation(const glm::mat4& in) { mRotation = glm::toQuat(in); UpdateTransformationMatrix(); }

	virtual glm::mat4		GetTransformationMatrix() { return mTransformationMatrix; }

	virtual glm::vec4 GetForwardDirection() { return glm::normalize(GetRotationMatrix() * glm::vec4(0.f, 0.f, -1.f, 0.f)); }
	virtual glm::vec4 GetRightDirection() { return glm::normalize(GetRotationMatrix() * glm::vec4(1.f, 0.f, 0.f, 0.f)); }
	virtual glm::vec4 GetUpDirection() { return glm::normalize(GetRotationMatrix() * glm::vec4(0.f, 1.f, 0.f, 0.f)); }

protected:
	virtual void	UpdateTransformationMatrix();
	glm::mat4	mTransformationMatrix;

private:
	glm::vec4	mPosition;
	glm::fquat	mRotation;
};

#endif // _WORLDOBJECT_H
