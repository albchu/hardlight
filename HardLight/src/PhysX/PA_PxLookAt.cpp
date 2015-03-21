#include "PhysxAgent.h"
// http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/

static PxQuat RotationBetweenVectors(PxVec3 start, PxVec3 dest)
{
	start.normalize();
	dest.normalize();

	float cosTheta = start.dot(dest);
	PxVec3 rotationAxis;

	if (cosTheta < -1 + 0.001f){
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = PxVec3(0.f, 0.f, 1.f).cross(start);
		if (rotationAxis.magnitude() < 0.001f) // bad luck, they were parallel, try again!
			rotationAxis = PxVec3(1.f, 0.f, 0.f).cross(start);

		rotationAxis.normalize();
		return PxQuat(PxPi, rotationAxis);
	}

	rotationAxis = start.cross(dest);

	float s = sqrt((1.f + cosTheta) * 2.f);
	float invs = 1.f / s;

	return PxQuat(
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs,
		s * 0.5f
		);
}

PxQuat PhysxAgent::PxLookAt(vec3 direction, vec3 up)
{
	PxVec3 d = PxVec3(direction.x, direction.y, direction.z);
	PxVec3 u = PxVec3(up.x, up.y, up.z);
	return PxLookAt(d, u);
}

PxQuat PhysxAgent::PxLookAt(PxVec3 direction, PxVec3 up)
{
	direction.normalize();
	PxVec3 right = direction.cross(up).getNormalized();
	up = right.cross(direction).getNormalized();

	PxQuat q1 = RotationBetweenVectors(PxVec3(0.f,0.f,1.f), direction).getNormalized();

	PxVec3 newUp = q1.rotate(PxVec3(0.f,1.f,0.f)).getNormalized();

	PxQuat q2 = RotationBetweenVectors(newUp, up).getNormalized();

	PxQuat q3 = q2*q1;
	return q3.getNormalized();
}
