//__________________________________________________________________________
// Author(s): Claudio Pizzolato, Monica Reggiani - June 2014
// email:  claudio.pizzolato@griffithuni.edu.au
//         monica.reggiani@gmail.com
//
// DO NOT REDISTRIBUTE WITHOUT PERMISSION
//__________________________________________________________________________
//

#include "LoggerOnQueues.h"
#include "OutputQueues.h"
#include <vector>
#include <string>
#include <iostream>

LoggerOnQueues::LoggerOnQueues(const std::vector< std::string >& valuesToLog) 
{
  
    for (auto& it: valuesToLog) 
        CEINMS::OutputConnectors::logQueues.insert(std::make_pair(it, new CEINMS::Concurrency::Queue< CEINMS::OutputConnectors::FrameType>) ); 

  
}

void LoggerOnQueues::log(double time, const CEINMS::OutputConnectors::DataType& dataToLog, const std::string& valueToLog)
{
  
    CEINMS::OutputConnectors::FrameType dataToPush;
    dataToPush.data = dataToLog; 
    dataToPush.time = time; 
    
    auto currentQueue = CEINMS::OutputConnectors::logQueues.find(valueToLog);

    if (currentQueue == CEINMS::OutputConnectors::logQueues.end()) {
        std::cout << "queue for " << valueToLog << " was not found\n";
        exit(EXIT_FAILURE);
    }
    else 
        currentQueue->second->push(dataToPush);   

  
}

