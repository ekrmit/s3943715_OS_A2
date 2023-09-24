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
    //dataFile.close();

    //Create processes
    std::vector<pcb> queue;
    std::string pcbParams;
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
        queue.push_back(process);
    }

    //keep track of crrent time.
    time_type allProcessWaitTime = 0;
    time_type allProcessTurnAroundtime = 0;
    time_type allProcessResponseTime = 0;

    time_type currTurnArTime = 0;
    
    time_type currentTime = 0;

    //Go through the queue of processes, satrting with first in.
    for(int x = 0; x < int(queue.size()); x++){
        queue[x].setTotalWaitTime(currentTime);

        currentTime += queue[x].getTotalTime();

        currTurnArTime = queue[x].getTotalWaitTime() + queue[x].getTotalTime();

        std::cout << "Process " << queue[x].getID() << ": Burst Time = " << queue[x].getTotalTime()
             << ", Turnaround Time = " << currTurnArTime
             << ", Waiting Time = " << queue[x].getTotalWaitTime()
             << ", Response Time = " << queue[x].getTotalWaitTime() << std::endl;
        
        allProcessWaitTime += long(queue[x].getTotalWaitTime());
        allProcessResponseTime +=long(queue[x].getTotalWaitTime());
        allProcessTurnAroundtime += (long(queue[x].getTotalWaitTime()) + long(queue[x].getTotalTime()));

    }

    //Calculate Averages for  
    int numProcesses = int(queue.size());
    time_type waitAverage = allProcessWaitTime/numProcesses;
    time_type turnAroundAverage = allProcessTurnAroundtime/long(queue.size());
    time_type responseAverage = allProcessResponseTime / long(queue.size());

    std::cout << std::endl;
    std::cout << "Results:" << std::endl;
    std::cout << "Number of Processes: " << numProcesses << std::endl;
    std::cout << "Average Waiting Time: " << waitAverage << std::endl;
    std::cout << "Average Turnaround Time: " << turnAroundAverage << std::endl;
    std::cout << "Average Response Time: " << responseAverage << std::endl;

    return EXIT_SUCCESS;

}