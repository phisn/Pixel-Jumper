#pragma once



template <typename T>
class ComPtr
{
public:
	~ComPtr()
	{
		release();
	}

	void release()
	{
		if (object)
		{
			object->Release();
			object = 0;
		}
	}

	T** operator&()
	{
		return &object;
	}

	T* operator->() const
	{
		return object;
	}

	T* get()
	{
		return object;
	}
private:
	T* object = 0;
};
