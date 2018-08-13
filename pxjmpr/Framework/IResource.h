#pragma once

#ifndef UNICODE
#endif

#include <Windows.h>

class IResource
{
public:
	_Success_(return == true)
	virtual HRESULT create() = 0;
	virtual void release() = 0;
};