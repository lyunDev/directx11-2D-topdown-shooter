#include "Framework.h"
#include "UpdateDispatcher.h"

vector<function<bool(void)>> UpdateDispatcher::updates;
vector<function<void(void)>> UpdateDispatcher::onCompletes;