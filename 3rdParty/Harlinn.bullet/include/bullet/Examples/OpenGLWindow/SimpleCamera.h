#ifndef SIMPLE_CAMERA_H
#define SIMPLE_CAMERA_H

#include "../CommonInterfaces/CommonCameraInterface.h"

#include <bullet/bullet_export.h>

struct SimpleCamera : public CommonCameraInterface
{
	struct SimpleCameraInternalData* m_data;

	BT_EXPORT SimpleCamera();
	BT_EXPORT virtual ~SimpleCamera();

	BT_EXPORT void update();
	BT_EXPORT virtual void getCameraProjectionMatrix(float m[16]) const;
	BT_EXPORT virtual void getCameraViewMatrix(float m[16]) const;

	BT_EXPORT virtual void setVRCamera(const float viewMat[16], const float projectionMatrix[16]);
	BT_EXPORT virtual bool getVRCamera(float viewMat[16], float projectionMatrix[16]);

	BT_EXPORT virtual void setVRCameraOffsetTransform(const float offset[16]);
	BT_EXPORT virtual void disableVRCamera();

	BT_EXPORT virtual bool isVRCamera() const;

	BT_EXPORT virtual void getCameraTargetPosition(float pos[3]) const;
	BT_EXPORT virtual void getCameraPosition(float pos[3]) const;

	BT_EXPORT virtual void getCameraTargetPosition(double pos[3]) const;
	BT_EXPORT virtual void getCameraPosition(double pos[3]) const;

	BT_EXPORT virtual void setCameraTargetPosition(float x, float y, float z);
	BT_EXPORT virtual void setCameraDistance(float dist);
	BT_EXPORT virtual float getCameraDistance() const;

	BT_EXPORT virtual void setCameraUpVector(float x, float y, float z);
	BT_EXPORT void getCameraUpVector(float up[3]) const;

	BT_EXPORT void getCameraForwardVector(float fwd[3]) const;

	///the setCameraUpAxis will call the 'setCameraUpVector' and 'setCameraForwardVector'
	BT_EXPORT virtual void setCameraUpAxis(int axis);
	BT_EXPORT virtual int getCameraUpAxis() const;

	BT_EXPORT virtual void setCameraYaw(float yaw);
	BT_EXPORT virtual float getCameraYaw() const;

	BT_EXPORT virtual void setCameraPitch(float pitch);
	BT_EXPORT virtual float getCameraPitch() const;

	BT_EXPORT virtual void setAspectRatio(float ratio);
	BT_EXPORT virtual float getAspectRatio() const;

	BT_EXPORT virtual float getCameraFrustumFar() const;
	BT_EXPORT virtual float getCameraFrustumNear() const;

	BT_EXPORT virtual void setCameraFrustumFar(float far);
	BT_EXPORT virtual void setCameraFrustumNear(float near);
};

#endif  //SIMPLE_CAMERA_H
