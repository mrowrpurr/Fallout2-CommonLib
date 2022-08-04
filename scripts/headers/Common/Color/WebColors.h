#pragma once

#include "sfall/sfall.h"
#include "sfall/lib.strings.h"

#define WEBCOLORS_INI_PATH "mods/CommonLib/Color/WebColors.ini"

procedure webcolor_hex(variable color_name) begin
    variable color_hex = get_ini_string(
        WEBCOLORS_INI_PATH + "|colors|" + 
        string_replace(string_tolower(color_name), " ", "")
    );
    return color_hex if color_hex != "" else 0;
end
