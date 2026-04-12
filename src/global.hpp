#ifndef H_GLOBALS
#define H_GLOBALS

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"

inline bool exitGame = false;

enum GameMenuState { GMSTATE_MAIN, GMSTATE_GAME, GMSTATE_SHOP, GMSTATE_DEATH };

namespace Const_Map {
    inline constexpr int size = 100;
    inline constexpr int center = size / 2;
    inline constexpr float tile_size = 100.0f;
    inline constexpr float cell_center_offset = 0.5f;
    inline constexpr float spawn_safe_radius = 5.0f;
    inline constexpr int tree_spawn_roll_min = 0;
    inline constexpr int tree_spawn_roll_max = 6;
    inline constexpr int tree_spawn_roll_hit = 3;
}

namespace Const_Render {
    inline constexpr int width = 800;
    inline constexpr int height = 600;
    inline constexpr int target_fps = 32;
}

namespace Const_Player {
    inline constexpr float speed = 200.0f;
    inline constexpr int animation_frame_real_max = 8;
    inline constexpr float sprite_unit_px = 32.0f;
    inline constexpr float hitbox_left_units = 10.0f;
    inline constexpr float hitbox_top_units = 4.0f;
    inline constexpr float hitbox_right_units = 20.0f;
    inline constexpr float hitbox_bottom_units = 8.0f;
    inline constexpr float camera_follow_margin = 100.0f;
    inline constexpr float camera_follow_threshold_x = 100.0f;
    inline constexpr float camera_follow_threshold_y = 75.0f;
    inline constexpr float camera_follow_y_scale = 0.75f;
}

namespace Const_Camera {
    inline constexpr float initial_zoom = 0.5f;
}

#pragma clang diagnostic pop
#endif
