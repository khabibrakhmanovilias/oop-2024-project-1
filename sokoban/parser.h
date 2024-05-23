#ifndef PARSER_H
#define PARSER_H

#include "level.h"
#include <sstream>
#include <fstream>
#include <array>
#include <iomanip>
#include <iostream>

level decode_level(const std::string &line) {
    level level;
    std::istringstream iss(line);
    std::string segment;
    size_t row_count = 0;
    std::vector<std::vector<char>> data;

    while(getline(iss, segment, '|')) {
        std::vector<char> row;
        int i = 0;
        while (i < segment.length()) {
            int count = 0;
            while (i < segment.length() && std::isdigit(segment[i])) {
                count = count * 10 + (segment[i] - '0');
                i++;
            }
            if(count == 0) count = 1;
            if(i < segment.length()){
                while(count > 0){
                    row.push_back(segment[i]);
                    count--;
                }
            }
            ++i;
        }
        data.push_back(row);
        row_count++;
    }
    size_t max_length = 0;
    for (const auto& row : data) {
        max_length = std::max(max_length, row.size());
    }
    level.set_columns(max_length);
    level.set_rows(row_count);

    for (auto& row : data) {
        while (row.size() < max_length) {
            row.push_back(' ');
        }
    }

    level.set_data(data);

    return level;
}

std::vector<level> parse_sokoban_levels (const std::string &filename) {
    std::ifstream file(filename);
    std::vector<level> levels;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        return levels;
    }

    while(getline(file, line)){
        if(line.empty() || line[0] == ';'){
            continue;
        }
        levels.push_back(decode_level(line));
    }

    file.close();
    return levels;
}

#endif //PARSER_H
