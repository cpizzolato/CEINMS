//__________________________________________________________________________
// Author(s): Claudio Pizzolato, Monica Reggiani - March 2015
// email:  claudio.pizzolato@griffithuni.edu.au
//
// DO NOT REDISTRIBUTE WITHOUT PERMISSION
//__________________________________________________________________________
//


#ifndef Ceinms_SimulationManager_h
#define Ceinms_SimulationManager_h
#include "SetupDataStructure.h"
#include "CeinmsSetupXmlReader.h"
#include "InputDataXmlReader.h"
#include "ExecutionXmlReader.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>

namespace CEINMS {
    class SimulationManager {

    public:
        SimulationManager(const std::string& setupFilename);
        bool run();

    private:
        template <typename NMSmodelT, template <typename, typename> class ModelEvaluatorT, typename LoggerT>
        bool runOpenLoop();

        template <typename T>
        bool runHybrid();

       
        CeinmsSetupXmlReader ceinmsSetup_;
        InputDataXmlReader dataLocations_;
        ExecutionXmlReader executionCfg_;
        std::string subjectFile_;
        std::string executionFile_;
        std::string inputData_;
        std::string outputDirectory_;
        std::string emgGeneratorFile_;



    };



    void sortMaFilenames(const std::map<std::string, std::string>& maMap, const std::vector< std::string >& dofNames, std::vector< std::string >& maDataFilenames)
    {
        int currentDof = 0;
        for (auto& it : dofNames)
        {
            try
            {
                maDataFilenames.push_back(maMap.at(it));
            }
            catch (std::out_of_range)
            {
                std::cerr << "Could not find moment arm file for " << it << " degree of freedom" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}


#include "SimulationManager.cpp"
#endif