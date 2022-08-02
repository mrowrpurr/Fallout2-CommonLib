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

    hex_string = string_toupper(hex_string); // Normalize to upper case

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
