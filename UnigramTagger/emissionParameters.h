#ifndef EMISSIONPARAMETER_H
#define EMISSIONPARAMETER_H


std::map<std::vector<std::string>, double> emissionParameters(const std::string);

std::map<std::string,std::string> findMaxEmission(std::map<std::vector<std::string>, double>);


#endif

