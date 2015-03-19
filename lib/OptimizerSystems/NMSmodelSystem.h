#ifndef Ceinms_NMSmodelSystem_h
#define Ceinms_NMSmodelSystem_h

#include "AbstractOptimizerSystem.h"

#include "ParametersInterpreter.h" //TODO: rename this class
#include <vector>

namespace CEINMS {
    template <typename NMSmodelT, typename ModelEvaluatorT, typename ObjectiveFunctionT>
    class NMSmodelSystem : public Optimizers::AbstractOptimizerSystem  {
    public:
        NMSmodelSystem(NMSmodelT& subject, const ModelEvaluatorT& modelEvaluatior, const ObjectiveFunctionT& objectiveFunction, const Parameter::ParameterSet& parameterSet);
        virtual ~NMSmodelSystem() {}
        void setDofsToCalibrate(const std::vector<std::string>& dofsToCalibrate);
        void evaluate();
        void setParameters(const std::vector<double>& x);
        std::vector<double> getParameters();
        double getF() const { return f_; }
        size_t getNoParameters() { return parameterInterpreter_.getNoParameters(); }
        void getUpperLowerBounds(std::vector<double>& upperBounds, std::vector<double>& lowerBounds) const; 


    private:

        NMSmodelT& subject_;
        ModelEvaluatorT modelEvaluator_;
        ObjectiveFunctionT objectiveFunction_;
        ParametersInterpreter<NMSmodelT> parameterInterpreter_;
        std::vector<std::string> dofsToCalibrate_;
        double f_;
    };
}


//#include "NMSmodelSystem.cpp"
#endif