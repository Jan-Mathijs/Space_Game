#pragma once
#ifdef RASPBERRY
#include "Input/BaseInput.h"
#include "Headers/Input.h"

class LinuxInput :
	public BaseInput
{
public:
	LinuxInput();
	~LinuxInput();

	void CheckInput();

	Input* theInput;
};

#endif