#pragma once

class CPed {
public:
	void UpdateHeading();

	int GetBoneFrame(int frame);

	bool isCrawling();
};
class CAutoPed : public CPed {
public:

};

