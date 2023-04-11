#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

//checkAvail
bool checkAvail(size_t day, size_t worker, const AvailabilityMatrix& avail);

//checkShifts
bool checkShifts(unsigned int worker, std::map<size_t, size_t>& shiftsMap);

//schedSolve
bool schedSolve(size_t row, size_t col, const size_t dailyNeed, std::map<size_t, size_t>& shiftsMap, const AvailabilityMatrix& avail, DailySchedule& sched);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below

    

    //1. initialize sched to empty
    vector<Worker_T> emptyVec(dailyNeed, INVALID_ID);
    vector<vector<Worker_T>> temp (avail.size(), emptyVec);
    sched = temp;

    //2. create shifts map
    std::map<size_t, size_t> shiftsMap;
    for(size_t i = 0; i < avail[0].size(); i++){
        shiftsMap[i] = maxShifts;
    }

    //3. call recursive function
    bool result = schedSolve(0, 0, dailyNeed, shiftsMap, avail, sched);

    //4. return either true or false
    return result;

}

//schedSolve
/*

    Helper function that fills in sched and returns true if possible solution, false if no possible solution

*/
bool schedSolve(size_t row, size_t col, const size_t dailyNeed, std::map<size_t, size_t>& shiftsMap, const AvailabilityMatrix& avail, DailySchedule& sched){

    //1. Base Case --> row goes past #days = avail.size()
    if(row >= avail.size()){
        return true;
    }
    //2. end of row
    else if(col >= dailyNeed){
        //row goes down 1 (starts at beginning of row)
        return schedSolve(row+1, 0, dailyNeed, shiftsMap, avail, sched);
    }
    //3. if index has not been filled
    else if(sched[row][col] == INVALID_ID){
        //A. iterate through workers
        for(unsigned int worker = 0; worker < avail[0].size(); worker++){
            //set current spot to current worker
            sched[row][col] = worker;

            //check if valid
            if(checkAvail(row, worker, avail) && checkShifts(worker, shiftsMap)){
                //1. decrement map
                shiftsMap[worker]--;

                //2. check next step
                if(schedSolve(row, col+1, dailyNeed, shiftsMap, avail, sched)){
                    return true;
                }

                //3. reincrement map to backtrack
                shiftsMap[worker]++;
            }
        }

        //backtrack if can't find solution
        sched[row][col] = INVALID_ID;

        //return false cause invalid branch
        return false;
    }

    //return false if end is reached
    return false;

}


//checkAvail
bool checkAvail(size_t day, size_t worker, const AvailabilityMatrix& avail){
    return avail[day][worker];
}

//checkShifts
bool checkShifts(unsigned int worker, std::map<size_t, size_t>& shiftsMap){
    if(shiftsMap[worker] == 0){
        return false;
    }
    else{
        return true;
    }
}

