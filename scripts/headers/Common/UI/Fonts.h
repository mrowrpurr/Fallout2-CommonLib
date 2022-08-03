#pragma once

#define is_valid_font(font) \
    (typeof(font) == 1 and font >= 100 and font <= 104)

#define all_valid_fonts ([100, 101, 102, 103, 104])

#define font_line_height(font) \
    10 if font == 101 else ( \
    12 if font == 100 else ( \
    28 if font == 102 else ( \
    20 if font == 103 else ( \
    26 if font == 104 else 0 \
))))
