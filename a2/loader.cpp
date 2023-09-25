#include "loader.h"

using namespace osp2023;

//Method: Give data file name, returns vector of created PCBs.
static std::vector<pcb> createPCBs(std::string dataFileName){
    //Open datafile in a fsteam
    std::fstream dataFile;
    dataFile.open(dataFileName);

    //Create return vector.
    std::vector<pcb> PCBs;

    //Create line holder variable.
    std::string pcbParams;

    //String delimiter.
    std::string delimiter = ",";

    while( getline(dataFile, pcbParams) ){
        //get ID from data line
        id_type pID = stoi(pcbParams.substr(0, pcbParams.find(delimiter)));

        //get burst time from data line
        std::string burstString = pcbParams.substr(pcbParams.find(delimiter) + 1, pcbParams.length());
        time_type burstTime = stoi(burstString);

        //create the process and set variables
        pcb process;
        process.setID(pID);
        process.setTotalTime(burstTime);

        //Add process to return vector.
        PCBs.push_back(process);
    }

    return PCBs;
}