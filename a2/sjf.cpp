//Shortest Job First Scheduling Algorithm

#include "pcb.h"
#include "types.h"

#include <iostream>
#include "pcb.h"
#include "types.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace osp2023;

//Function to sort vector of pcb by shortest burst time.
bool compareByBurstTime(pcb& a, pcb& b) {
    return a.getTotalTime() < b.getTotalTime();
}

int main(int argc, char *argv[]){

    //check number of arguments. (HAS TO BE 2).
    if(argc != 2){
        std::cout << "Valid usage: ./sfj <data file name> \n Exiting Program" << std::endl;
        return EXIT_FAILURE;
    }

    //Open datafile in a fsteam.
    std::string data_file_name = argv[1];
    std::fstream dataFile;
    dataFile.open(data_file_name);

    //Exit program if data file is not open in fstream.
    if(!dataFile){
        std::cout << "Data file not valid or doesnt exist. \n Exiting Program." << std::endl;
        return EXIT_FAILURE;
    }

    //Create processes.
    std::vector<pcb> queue;
    std::string pcbParams;
    std::string delimiter = ",";

    while( getline(dataFile, pcbParams) ){
        //Get ID from data line.
        id_type pID = stoi(pcbParams.substr(0, pcbParams.find(delimiter)));

        //Get burst time from data line.
        std::string burstString = pcbParams.substr(pcbParams.find(delimiter) + 1, pcbParams.length());
        time_type burstTime = stoi(burstString);

        //Create the process and set variables.
        pcb process;
        process.setID(pID);
        process.setTotalTime(burstTime);
        queue.push_back(process);
    }

    //Sort the queue of ready proccess, by the shortest burst time first.
    std::sort(queue.begin(), queue.end(), compareByBurstTime);

    // //FOR DEBUG, PRINT ALL PROCESSES IN ORDER
    // for(int x = 0; x < int(queue.size()); x++){
    //     std::cout << "Process ID:" << queue[x].getID() << ", Burst Time: " << queue[x].getTotalTime() << std::endl;
    // }

    //TOTALS OF ALL TIMES
    time_type allProcessWaitTime = 0;
    time_type allProcessTurnAroundtime = 0;
    time_type allProcessResponseTime = 0;

    //varialbe to calculate and store the turn around time for each process.
    time_type currTurnArTime = 0;
    
    //Keep track of current time.
    time_type currentTime = 0;

    //Go through the queue of processes, satrting with first in.
    for(int x = 0; x < int(queue.size()); x++){
        //Set wait time to total time used by program (acuumulated burst times)
        queue[x].setTotalWaitTime(currentTime);

        //Add this procces' burst time to current time.
        currentTime += queue[x].getTotalTime();

        //Calculate turn around time for this process.
        currTurnArTime = queue[x].getTotalWaitTime() + queue[x].getTotalTime();

        // // FOR DEBUG Print current proccess information.
        // std::cout << "Process " << queue[x].getID() << ": Burst Time = " << queue[x].getTotalTime()
        //      << ", Turnaround Time = " << currTurnArTime
        //      << ", Waiting Time = " << queue[x].getTotalWaitTime()
        //      << ", Response Time = " << queue[x].getTotalWaitTime() << std::endl;
        
        //Add to all totals.
        allProcessWaitTime += long(queue[x].getTotalWaitTime());
        allProcessResponseTime +=long(queue[x].getTotalWaitTime());
        allProcessTurnAroundtime += (long(queue[x].getTotalWaitTime()) + long(queue[x].getTotalTime()));

    }

    //Calculate Averages.
    int numProcesses = int(queue.size());
    time_type waitAverage = allProcessWaitTime/numProcesses;
    time_type turnAroundAverage = allProcessTurnAroundtime/long(queue.size());
    time_type responseAverage = allProcessResponseTime / long(queue.size());

    //Print final information.
    std::cout << std::endl;
    std::cout << "Results:" << std::endl;
    std::cout << "Number of Processes: " << numProcesses << std::endl;
    std::cout << "Average Waiting Time: " << waitAverage << std::endl;
    std::cout << "Average Turnaround Time: " << turnAroundAverage << std::endl;
    std::cout << "Average Response Time: " << responseAverage << std::endl;

    return EXIT_SUCCESS;
}