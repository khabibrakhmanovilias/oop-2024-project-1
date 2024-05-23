#include "player.h"
#include "globals.h"

void player::move_player(player &player1, int dx, int dy) {
    int next_row = static_cast<int>(player_row) + dy;
    int next_column = static_cast<int>(player_column) + dx;
    if (!LEVELS[level_index].is_cell_inside_level(next_row, next_column)) {
        return;
    }

    char &cell = LEVELS[level_index].get_level_cell(static_cast<size_t>(next_row), static_cast<size_t>(next_column));
    if (cell == FLOOR || cell == GOAL) {
        player_row = static_cast<size_t>(next_row);
        player_column = static_cast<size_t>(next_column);
    } else if (cell == BOX || cell == BOX_ON_GOAL) {
        int target_row = next_row + dy;
        int target_column = next_column + dx;
        if (!LEVELS[level_index].is_cell_inside_level(target_row, target_column)) {
            return;
        }
        char &target_cell = LEVELS[level_index].get_level_cell(static_cast<size_t>(target_row), static_cast<size_t>(target_column));
        if (target_cell == FLOOR || target_cell == GOAL) {
            cell = cell == BOX ? FLOOR : GOAL;
            if (target_cell == FLOOR) {
                target_cell = BOX;
            } else {
                target_cell = BOX_ON_GOAL;
                play_sound(goal_sound);
            }

            player_row = static_cast<size_t>(next_row);
            player_column = static_cast<size_t>(next_column);

            bool level_solved = true;
            for (size_t row = 0; level_solved && row < LEVELS[level_index].get_rows(); ++row) {
                for (size_t column = 0; level_solved && column < LEVELS[level_index].get_columns(); ++column) {
                    char cell_to_test = LEVELS[level_index].get_level_cell(row, column);
                    if (cell_to_test == GOAL) {
                        level_solved = false;
                    }
                }
            }

            if (level_solved) {
                ++level_index;
                LEVELS[level_index].load_next_level(player1);
                play_sound(exit_sound);
            }
        }
    }
}



void player::draw_player() const {
    {
        float x = shift_to_center_cell_by_x + static_cast<float>(player_column) * cell_size;
        float y = shift_to_center_cell_by_y + static_cast<float>(player_row) * cell_size;
        draw_sprite(player_sprite, x, y, cell_size);
    }
}