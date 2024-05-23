#ifndef LEVELS_H
#define LEVELS_H

#include <cstddef>
#include "player.h"
#include <vector>

class level {
public:
    level() : rows(0), columns(0), m_data(0) {}

    level(size_t rows, size_t columns, std::vector<std::vector<char>>& data) {
        this->rows = rows;
        this->columns = columns;
        this->m_data = data;
    }

    ~level() {
        rows = 0;
        columns = 0;
        m_data.clear();
    }


    [[nodiscard]]bool is_cell_inside_level(int row, int column) const {
        return row < rows && column < columns;
    }

    char &get_level_cell(size_t row, size_t column) {
        return m_data[row][column];
    }

    void set_level_cell(size_t row, size_t column, char cell) {
        m_data[row][column] = cell;
    }

    void load_next_level(player &player1);

    void derive_graphics_metrics_from_loaded_level() const;

    [[nodiscard]] size_t get_rows() const {
        return rows;
    }

    [[nodiscard]] size_t get_columns() const {
        return columns;
    }

    [[nodiscard]] std::vector<std::vector<char>> get_data() const {
        return m_data;
    }

    void set_rows(const size_t& other){
        rows = other;
    }

    void set_columns(const size_t& other){
        columns = other;
    }

    void set_data(const std::vector<std::vector<char>>& other) {
        m_data = other;
    }

    void draw_loaded_level();

    static void draw_level_label();


    void pushback(std::vector<char> row) {
        m_data.push_back(row);
    }


private:
    size_t rows;
    size_t columns;
    std::vector<std::vector<char>> m_data;
};

#endif // LEVELS_H
