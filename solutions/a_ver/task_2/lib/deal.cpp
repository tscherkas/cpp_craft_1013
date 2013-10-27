#include <stdint.h>
#include <fstream>
#include <deal.h>

using namespace std;

istream& operator>> (istream& is, MessageHeader &m){

    is.read((char *)&m.type, sizeof(uint32_t));
    is.read((char *)&m.time, sizeof(uint32_t));
    is.read((char *)&m.len, sizeof(uint32_t));

    return is;
}