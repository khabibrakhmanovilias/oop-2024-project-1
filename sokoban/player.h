#ifndef PLAYER_H
#define PLAYER_H

#include <cstddef>

class player {
public:
    player() {
        player_row = 0;
        player_column = 0;
    }

    void spawn_player(size_t row, size_t column) {
        player_row = row;
        player_column = column;
    }

    void move_player(player &player, int dx, int dy);

    void draw_player() const;

private:
    size_t player_row;
    size_t player_column;
};

#endif // PLAYER_H
