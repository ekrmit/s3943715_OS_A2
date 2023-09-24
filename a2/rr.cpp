//Round Robin Scheduling Algorithm

#include "pcb.h"
#include "types.h"
#include "loader.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace osp2023;

bool isNumber (std::string line){
    if (isdigit(atoi(line.c_str())))
        return true;
    return false;
}

int main(int argc, char *argv[]){
    
    //check number of arguments. (HAS TO BE 2)
    if(argc != 3){
        std::cout << "Valid usage: ./rr <quantum> <data file name> \n Exiting Program" << std::endl;
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

    //UNCOMMENT WHEN LOADER IMPLEMENTED
    //dataFile.close();

    if(!isNumber(argv[1])){
        std::cout << "The input quantumn is not a valid number. \n Exiting Program." << std::endl;
        return EXIT_FAILURE;
    }

    //Create the qunatum from input arg.
    time_type quantum = std::stoi(argv[1]);

    //Create processes.
    std::vector<pcb> readyQueue;
    std::string pcbParams;
    std::string delimiter = ",";

    while( getline(dataFile, pcbParams) ){
        //get ID from data line
        id_type pID = std::stoi(pcbParams.substr(0, pcbParams.find(delimiter)));

        //get burst time from data line
        std::string burstString = pcbParams.substr(pcbParams.find(delimiter) + 1, pcbParams.length());
        time_type burstTime = std::stoi(burstString);

        //create the process and set variables
        pcb process;
        process.setID(pID);
        process.setTotalTime(burstTime);
        readyQueue.push_back(process);
    }

    int numProcesses = int(readyQueue.size());

    //keep track of crrent time.
    time_type allProcessWaitTime = 0;
    time_type allProcessTurnAroundtime = 0;
    time_type allProcessResponseTime = 0;
    
    //All used up time.
    time_type currentTime = 0;

    //Go through the readyQueue of processes, satrting with first in.
    while(!readyQueue.empty()){
        pcb currentProcess = readyQueue.front();
        readyQueue.erase(readyQueue.begin());

        //Add to total response time if this is the first signal for process.
        if(currentProcess.getTimeUsed() == 0){
            allProcessResponseTime += currentTime;
        }

        //Determine the time slice of the process, then add to process' total used time.
        time_type timeSlice = std::min(quantum, (currentProcess.getTotalTime() - currentProcess.getTimeUsed()) );
        currentProcess.setTimeUsed(currentProcess.getTimeUsed() + timeSlice);

        //Calcuate the wait time for this cycle
        time_type currUsedTime = currentTime - currentProcess.getTotalWaitTime();
        currentProcess.setTotalWaitTime(currUsedTime);

        //Add time slice to total time used.
        currentTime += timeSlice;

        //FOR DEBUGGING!!!, REMOVE ME LATER!!!
        std::cout << "CURRENT PROCESS, ID: " << currentProcess.getID() << ", BT: " << currentProcess.getTimeUsed() << std::endl;
        std::cout << "Time slice: " << timeSlice << ", Cycle wait time: " << currUsedTime 
                  << ", Curr wait total: " << currentProcess.getTotalWaitTime() << std::endl;
        std::cout << std::endl;
        
        //Check if process has finished execution.
        if(currentProcess.getTimeUsed() >= currentProcess.getTotalTime()){
            
            //Add this finished process' total wait time to all process total.
            allProcessWaitTime += currentProcess.getTotalWaitTime();

            //Calculate and add this process' TA time to total
            time_type TA_time = currentProcess.getTotalTime() + currentProcess.getTotalWaitTime();
            allProcessTurnAroundtime += TA_time;

            //FOR DEBUGGING!! REMOVE ME LATER!
            std::cout << "\033[1;31m" << "PROCESS COMPLETE. ID: " << currentProcess.getID() 
                                                      << ", BT: " << currentProcess.getTotalTime() << std::endl;
            std::cout << "Process wait time: " << currentProcess.getTotalWaitTime() << std::endl;
            std::cout << "Process TA time: " << TA_time << "\033[1;0m" << std::endl;

        }

        else{
            //If process not complete, add to the back of ready queue.
            readyQueue.push_back(currentProcess);
        }

    }

    //Calculate Averages for  
    time_type waitAverage = allProcessWaitTime/numProcesses;
    time_type turnAroundAverage = allProcessTurnAroundtime/numProcesses;
    time_type responseAverage = allProcessResponseTime / numProcesses;

    std::cout << std::endl;
    std::cout << "Results:" << std::endl;
    std::cout << "Number of Processes: " << numProcesses << std::endl;
    std::cout << "Average Waiting Time: " << waitAverage << std::endl;
    std::cout << "Average Turnaround Time: " << turnAroundAverage << std::endl;
    std::cout << "Average Response Time: " << responseAverage << std::endl;

    return EXIT_SUCCESS;
}