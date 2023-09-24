#include <iostream>
#include <vector>
#include <fstream>

#include "pcb.h"
#include "types.h"

class loader{
    //class method: Give name of data file, returns vector of created PCBs.
    std::vector<pcb> createPCBs(std::string dataFileName);
};