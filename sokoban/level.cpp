#include "level.h"

void level::derive_graphics_metrics_from_loaded_level() const {
    screen_width = static_cast<float>(GetScreenWidth());
    screen_height = static_cast<float>(GetScreenHeight());

    cell_size = std::min(
            screen_width / static_cast<float>(columns),
            screen_height / static_cast<float>(rows)
    ) * CELL_SCALE;
    screen_scale = std::min(
            screen_width,
            screen_height
    ) / SCREEN_SCALE_DIVISOR;
    float level_width = static_cast<float>(columns) * cell_size;
    float level_height = static_cast<float>(rows) * cell_size;
    shift_to_center_cell_by_x = (screen_width - level_width) * 0.5f;
    shift_to_center_cell_by_y = (screen_height - level_height) * 0.5f;
}

void level::draw_loaded_level() {
    ClearBackground(BLACK);

    for (size_t row = 0; row < rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            float x = shift_to_center_cell_by_x + static_cast<float>(column) * cell_size;
            float y = shift_to_center_cell_by_y + static_cast<float>(row) * cell_size;

            char cell = get_level_cell(row, column);
            switch (cell) {
                case FLOOR:
                case GOAL:
                case BOX:
                case BOX_ON_GOAL:
                    draw_image(floor_image, x, y, cell_size);
                default:
                    break;
            }
            switch (cell) {
                case WALL:
                    draw_image(wall_image, x, y, cell_size);
                    break;
                case GOAL:
                    draw_image(goal_image, x, y, cell_size);
                    break;
                case BOX:
                    draw_image(box_image, x, y, cell_size);
                    break;
                case BOX_ON_GOAL:
                    draw_image(box_on_goal_image, x, y, cell_size);
                    break;
                default:
                    break;
            }
        }
    }
}

void level::draw_level_label() {
    {
        const float level_font_size = GAME_LEVEL_FONT_SIZE * screen_scale;
        const float level_top_margin = GAME_LEVEL_Y_SHIFT * screen_scale;

        std::string level_text = std::string("Level ");
        level_text += std::to_string(level_index + 1);
        level_text += " out of ";
        level_text += std::to_string(LEVEL_COUNT);

        Vector2 level_size = MeasureTextEx(menu_font, level_text.c_str(), level_font_size, 1);
        Vector2 level_position = {(screen_width - level_size.x) * 0.5f, level_top_margin};
        DrawTextEx(menu_font, level_text.c_str(), level_position, level_font_size, 1, GAME_LEVEL_COLOR1);
        level_position.x -= 4 * screen_scale;
        level_position.y -= 4 * screen_scale;
        DrawTextEx(menu_font, level_text.c_str(), level_position, level_font_size, 1, GAME_LEVEL_COLOR2);
    }
}

void level::load_next_level(player &player1) {
    if (level_index >= LEVEL_COUNT) {
        level_index = 0;
        game_state = VICTORY_STATE;
        create_victory_menu_background();
        return;
    }

    for (size_t row = 0; row < rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            char cell = LEVELS[level_index].m_data[row][column];
            if (cell == PLAYER) {
                set_level_cell(row, column, FLOOR);
                player1.spawn_player(row, column);
            } else if (cell == PLAYER_ON_GOAL) {
                set_level_cell(row, column, GOAL);
                player1.spawn_player(row, column);
            } else {
                set_level_cell(row, column, cell);
            }
        }
    }

    derive_graphics_metrics_from_loaded_level();
}