#pragma once

#include "sfall/sfall.h"
#include "sfall/lib.strings.h"
#include "Common/Color/RGBColor.h"

#define WEBCOLORS_INI_PATH "mods/CommonLib/Color/WebColors.ini"

procedure webcolor_hex(variable color_name) begin
    // Don't check the .ini if provided a # or number leading string
    variable first_char = substr(color_name, 0, 1);
    switch first_char begin
        case "#": return rgb_hex_string(color_name);
        case "0": return rgb_hex_string(color_name);
        case "1": return rgb_hex_string(color_name);
        case "2": return rgb_hex_string(color_name);
        case "3": return rgb_hex_string(color_name);
        case "4": return rgb_hex_string(color_name);
        case "5": return rgb_hex_string(color_name);
        case "6": return rgb_hex_string(color_name);
        case "7": return rgb_hex_string(color_name);
        case "8": return rgb_hex_string(color_name);
        case "9": return rgb_hex_string(color_name);
    end

    // Read from the .ini
    variable color_hex = get_ini_string(
        WEBCOLORS_INI_PATH + "|colors|" + 
        string_replace(string_tolower(color_name), " ", "")
    );

    // Return either the result or a rgb-hex-ified version of provided string
    return rgb_hex_string(color_hex) if color_hex != "" else rgb_hex_string(color_name);
end
