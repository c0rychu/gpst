#include <iostream>
#include <exception>
#include <stdexcept>
#include <time.h>
#include <getopt.h>
#include "gpst_leaps.h"
#include "gpst_lib.h"

static const char USAGE[] =
"Usage: gpst [-n] [-g <gpstime>] [-u <unixtime>] [-h]\n\n"
"\t-n --now            \t print the current gpstime \n"
"\t-g --gps <gpstime>  \t print the unixtime of the gpstime\n"
"\t-u --unix <unixtime>\t print the gpstime of the unixtime\n"
"\t-h --help           \t print this message\n\n"
"Expiration date: " EXPIRE_ON_STR "\n\n";

void
usage()
{
    std::cout << USAGE << std::endl;
}

int
main(int argc, char** argv)
{
    if (argc == 1) {
        usage();
        return -1;
    }

    int c;
    while (1)
    {
        static struct option long_options[] =
        {
            {"now",        no_argument,   0, 'n'},
            {"gps",  required_argument,   0, 'g'},
            {"unix", required_argument,   0, 'u'},
            {"help",       no_argument,   0, 'h'},
            {0, 0, 0, 0}
        };
        /* getopt_long stores the option index here. */
        int option_index = 0;
        c = getopt_long (argc, argv, "ng:u:h", long_options, &option_index);
        
        /* Detect the end of the options. */
        if (c == -1)
            break;
        
        switch (c) {       
            case 'n':
                printf("%ld\n", unix2gps(time(NULL)));
                break;

            case 'u':
                try {
                    printf("%ld\n", unix2gps((time_t)std::stol(optarg, NULL, 10)));
                } catch (std::invalid_argument& e) {
                    std::cerr << e.what() << std::endl;
                }
                break;
                
            case 'g':
                printf("%ld\n", gps2unix((time_t)std::stol(optarg, NULL, 10)));
                break;
                
            case 'h':
                usage();
                break;
                
            case '?':
                break;
                
            default:
                abort();
        }
    }
     
    /* Print any remaining command line arguments (not options). */
    if (optind < argc)
    {
        printf ("invalid arguments: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        putchar ('\n');
        usage();
    }
    return 0;
}


