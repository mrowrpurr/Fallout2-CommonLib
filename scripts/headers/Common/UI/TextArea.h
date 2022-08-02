#pragma once

/*
    Represents a single, scrollable text area which displays read-only text.

    Individual lines can be different colors.
    
    Does not support different colors for charcters in the same line.
*/

#include "sfall/define_extra.h"
#include "Common/UI/TextWidthSubstring.h"
#include "Common/Color/NormalizedRGBColor.h"

/*
    Default Color
*/

#define __TEXT_AREA_DEFAULT_NORMALIZED_RGB_COLOR "255255255"
#define TextArea_DefaultColor_get(textarea) rgb_normalized_to_hex(textarea.color)
#define TextArea_DefaultColor_set(textarea, hex_color) textarea.color = rgb_normalize_hex(hex_color)

/*
    Default Font
*/

#define __TEXT_AREA_DEFAULT_FONT 101
#define TextArea_DefaultFont_get(textarea) (textarea.font)

/*
    Lines of text
*/

inline procedure __TextArea_AddVisibleLine(variable text_area, variable line_text, variable normalized_line_color) begin
    variable total_added_text_characters_count; 
    variable line_length = strlen(line_text);
    variable width       = text_area.width;
    while total_added_text_characters_count < line_length do begin

        variable text_to_attempt_to_add;
        if total_added_text_characters_count == 0 then
            text_to_attempt_to_add = line_text;
        else
            text_to_attempt_to_add = substr(line_text, total_added_text_characters_count, 0);

        variable text_to_add = get_text_width_substring_with_separator(line_text, width, text_area.font);
        
        variable text_to_add_length = strlen(text_to_add);
        if text_to_add_length == 0 then begin
            // TODO REMOVE THE Waterchip: prefix here!
            debug_msg("Waterchip: [TextArea] width " + width + " of text area too small to render text '" + text_to_attempt_to_add + "'");
            break;
        end
        
        total_added_text_characters_count += text_to_add_length;
        call array_push(text_area.visible_lines, text_to_add);
        call array_push(text_area.visible_line_colors, normalized_line_color);
    end
end

// Adds a line (using the default line color)
procedure TextArea_AddLine(variable text_area, variable text) begin
    call array_push(text_area.all_lines, text);
    call array_push(text_area.line_colors, text_area.color);
    call __TextArea_AddVisibleLine(text_area, text, text_area.color);
end

// Adds a line using the provided color (formatted as HTML hex color string)
procedure TextArea_AddColoredLine(variable text_area, variable text, variable hex_color) begin
    variable normalized_rgb_color = rgb_normalize_hex(hex_color);
    call array_push(text_area.all_lines, text);
    call array_push(text_area.line_colors, normalized_rgb_color);
    call __TextArea_AddVisibleLine(text_area, text, normalized_rgb_color);
end

procedure TextArea_ClearLines(variable text_area) begin
    resize_array(text_area.all_lines,           0);
    resize_array(text_area.line_colors,         0);
    resize_array(text_area.visible_lines,       0);
    resize_array(text_area.visible_line_colors, 0);
end

/*
    ...........
*/

#define __TEXT_AREA_DEFRAULT_WINDOW_NAME_PREFIX "CommonLibUiTextArea_"


procedure TextArea_Create(variable defaults = 0) begin
    variable text_area = defaults if defaults else {};
    fix_array(text_area);

    // If the name wasn't set, make a random one!
    if not text_area.name or strlen(text_area.name) == 0 then begin
        text_area.name = __TEXT_AREA_DEFRAULT_WINDOW_NAME_PREFIX + random(10000, 99999) + random(10000, 99999);
    end

    // Text color
    if text_area.color then
        text_area.color = rgb_normalize_hex(text_area.color);
    else
        text_area.color = __TEXT_AREA_DEFAULT_NORMALIZED_RGB_COLOR;

    if not text_area.font   then text_area.font   = __TEXT_AREA_DEFAULT_FONT;
    if not text_area.width  then text_area.width  = get_screen_width;
    if not text_area.height then text_area.height = get_screen_height;

    // TODO: make the fields which store lines and colors "private" by staring with .__
    // TODO: rename all_lines/line_colors to something like all_line_colors for consistency with visible* fields

    // Stores all lines 
    text_area.all_lines = [];
    fix_array(text_area.all_lines);

    // Stores colors of each line (shares index of all_lines)
    // Stored as 'normalized' RGB colors (use RGB normalize/extract functions)
    text_area.line_colors = [];
    fix_array(text_area.line_colors);

    // Stores visible lines 
    text_area.visible_lines = [];
    fix_array(text_area.visible_lines);

    // Stores colors of each line (shares index of visible_lines)
    // Stored as 'normalized' RGB colors (use RGB normalize/extract functions)
    text_area.visible_line_colors = [];
    fix_array(text_area.visible_line_colors);

    return text_area;
end

// Set a bit to note that it's rendering!
procedure TextArea_Render(variable text_area) begin

end

procedure TextArea_DestroyUI(variable text_area) begin
    
end

procedure TextArea_Show(variable text_area) begin
    // text_area.visible = true;
    // log_info("SHOW WINDOW '" + WINDOW_NAME + "'");
    // create_win_flag(
    //         WINDOW_NAME,
    //         10,
    //         100,
    //         500,
    //         400,
    //         WIN_FLAG_HIDDEN + WIN_FLAG_MOVEONTOP
    //     );
    // SelectWin(WINDOW_NAME);
    // FillWin(0.0, 0.0, 0.0);
    // SetFont(101);
    // SetTextColor(0.988, 0, 0.957);
    // Format("Hey wassup? a bunch of text yo!", 5, 10, 240, 12, justifyleft);
    // show_window(WINDOW_NAME);
end

procedure TextArea_Hide(variable text_area) begin
    // DeleteWin(WINDOW_NAME); // check if it exists first
    text_area.visible = false;
end

procedure TextArea_ToggleVisibility(variable text_area) begin
    if text_area then begin
        if text_area.visible then
            call TextArea_Hide(text_area);
        else
            call TextArea_Show(text_area);
    end
end

procedure TextArea_Destroy(variable text_area) begin

end

/*
    Visible Line Calculation
*/

///////////////////////////////////////////////////////////////
// TODO extract me

///////////////////////////////////////////////////////////////


