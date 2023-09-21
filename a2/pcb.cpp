#include "pcb.h"

const osp2023::id_type pcb::getID(){
    return id;
}

void pcb::setID(osp2023::id_type id){
    this->id = id;
}

const osp2023::time_type pcb::getTotalTime(){
    return total_time;
}

void pcb::setTotalTime(osp2023::time_type totalTime){
    this->total_time = totalTime;
}

const osp2023::time_type pcb::getTimeUsed(){
    return time_used;
}

void pcb::setTimeUsed(osp2023::time_type timeUsed){
    this->time_used = timeUsed;
}

const osp2023::time_type pcb::getTotalWaitTime(){
    return total_wait_time;
}

void pcb::setTotalWaitTime(osp2023::time_type totalWaitTime){
    this->total_wait_time = totalWaitTime;
}


