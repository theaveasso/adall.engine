#include "adall/adall.h"

class adlglSandbox : public adlApplication {
public:
	~adlglSandbox() override = default;
};

adlApplication& adlMakeApplication() {
	return adlglSandbox::getInstance();
}