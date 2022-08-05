#pragma once

/*
    Represents a single, scrollable text area which displays read-only text.

    Individual lines can be different colors.
    
    Does not support different colors for charcters in the same line.
*/

#include "sfall/define_extra.h"
#include "Common/UI/Fonts.h"
#include "Common/UI/TextWidthSubstring.h"
#include "Common/Color/WebColors.h"
#include "Common/Color/NormalizedRGBColor.h"

#define __TEXT_AREA_DEFAULT_FONT (101)
#define __TEXT_AREA_DEFAULT_TEXT_NORMALIZED_RGB_COLOR "255255255"
#define __TEXT_AREA_DEFAULT_BACKGROUND_NORMALIZED_RGB_COLOR "000000000"
#define __TEXT_AREA_DEFRAULT_WINDOW_NAME_PREFIX "CommonLibUiTextArea_"

// @private
procedure __TextArea_AddVisibleLine(variable text_area, variable line_text, variable normalized_line_color);

// Adds a line (using the default line color)
procedure TextArea_AddLine(variable text_area, variable text) begin
    call array_push(text_area._original_lines, text);
    call array_push(text_area._original_line_colors, text_area.color);
    call __TextArea_AddVisibleLine(text_area, text, text_area.color);
end

// Adds a line using provided color (formatted as HTML hex color string)
procedure TextArea_AddColoredLine(variable text_area, variable text, variable hex_color) begin
    variable normalized_rgb_color = rgb_normalize_hex(hex_color);
    call array_push(text_area._original_lines, text);
    call array_push(text_area._original_line_colors, normalized_rgb_color);
    call __TextArea_AddVisibleLine(text_area, text, normalized_rgb_color);
end

// Clears all lines (visible and non-visible)
procedure TextArea_ClearLines(variable text_area) begin
    resize_array(text_area._original_lines, 0);
    resize_array(text_area._original_line_colors, 0);
    resize_array(text_area._visible_lines, 0);
    resize_array(text_area._visible_line_colors, 0);
    text_area._visible_lines_start_index = 0;
    text_area._visible_line_count = 0;
end

procedure TextArea_Create(variable defaults = 0) begin
    variable text_area = defaults if defaults else {};
    fix_array(text_area);

    // If the name wasn't set, make a random one!
    if not text_area.name or strlen(text_area.name) == 0 then begin
        text_area.name = __TEXT_AREA_DEFRAULT_WINDOW_NAME_PREFIX + random(10000, 99999) + random(10000, 99999);
    end

    if text_area.color then
        text_area.color = rgb_normalize_hex(webcolor_hex(text_area.color));
    else
        text_area.color = __TEXT_AREA_DEFAULT_TEXT_NORMALIZED_RGB_COLOR;

    if text_area.background_color then
        text_area.background_color = rgb_normalize_hex(webcolor_hex(text_area.background_color));
    else
        text_area.background_color = __TEXT_AREA_DEFAULT_BACKGROUND_NORMALIZED_RGB_COLOR;

    if not text_area.width  then text_area.width  = get_screen_width;
    if not text_area.height then text_area.height = get_screen_height;

    if not text_area.font or not is_valid_font(text_area.font) then
        text_area.font = __TEXT_AREA_DEFAULT_FONT;

    variable height_of_font = font_line_height(text_area.font);

    if not text_area.line_height or text_area.line_height < height_of_font then
        text_area.line_height = height_of_font;

    // TODO: make the fields which store lines and colors "private" by staring with .__
    // TODO: rename all_lines/line_colors to something like all_line_colors for consistency with visible* fields

    // Stores all lines 
    text_area._original_lines = [];
    fix_array(text_area._original_lines);

    // Stores colors of each line (shares index of all_lines)
    // Stored as 'normalized' RGB colors (use RGB normalize/extract functions)
    text_area._original_line_colors = [];
    fix_array(text_area._original_line_colors);

    // Stores visible lines 
    text_area._visible_lines = [];
    fix_array(text_area._visible_lines);

    // Stores colors of each line (shares index of visible_lines)
    // Stored as 'normalized' RGB colors (use RGB normalize/extract functions)
    text_area._visible_line_colors = [];
    fix_array(text_area._visible_line_colors);

    text_area._visible_lines_start_index = 0;
    text_area._visible_line_count   = 0;

    return text_area;
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

// @private
// Called when adding lines via TextArea_AddLine or TextArea_AddColoredLine
// Inline because it's only used from 2 places (adding color and non-color lines)
// and would prefer not to add an additional procedure invocation on line addition.
inline procedure __TextArea_AddVisibleLine(variable text_area, variable line_text, variable normalized_line_color) begin
    variable autoscroll                = text_area.autoscroll;
    variable line_height               = text_area.line_height;
    variable current_total_line_height = len_array(text_area._visible_lines) * line_height;
    variable available_vertical_space  = text_area.height - current_total_line_height;
    variable line_length               = strlen(line_text);
    variable width                     = text_area.width;

    variable total_added_text_characters_count; 
    while total_added_text_characters_count < line_length do begin

        variable text_to_attempt_to_add;
        if total_added_text_characters_count == 0 then
            text_to_attempt_to_add = line_text;
        else
            text_to_attempt_to_add = substr(line_text, total_added_text_characters_count, 0);

        variable text_to_add = get_text_width_substring_with_separator(text_to_attempt_to_add, width, text_area.font);
        
        variable text_to_add_length = strlen(text_to_add);
        if text_to_add_length == 0 then begin
            debug_msg("[TextArea] width " + width + " of text area too small to render text '" + text_to_attempt_to_add + "'");
            break;
        end
        
        current_total_line_height = len_array(text_area._visible_lines) * line_height;
        available_vertical_space  = text_area.height - current_total_line_height;

        if available_vertical_space - line_height >= 0 then
            text_area._visible_line_count++; // There is enough visible space to display this line!
        else if autoscroll then
            text_area._visible_lines_start_index++; // Move the index of visible lines down

        call array_push(text_area._visible_lines, text_to_add);
        call array_push(text_area._visible_line_colors, normalized_line_color);
        
        total_added_text_characters_count += text_to_add_length;
    end
end
