#include "Settings.h"

bool Settings::getConfig(ServerConfig& config)
{
    std::string port;
    pt::ptree tree;
    try {
        pt::read_xml(filepath, tree);
        port = tree.get<std::string>("chat_server.port");
    }
    catch (const pt::ptree_error & ex)
    {
        std::cout << ex.what() << std::endl;
        port = "27015";
        tree.put("chat_server.port", port);
        std::ofstream file(filepath);
        file.close();
        pt::write_xml(filepath, tree);
        return false;
    }
    config.setPort(port);
    return true;
}
