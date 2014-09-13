
#include "MakeSourceState.hpp"

using namespace mksrc;

int main(int argc, char **argv) {
    MakeSourceState state;
    state.parse(argc, argv);
    return 0;
}
