#ifndef ExecutionXmlReader_h
#define ExecutionXmlReader_h

#include <string>
#include <vector>
#include "NMSmodelConfig.h"
#include "execution.hxx"


class ExecutionXmlReader {
    
public:
    ExecutionXmlReader(const std::string& filename);
    NMSModelCfg::RunMode getRunMode() const;
    void getMusclesToPredict(std::vector<std::string>& musclesToPredict);
    void getMusclesToTrack(std::vector<std::string>& musclesToTrack);
    void getHybridWeightings(double& alpha, double& beta, double& gamma);
	void getAnnealingParameters(unsigned& nt, unsigned& ns, double& rt, double& t, unsigned& maxNoEval, double& epsilon, unsigned& noEpsilon) const;
    
private:
    void readXml();
    
    unsigned runMode_;
    std::auto_ptr<ExecutionType> executionPointer_;
};

#endif