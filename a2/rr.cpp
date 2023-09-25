//Round Robin Scheduling Algorithm

#include "pcb.h"
#include "types.h"
#include "loader.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace osp2023;

int main(int argc, char *argv[]){
    
    //check number of arguments. (HAS TO BE 2)
    if(argc != 3){
        std::cout << "Valid usage: ./rr <quantum> <data file name> \n Exiting Program" << std::endl;
        return EXIT_FAILURE;
    }

    //Open datafile in a fsteam
    std::string data_file_name = argv[2];
    std::fstream dataFile;
    dataFile.open(data_file_name);

    //Exit program if data file is not open in fstream
    if(!dataFile){
        std::cout << "Data file not valid or doesnt exist. \n Exiting Program." << std::endl;
        return EXIT_FAILURE;
    }

    //UNCOMMENT WHEN LOADER IMPLEMENTED
    //dataFile.close();

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
        process.setTimeUsed(0);
        process.setTotalWaitTime(0);
        process.setResponseTime(-1);
        readyQueue.push_back(process);
    }

    int numProcesses = int(readyQueue.size());

    //keep track of crrent time.
    time_type allProcessWaitTime = 0;
    time_type allProcessTurnAroundtime = 0;
    time_type allProcessResponseTime = 0;
    
    //All used up time.
    time_type currentTime = 0;

    //Pre defined variables, for calculation in the loop.
    time_type timeSlice = 0;
    time_type remainingTime = 0;

    //Go through the readyQueue of processes, satrting with first in.
    while(!readyQueue.empty()){
        pcb currentProcess = readyQueue.front();
        readyQueue.erase(readyQueue.begin());

        //Add to total response time if this is the first signal for process.
        if(currentProcess.getResponseTime() == -1){
            currentProcess.setResponseTime(currentTime);
            allProcessResponseTime += currentTime;
        }

        //Determine the time slice of the process, then add to process' total used time.
        remainingTime = currentProcess.getTotalTime() - currentProcess.getTimeUsed();
        timeSlice = std::min(quantum, remainingTime);
        currentProcess.setTimeUsed(currentProcess.getTimeUsed() + timeSlice);

        //Add time slice to total time used.
        currentTime += timeSlice;
        
        //Check if process has finished execution.
        if(currentProcess.getTimeUsed() >= currentProcess.getTotalTime()){

            //Calculate and add this process' TA time to total
            time_type TA_time = currentTime;
            time_type wait_time = TA_time - currentProcess.getTimeUsed();
            currentProcess.setTotalWaitTime(wait_time);
            allProcessTurnAroundtime += TA_time;
            allProcessWaitTime += wait_time;

            
            std::cout << "Process ID: " << currentProcess.getID() << ", Burst Time: " << currentProcess.getTotalTime()
                      << ", Waiting time: " << currentProcess.getTotalWaitTime()
                      << ", Response Time: " << currentProcess.getResponseTime()
                      << ", Turn-around time: " << TA_time << std::endl;
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
    std::cout << "\033[1;32m" << "Round Robin Scheduling Results:" << "\033[0m" << std::endl;
    std::cout << "\033[34m" << "Number of Processes: " << numProcesses << std::endl;
    std::cout << "Quantum Size: " << quantum << "\033[0m" <<std::endl;
    std::cout << "\033[32m" << "Average Waiting Time: " << waitAverage << "ms" << std::endl;
    std::cout << "Average Response Time: " << responseAverage << "ms" << std::endl;
    std::cout << "Average Turnaround Time: " << turnAroundAverage << "ms" << "\033[0m" << std::endl;
    std::cout << std::endl;

    return EXIT_SUCCESS;
}