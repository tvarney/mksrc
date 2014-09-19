
#ifndef MKSRC_OUTPUT_LEVEL_HPP
#define MKSRC_OUTPUT_LEVEL_HPP

namespace mksrc {
    struct OutputLevel {
        enum Value {
            Quiet   = 0,
            Brief   = 1,
            Normal  = 2,
            Verbose = 3
        };
    };
}

#endif
