
#include <iostream>
#include <getopt.h>

static const char *short_options = "vbqL:D:B:";
static struct option long_options[] = {
    {"verbose", no_argument, nullptr, 'v'},
    {"brief", no_argument, nullptr, 'b'},
    {"quiet", no_argument, nullptr, 'q'},
    {"license", required_argument, nullptr, 'L'},
    {"docstyle", required_argument, nullptr, 'D'},
    {"body", required_argument, nullptr, 'B'},
};

int main(int argc, char **argv) {
    int option_ind = 0, c;
    while(true) {
	c = getopt_long(argc, argv, short_options, long_options, &option_ind);
	if(c == -1) {
	    break;
	}
	
	switch(c) {
	case 'v':
	    std::cout << "verbose" << std::endl;
	    break;
	case 'b':
	    std::cout << "brief" << std::endl;
	    break;
	case 'q':
	    std::cout << "quiet" << std::endl;
	    break;
	case 'L':
	    std::cout << "License: " << optarg << std::endl;
	    break;
	case 'D':
	    std::cout << "Docstyle: " << optarg << std::endl;
	    break;
	case 'B':
	    std::cout << "Body: " << optarg << std::endl;
	    break;
	default:
	    break;
	}
    }
    
    std::cout << "Files: " << std::endl;
    for(int i = optind; i < argc; ++i) {
	std::cout << "  " << argv[i] << std::endl;
    }
    
    return 0;
}
