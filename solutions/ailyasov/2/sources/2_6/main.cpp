#include "binary_datafeed.h"

int main() {
    BinaryDatafeed::process( 
            SOURCE_DIR "/tests/2.6_example.in", 
            SOURCE_DIR "/tests/2.6.out");
    return 0;
}

