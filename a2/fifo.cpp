//First in First Out CPU scheduling algorithm.

#include "pcb.h"
#include "types.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace osp2023;

int main(int argc, char *argv[]){

    //check number of arguments. (HAS TO BE 2)
    if(argc != 2){
        std::cout << "Valid usage: ./fifo <data file name> \n Exiting Program" << std::endl;
        return EXIT_FAILURE;
    }

    //Open datafile in a fsteam
    std::string data_file_name = argv[1];
    std::fstream dataFile;
    dataFile.open(data_file_name);

    //Exit program if data file is not open in fstream
    if(!dataFile){
        std::cout << "Data file not valid or doesnt exist. \n Exiting Program." << std::endl;
        return EXIT_FAILURE;
    }

    //Create processes
    std::vector<pcb> queue;
    std::string pcbParams;
    std::string delimiter = ",";

    while( getline(dataFile, pcbParams) ){
        //get ID from data line
        id_type pID = stoi(pcbParams.substr(0, pcbParams.find(delimiter)));

        //get burst time from data line
        std::string burstTime = pcbParams.substr(pcbParams.find(delimiter), pcbParams.length());

        std::cout << "pID: " << pID << ", Burst Time: " << burstTime << std::endl;
    }

    return EXIT_SUCCESS;

}