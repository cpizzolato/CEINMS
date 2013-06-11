#ifndef StiffTendon_h
#define StiffTendon_h
#include "Curve.h"
#include <string>


class StiffTendon {
    
public:
    typedef Curve<CurveMode::Offline> CurveOffline;
    StiffTendon();
    StiffTendon(std::string id);
    StiffTendon( double optimalFibreLength,
                   double pennationAngle,
                   double tendonSlackLength,
                   double percentageChange,
                   double damping,
                   double maxIsometricForce, 
                   double strengthCoefficient,
                   const CurveOffline& activeForceLengthCurve,
                   const CurveOffline& passiveForceLengthCurve, 
                   const CurveOffline& forceVelocityCurve
                 );
    virtual ~StiffTendon();

    
    void setParametersToComputeForces(double optimalFibreLength,
                                      double pennationAngle,
                                      double tendonSlackLength,
                                      double percentageChange,
                                      double damping, 
                                      double maxIsometricForce, 
                                      double strengthCoefficient); 

    void setTime(const double& time) {} // it is useless in the stiff tendon, but I need to respect the interface
    void setMuscleTendonLength(double muscleTendonLength);
    void setActivation(double activation);
    void updateFibreLength();

    double getFibreLength() { return fibreLength_;}
    void setStrengthCoefficient(double strengthCoefficient) { };
    void setTendonSlackLength(double tendonSlackLength) { tendonSlackLength_ = tendonSlackLength; }
    void setCurves(const CurveOffline& activeForceLengthCurve, 
                   const CurveOffline& passiveForceLengthCurve, 
                   const CurveOffline& forceVelocityCurve) { };
    void setTendonForceStrainCurve(const CurveOffline& tendonForceStrainCurve) { };
                   
    void pushState() {};
    void resetState();

private:
    double optimalFibreLength_;
    double percentageChange_;
    double pennationAngle_;
    double tendonSlackLength_;
    
    double fibreLength_;
    double muscleTendonLength_;
    double activation_;
    
    std::string id_;
    
};

#endif