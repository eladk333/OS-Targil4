#include "ConfigParser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

Config parse_config(const std::string& filename) {
    Config config;
    std::ifstream infile(filename);
    std::string line;
    ProducerConfig current;

    while (std::getline(infile, line)) {
        if (line.find("PRODUCER") != std::string::npos) {
            std::istringstream iss(line);
            std::string dummy;
            iss >> dummy >> current.id;
            std::getline(infile, line);
            current.messageCount = std::stoi(line);
            std::getline(infile, line);
            size_t eq = line.find('=');
            current.queueSize = std::stoi(line.substr(eq + 1));
            config.producers.push_back(current);
        } else if (line.find("Co-Editor queue size") != std::string::npos) {
            size_t eq = line.find('=');
            config.coEditorQueueSize = std::stoi(line.substr(eq + 1));
        }
    }

    return config;
}
