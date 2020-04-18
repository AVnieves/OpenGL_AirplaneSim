#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct Camera
{
public:
	Camera(const glm::vec3& pos, glm::vec3 f, glm::vec3 u, float fov, float aspect, float zNear, float zFar)
		: forward(f), up(u)
	{
		this->pos = pos;
		this->forward = f;
		this->up = u;
		this->projection = glm::perspective(fov, aspect, zNear, zFar);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(pos, pos + forward, up);
	}

	void SetCameraPosition(glm::vec3& pos)
	{
		this->pos = pos;
	}

	void SetCameraUp(glm::vec3 u)
	{
		this->up = u;
	}

	void SetCameraForward(glm::vec3 f)
	{
		this->forward = f;
	}

	void MoveForward(float amt)
	{
		pos += forward * amt;
	}

	void MoveRight(float amt)
	{
		pos += glm::cross(up, forward) * amt;
	}

	void Pitch(float angle)
	{
		glm::vec3 right = glm::normalize(glm::cross(up, forward));

		forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(forward, 0.0)));
		up = glm::normalize(glm::cross(forward, right));
	}

	void RotateY(float angle)
	{
		//static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

		glm::mat4 rotation = glm::rotate(angle, up);

		forward = glm::vec3(glm::normalize(rotation * glm::vec4(forward, 0.0)));
		up = glm::vec3(glm::normalize(rotation * glm::vec4(up, 0.0)));
	}

protected:
private:
	glm::mat4 projection;
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
};

#endif
