#include "adall/adal.h"

class adlglSandbox : public adlglApplication {
public:
	~adlglSandbox() override = default;
};

adlglApplication& adlglMakeApplication() {
	return adlglSandbox::getInstance();
}