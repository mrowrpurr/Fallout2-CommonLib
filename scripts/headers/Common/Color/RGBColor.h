#pragma once

#include "Common/Convert/Hexadecimal.h"
#include "Common/Text/Padding.h"

#define rgb_int_to_float(rgb_int)   ((0.0 + rgb_int) / 255)
#define rgb_float_to_int(rgb_float) (round(rgb_float * 255))

procedure rgb_hex_string(variable hex_string) begin
    // TODO extract to a typecheck assertion macro, e.g. Common/TypeCheck.h
    switch typeof(hex_string) begin
        case 1: begin
            debug_msg(sprintf("[rgb_hex_string] invalid hex string. expected string, received int %s", hex_string));
            return 0;
        end
        case 2: begin
            debug_msg(sprintf("[rgb_hex_string] invalid hex string. expected string, received float %s", hex_string));
            return 0;
        end
    end

    variable length = strlen(hex_string);
    if length and substr(hex_string, 0, 1) == "#" then begin
        length--;
        hex_string = substr(hex_string, 1, 0);
    end

    switch length begin
        case 1: return hex_string + hex_string + hex_string + 
                       hex_string + hex_string + hex_string;
        case 2: return hex_string + hex_string + hex_string;
        case 3: return substr(hex_string, 0, 1) + substr(hex_string, 0, 1) +
                       substr(hex_string, 1, 1) + substr(hex_string, 1, 1) +
                       substr(hex_string, 2, 1) + substr(hex_string, 2, 1);
        case 6: return hex_string;
        default: begin
            debug_msg(sprintf("[rgb_hex_string] invalid hex string, expected length (1,2,3,6) received length %s", strlen(hex_string)) + sprintf(" value '%s'", hex_string));
            return 0;
        end
    end
end

procedure rgb_red_int_from_hex(variable hex_string) begin
    hex_string = rgb_hex_string(hex_string);
    if hex_string then
        return HexToDecimal(substr(hex_string, 0, 2));
    else
        return 0;
end

procedure rgb_green_int_from_hex(variable hex_string) begin
    hex_string = rgb_hex_string(hex_string);
    if hex_string then
        return HexToDecimal(substr(hex_string, 2, 2));
    else
        return 0;
end

procedure rgb_blue_int_from_hex(variable hex_string) begin
    hex_string = rgb_hex_string(hex_string);
    if hex_string then
        return HexToDecimal(substr(hex_string, 4, 2));
    else
        return 0;
end

#define rgb_red_from_hex(hex_string)   rgb_red_float_from_hex(hex_string)
#define rgb_green_from_hex(hex_string) rgb_green_float_from_hex(hex_string)
#define rgb_blue_from_hex(hex_string)  rgb_blue_float_from_hex(hex_string)

procedure rgb_red_float_from_hex(variable hex_string) begin
    variable int_value = rgb_red_int_from_hex(hex_string);
    if int_value then
        return rgb_int_to_float(int_value);
    else
        return 0.0;
end

procedure rgb_green_float_from_hex(variable hex_string) begin
    variable int_value = rgb_green_int_from_hex(hex_string);
    if int_value then
        return rgb_int_to_float(int_value);
    else
        return 0.0;
end

procedure rgb_blue_float_from_hex(variable hex_string) begin
    variable int_value = rgb_blue_int_from_hex(hex_string);
    if int_value then
        return rgb_int_to_float(int_value);
    else
        return 0.0;
end

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

#define rgb_extract_red_int(combined_rgb)   (atoi(substr(combined_rgb, 0, 3)))
#define rgb_extract_green_int(combined_rgb) (atoi(substr(combined_rgb, 3, 3)))
#define rgb_extract_blue_int(combined_rgb)  (atoi(substr(combined_rgb, 6, 3)))

#define rgb_extract_red(combined_rgb)   rgb_extract_red_float(combined_rgb)
#define rgb_extract_green(combined_rgb) rgb_extract_green_float(combined_rgb)
#define rgb_extract_blue(combined_rgb)  rgb_extract_blue_float(combined_rgb)

#define rgb_extract_red_float(combined_rgb)   rgb_int_to_float(rgb_extract_red_int(combined_rgb))
#define rgb_extract_green_float(combined_rgb) rgb_int_to_float(rgb_extract_green_int(combined_rgb))
#define rgb_extract_blue_float(combined_rgb)  rgb_int_to_float(rgb_extract_blue_int(combined_rgb))

// #define rgb_normalized_to_hex(normalized) "TODO"
