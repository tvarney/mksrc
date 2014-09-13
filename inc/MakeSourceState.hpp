
#ifndef MKSRC_MAKE_SOURCE_STATE_HPP
#define MKSRC_MAKE_SOURCE_STATE_HPP

#include <vector>
#include "OutputLevel.hpp"

namespace mksrc {
    class MakeSourceState {
    public:
	MakeSourceState();
	~MakeSourceState() = default;
	
	bool parse(int argc, char **argv);
	bool parse(const char *filename);
    protected:
	const char *m_LicenseName;
	const char *m_DocstyleName;
	bool m_DoBody;
	OutputLevel::Value m_OutputLevel;
	
	std::vector<const char *> m_FileNames;
    };
}

#endif
