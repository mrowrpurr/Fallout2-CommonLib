#pragma once

procedure string_left_pad(variable text, variable min_size, variable padding_text) begin
    while strlen(text) < min_size do text = padding_text + text;
    return text;
end

procedure string_right_pad(variable text, variable min_size, variable padding_text) begin
    while strlen(text) < min_size do text += padding_text;
    return text;
end
