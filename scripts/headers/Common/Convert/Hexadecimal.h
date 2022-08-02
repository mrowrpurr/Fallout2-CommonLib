#pragma once

procedure HexToDecimal(variable hex_string) begin
    switch typeof(hex_string) begin
        case 1: return hex_string; // Already an integer
        case 2: begin
            debug_msg(sprintf("[HexToDecimal] Invalid argument. Expected string of hexadecimal characters, received float (%s)", hex_string));
            return -1;
        end
    end

    variable decimal = 0,
             base    = 1,
             index   = strlen(hex_string) - 1;

    while index >= 0 do begin
        variable character = substr(hex_string, index, 1);
        variable value     = charcode(character);
        if value >= 48 and value <= 57 then begin // 0 - 9
            decimal += (value - 48) * base;
            base    *= 16;
        end else if value >= 65 and value <= 70 then begin // A - F
            decimal += (value - 55) * base;
            base    *= 16;
        end else if value >= 97 and value <= 102 then begin // a - f
            decimal += (value - 87) * base;
            base    *= 16;
        end else begin
            debug_msg(sprintf("[HexToDecimal] Invalid argument. Expected string of hexadecimal characters. Invalid character: '%s'", character));
            return -1;
        end
        index -= 1;
    end

    return decimal;
end
