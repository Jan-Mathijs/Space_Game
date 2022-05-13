#pragma once
class BaseInput
{
public:
	BaseInput();
	~BaseInput();

	virtual void CheckInput() = 0;

	bool inputKeyW = false;
	bool inputKeyS = false;
	bool inputKeyQ = false;
	bool inputKeyE = false;
	bool inputKeyArrowUp = false;
	bool inputKeyArrowDown = false;
	bool inputKeyArrowLeft = false;
	bool inputKeyArrowRight = false;
	bool inputKeyESC = false;
	bool inputKeyL = false;
	bool inputKeyZ = false;
};

