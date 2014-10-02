//__________________________________________________________________________
// Author(s): Elena Ceseracciu - August 2014
// email:  elena.ceseracciu@gmail.com
//
// DO NOT REDISTRIBUTE WITHOUT PERMISSION
//__________________________________________________________________________
//

#include <string>
using std::string;
#include <map>
using std::map;
#include <iostream>
using std::cout;
using std::endl;

#include "CeinmsCalibrationSetupXmlReader.h"
#include "validation.h"
#include <boost/algorithm/string.hpp>
#include "ceinmsCalibrationSetup-schema.hxx"

inline bool isAbsolute(const char *path) {
    if (path[0] == '/' || path[0] == '\\') {
        return true;
    }
    std::string str(path);
    if (str.length()>1) {
        if (str[1] == ':') {
            return true;
        }
    }
    return false;
};

static void trim(std::string& fileName)
{
    boost::trim(fileName);
    boost::trim_if(fileName, boost::is_any_of("\""));
};

CeinmsCalibrationSetupXmlReader::CeinmsCalibrationSetupXmlReader(const string& filename)
{

    try {
        std::auto_ptr<CeinmsCalibrationType> ceinmsCalibrationDataPointer(parseAndValidate<CeinmsCalibrationType>(filename, ceinmsCalibrationSetup_schema, sizeof(ceinmsCalibrationSetup_schema)));
        ceinmsCalibrationSetupPointer_ = ceinmsCalibrationDataPointer;
    }
    catch (const xml_schema::exception& e) {
        cout << e << endl;
        exit(EXIT_FAILURE);
    }

    // save the location of input filename
    string::size_type dirSep = filename.rfind('/'); // Unix/Mac dir separator

    if (dirSep == string::npos)
        dirSep = filename.rfind('\\'); // DOS dir separator

    if (dirSep != string::npos) // if '_fileName' contains path information...
        filepath_ = filename.substr(0, dirSep + 1); // include trailing slashes

    readXml();
}

void CeinmsCalibrationSetupXmlReader::readXml() {

    try {
        std::string& mySubjectFile(*(ceinmsCalibrationSetupPointer_->subjectFile().begin()));
        std::string& myCalibrationExecutionFile(*(ceinmsCalibrationSetupPointer_->calibrationFile().begin()));
        std::string& myEmgGeneratorFile(*(ceinmsCalibrationSetupPointer_->excitationGeneratorFile().begin()));
        std::string& myOutputSubjectFile(*(ceinmsCalibrationSetupPointer_->outputSubjectFile().begin()));

    }
    catch (const xml_schema::exception& e) {
        cout << e << endl;
        exit(EXIT_FAILURE);
    }
}

std::string CeinmsCalibrationSetupXmlReader::getSubjectFile()
{
    std::string fileName(*(ceinmsCalibrationSetupPointer_->subjectFile().begin()));
    trim(fileName);
    if (isAbsolute(fileName.c_str()))
        return fileName;
    else
        return filepath_ + fileName;
}

std::string CeinmsCalibrationSetupXmlReader::getCalibrationFile()
{
    std::string fileName(*(ceinmsCalibrationSetupPointer_->calibrationFile().begin()));
    trim(fileName);
    if (isAbsolute(fileName.c_str()))
        return fileName;
    else
        return filepath_ + fileName;
}

std::string CeinmsCalibrationSetupXmlReader::getExcitationGeneratorFile()
{
    std::string fileName(*(ceinmsCalibrationSetupPointer_->excitationGeneratorFile().begin()));
    trim(fileName);
    if (isAbsolute(fileName.c_str()))
        return fileName;
    else
        return filepath_ + fileName;
}

std::string CeinmsCalibrationSetupXmlReader::getOutputSubjectFile()
{
    std::string fileName(*(ceinmsCalibrationSetupPointer_->outputSubjectFile().begin()));
    trim(fileName);
    if (isAbsolute(fileName.c_str()))
        return fileName;
    else
        return filepath_ + fileName;
}

bool CeinmsCalibrationSetupXmlReader::writeTemplateCeinmsCalibrationSetupFile(const std::string& templateFile)
{
    std::ofstream templateFileStream(templateFile);
    if (!templateFileStream.is_open())
        return false;
    CeinmsCalibrationType templateCeinmsSetup;
    templateCeinmsSetup.subjectFile().push_back("subjectUncalibrated.xml");
    templateCeinmsSetup.calibrationFile().push_back("calibration.xml");
    templateCeinmsSetup.excitationGeneratorFile().push_back("excitationGenerator.xml");
    templateCeinmsSetup.outputSubjectFile().push_back("subjectCalibrated.xml");
    ceinmsCalibration(templateFileStream, templateCeinmsSetup);
    templateFileStream.close();
    return true;
}
