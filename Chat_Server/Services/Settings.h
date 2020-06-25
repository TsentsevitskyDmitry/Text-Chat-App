#ifndef SETTINGS_H
#define SETTINGS_H

#include "Models/ServerConfig.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <iostream>

namespace pt = boost::property_tree;

class Settings {
private:
    static constexpr char filepath[] = "C:\\ChatServer\\config.xml";

public:
    static bool getConfig(ServerConfig& config);
};

#endif // SETTINGS_H
