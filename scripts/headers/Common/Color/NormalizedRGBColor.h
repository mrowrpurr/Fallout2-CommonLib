#pragma once

#include "Common/Color/RGBColor.h"

procedure rgb_normalize_ints(variable red_int, variable green_int, variable blue_int) begin
    // TODO - see if Star-Trek Scripting Language has bitwise shifting? https://stackoverflow.com/a/16697893
    //        meanwhile just combining 3x 3-digit ints into a string
    return string_left_pad(("" + red_int),   3, "0") +
           string_left_pad(("" + green_int), 3, "0") +
           string_left_pad(("" + blue_int),  3, "0");
end

procedure rgb_normalize_floats(variable red_float, variable green_float, variable blue_float) begin
    return rgb_normalize_ints(
        rgb_float_to_int(red_float),
        rgb_float_to_int(green_float),
        rgb_float_to_int(blue_float)
    );
end

procedure rgb_normalize_hex(variable hex_string) begin
    hex_string = rgb_hex_string(hex_string);
    if hex_string then
        return rgb_normalize_ints(
            HexToDecimal(substr(hex_string, 0, 2)),
            HexToDecimal(substr(hex_string, 2, 2)),
            HexToDecimal(substr(hex_string, 4, 2))
        );
    else
        return "000000000";
end

#define rgb_extract_red_int(combined_rgb)   (round(atof(substr(combined_rgb, 0, 3))))
#define rgb_extract_green_int(combined_rgb) (round(atof(substr(combined_rgb, 3, 3))))
#define rgb_extract_blue_int(combined_rgb)  (round(atof(substr(combined_rgb, 6, 3))))

#define rgb_extract_red_float(combined_rgb)   rgb_int_to_float(rgb_extract_red_int(combined_rgb))
#define rgb_extract_green_float(combined_rgb) rgb_int_to_float(rgb_extract_green_int(combined_rgb))
#define rgb_extract_blue_float(combined_rgb)  rgb_int_to_float(rgb_extract_blue_int(combined_rgb))

#define rgb_normalized_to_hex(combined_rgb) \
    ( \
        string_left_pad(DecimalToHex(rgb_extract_red_int(combined_rgb)),   2, "0") + \
        string_left_pad(DecimalToHex(rgb_extract_green_int(combined_rgb)), 2, "0") + \
        string_left_pad(DecimalToHex(rgb_extract_blue_int(combined_rgb)),  2, "0") \
    )
