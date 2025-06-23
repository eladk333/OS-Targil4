#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <string>
#include <vector>

struct ProducerConfig {
    int id;
    int messageCount;
    int queueSize;
};

struct Config {
    std::vector<ProducerConfig> producers;
    int coEditorQueueSize;
};

Config parse_config(const std::string& filename);

#endif
