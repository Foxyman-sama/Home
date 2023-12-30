#include "config.h"

#ifdef Testing

#include "test/tests.hpp"

int main(int argc, char **argv) { return startTests(argc, argv); }

#else

#include "modules/business_rules/entities/filemanipulatorimpl.hpp"
#include "modules/business_rules/interactor/interactor.hpp"

int main(int _argc, char **_p_argv) {}

#endif