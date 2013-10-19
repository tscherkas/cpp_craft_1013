#include "small_buffer.h"

int main() {
    SmallBuffer::read_to_buff_and_save_stats(
            SOURCE_DIR "/tests/2.5_example.in", 
            SOURCE_DIR "/tests/2.5.out");
    return 0;
}

