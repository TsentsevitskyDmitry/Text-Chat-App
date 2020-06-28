#include "Settings.h"

void Settings::fileNotFound(pt::ptree& tree, std::string& port)
{
    port = default_port;
    tree.put("chat_server.port", port);
    try {
        std::ofstream file(filepath);
        file.close(); // Create file
        pt::write_xml(filepath, tree);
    } catch (...) {
        // nothing to do
    }
}

bool Settings::getConfig(ServerConfig& config)
{
    bool success = false;
    std::string port;
    pt::ptree tree;
    try {
        pt::read_xml(filepath, tree);
        port = tree.get<std::string>("chat_server.port");
    }
    catch (const pt::ptree_error & ex)
    {
        fileNotFound(tree, port);
    }
    config.setPort(port);
    return success;
}
