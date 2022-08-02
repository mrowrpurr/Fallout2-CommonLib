#pragma once

/*
    Represents a single, scrollable text area which displays read-only text.

    Individual lines can be different colors.
    
    Does not support different colors for charcters in the same line.
*/

#include "sfall/define_extra.h"
#include "Common/UI/TextWidth.h"
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
    Non-visible lines
*/

// Adds a line (using the default line color)
// Does *NOT* automatically update visible lines or render
#define TextArea_AddLine(textarea, text) \
    begin \
        call array_push(textarea.all_lines, text); \
        call array_push(textarea.line_colors, text_area.color); \
    end \
    false

// Adds a line using the provided color (formatted as HTML hex color string)
// Does *NOT* automatically update visible lines or render
#define TextArea_AddColoredLine(textarea, text, hex_color) \
    begin \
        call array_push(textarea.all_lines, text); \
        call array_push(textarea.line_colors, rgb_normalize_hex(hex_color)); \
    end \
    false

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

    // Font
    if not text_area.font then
        text_area.font = __TEXT_AREA_DEFAULT_FONT;

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

procedure __TextArea_RecalculateVisibleLines(variable text_area) begin
    // // Calculate new arrays
    // variable visible_lines       = []; fix_array(visible_lines);
    // variable visible_line_colors = []; fix_array(visible_line_colors);

    // variable non_visible_line_index;
    // while non_visible_line_index < text_area.all_lines do begin
    //     variable non_visible_line_original_character_count = strlen(text_area.all_lines[non_visible_line_index]);

    // end

    // // Replace array pointers
    // variable previous_visible_lines       = text_area.visible_lines;
    // variable previous_visible_line_colors = text_area.visible_line_colors;
    // text_area.visible_lines       = visible_lines;
    // text_area.visible_line_colors = visible_line_colors;
    // free_array(previous_visible_lines);
    // free_array(previous_visible_line_colors);
end
