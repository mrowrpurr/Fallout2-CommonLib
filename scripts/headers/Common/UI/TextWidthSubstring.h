#pragma once

// TODO add an option to split on spaces for words

procedure get_text_width_substring(variable text, variable width, variable font = 0) begin
    if not text then return "";
    variable text_length = strlen(text);
    if not text_length then return "";

    if font then SetFont(font);

    variable text_width = get_text_width(text);

    if text_width <= width then return text;

    variable low    = 0;
    variable high   = text_length - 1;
    variable middle = text_length / 2;

    variable substring;
    variable substring_width;

    variable most_recent_middle_under_width;
    variable most_recent_middle_over_width;

    while true do begin
        if not middle then return ""; 

        substring       = substr(text, 0, middle);
        substring_width = get_text_width(substring);

        if substring_width == width then
            return substring;
        else if substring_width < width then begin
            // if we hit this conditional 2x in a row with the same value, then return the most recent match *under* desired length
            if most_recent_middle_under_width == middle then return substring;
            most_recent_middle_under_width = middle; // hold onto this as the most recent match *under* desired length
            low    = middle + 1;
            middle = (low + high) / 2;
        end else begin
            high   = middle - 1;
            middle = (low + high) / 2;
            // if we hit this conditional 2x in a row with the same value, then return the most recent match *under* desired length
            if most_recent_middle_over_width == middle then return substr(text, 0, most_recent_middle_under_width);
            most_recent_middle_over_width = middle;
        end
    end
end
