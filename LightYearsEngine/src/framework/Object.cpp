#include "framework/Core.h"
#include "framework/Object.h"

namespace ly {
	unsigned int Object::uniqueIDCounter = 0;
	Object::Object()
		: mIsPendingDestroy{ false }, mUniqueID{ GetNextAvaliableID() }
	{
	}
	Object::~Object()
	{
		//LOG("Object destroy");
	}
	void Object::Destroy()
	{
		onDestroy.Broadcast(this);
		mIsPendingDestroy = true;
	}

	weak<Object> Object::GetWeakRef()
	{
		return shared_from_this();
	}
	weak<const Object> Object::GetWeakRef() const
	{
		return shared_from_this();
	}
	unsigned int Object::GetNextAvaliableID()
	{
		return uniqueIDCounter++;
	}
}