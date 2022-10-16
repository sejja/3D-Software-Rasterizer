#include "../Math/Matrix4.h"
#include <vector>
#include <string>

class GameObject {

public:
	virtual void Render(const bool mode, const Matrix4& mtr) noexcept {};
	Vector4 mPosition = { 0, 0, 0, 0 };
	Vector4 mRotation = { 0, 0, 0, 0 };
	Vector4 mScale = { 0, 0, 0, 0 };
	Vector4 mUp = { 0, 1, 0, 0 };
	Vector4 mView = { 0, 0, 1, 0 };
	Vector4 mRight = mView.Cross(mUp);
	std::vector<GameObject*> Components;
	std::string mName;
};