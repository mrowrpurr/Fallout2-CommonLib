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

// @private procedure declarations
procedure __TextArea_AddVisibleLine(variable text_area, variable line_text, variable normalized_line_color);
procedure __TextArea_Initialize(variable text_area);

#define TextArea_VisibleLineCount(text_area) (text_area._visible_line_count)
#define TextArea_TotalLineCount(text_area) (len_array(text_area._visible_lines))

procedure TextArea_Refresh(variable text_area) begin
    if text_area and text_area.initialized then begin

        if text_area.transparent then begin
            DeleteWin(text_area.name);
            call __TextArea_Initialize(text_area);
            SelectWin(text_area.name);
        end else begin
            SelectWin(text_area.name);
            variable background_color = text_area.background_color;
            FillWin(
                rgb_extract_red_float(background_color),
                rgb_extract_green_float(background_color),
                rgb_extract_blue_float(background_color)
            );
        end

        variable line_count = text_area._visible_line_count;
        if not line_count then begin
            ShowWin;
            return;
        end
        
        SetFont(text_area.font);

        variable width = text_area.width;
        variable line_height = text_area.line_height;
        variable last_color;
        variable line_index = text_area._visible_lines_start;

        variable line_number;
        for line_number = 0; line_number < line_count; line_number++; begin
            display_msg("RENDER LINE " + line_index);
            variable line = text_area._visible_lines[line_index];
            variable font_color = text_area._visible_line_colors[line_index];
            if font_color != last_color then
                SetTextColor(
                    rgb_extract_red_float(font_color),
                    rgb_extract_green_float(font_color),
                    rgb_extract_blue_float(font_color)
                );
            last_color = font_color;
            Format(
                line, 
                0,
                (line_height * line_number),
                width,
                line_height,
                justifyleft
            );
            line_index++;
        end
        ShowWin;
    end
end

procedure TextArea_Show(variable text_area) begin
    if text_area then begin
        if text_area.visible then return;
        text_area.visible = true;
        if not text_area.initialized then
            call __TextArea_Initialize(text_area);
        show_window(text_area.name);
        call TextArea_Refresh(text_area);
    end
end

procedure TextArea_Hide(variable text_area) begin
    if text_area and text_area.visible then begin
        text_area.visible = false;
        hide_window(text_area.name);
    end
end

procedure TextArea_ToggleVisibility(variable text_area) begin
    if text_area then begin
        if text_area.visible then
            call TextArea_Hide(text_area);
        else
            call TextArea_Show(text_area);
    end
end

// if line count is positive, the area is scrolled down that number of lines
// if the line count is negative, the area is scrolled up the number of lines
procedure TextArea_Scroll(variable text_area, variable lines_count) begin
    if text_area then begin
        variable scroll_lines = text_area.scroll_lines;
        variable current_line_start_index = text_area._visible_lines_start;
        variable all_potentially_visible_lines = len_array(text_area._visible_lines);

        // Don't scroll until we have enough content to scroll
        if all_potentially_visible_lines <= scroll_lines then return;

        if lines_count > 0 and all_potentially_visible_lines - current_line_start_index <= scroll_lines then return; // can't scroll down anymore!

        variable new_start = current_line_start_index + lines_count;

        if new_start < 0 then
            new_start = 0;
        else if new_start > all_potentially_visible_lines - 1 then
            new_start = all_potentially_visible_lines - 1;

        if lines_count > 0 and new_start > all_potentially_visible_lines - scroll_lines then
            new_start = all_potentially_visible_lines - scroll_lines;

        text_area._visible_lines_start = new_start;
    end
end

// scroll up one full visible page (or text_area.scroll_lines if defined)
procedure TextArea_ScrollUp(variable text_area) begin
    call TextArea_Scroll(text_area, text_area.scroll_lines * -1);
end

// scroll up one full visible page (or text_area.scroll_lines if defined)
procedure TextArea_ScrollDown(variable text_area) begin
    call TextArea_Scroll(text_area, text_area.scroll_lines);
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

    variable max_visible_lines = floor(text_area.height / text_area.line_height);
    if not text_area.max_lines or text_area.max_lines > max_visible_lines then
        text_area.max_lines = max_visible_lines;

    variable max_lines = text_area.max_lines;
    if not text_area.scroll_lines or text_area.scroll_lines > max_lines then
        text_area.scroll_lines = max_lines;

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

    text_area._visible_lines_start = 0;
    text_area._visible_line_count = 0;

    return text_area;
end

procedure TextArea_Destroy(variable text_area) begin
    if text_area then begin
        if text_area.initialized then DeleteWin(text_area.name); // check if it exists first
        free_array(text_area._original_lines);
        free_array(text_area._original_line_colors);
        free_array(text_area._visible_lines);
        free_array(text_area._visible_line_colors);
    end
end

// Adds a line (using the default line color)
procedure TextArea_AddLine(variable text_area, variable text) begin
    call array_push(text_area._original_lines, text);
    call array_push(text_area._original_line_colors, text_area.color);
    call __TextArea_AddVisibleLine(text_area, text, text_area.color);
    if text_area.visible then call TextArea_Refresh(text_area);
end

// Adds a line using provided color (formatted as HTML hex color string)
procedure TextArea_AddColoredLine(variable text_area, variable text, variable hex_color) begin
    variable normalized_rgb_color = rgb_normalize_hex(webcolor_hex(hex_color));
    call array_push(text_area._original_lines, text);
    call array_push(text_area._original_line_colors, normalized_rgb_color);
    call __TextArea_AddVisibleLine(text_area, text, normalized_rgb_color);
    if text_area.visible then call TextArea_Refresh(text_area);
end

// Clears all lines (visible and non-visible)
procedure TextArea_Clear(variable text_area) begin
    resize_array(text_area._original_lines, 0);
    resize_array(text_area._original_line_colors, 0);
    resize_array(text_area._visible_lines, 0);
    resize_array(text_area._visible_line_colors, 0);
    text_area._visible_lines_start = 0;
    text_area._visible_line_count = 0;
    if text_area.visible then call TextArea_Refresh(text_area);
end

/*
    @private procedures
*/

inline procedure __TextArea_Initialize(variable text_area) begin
    variable flags;
    if text_area.transparent then
        flags = WIN_FLAG_HIDDEN + WIN_FLAG_MOVEONTOP + WIN_FLAG_TRANSPARENT;
    else
        flags = WIN_FLAG_HIDDEN + WIN_FLAG_MOVEONTOP;
    create_win_flag(
        text_area.name,
        text_area.x,
        text_area.y,
        text_area.width,
        text_area.height,
        flags
    );
    text_area.initialized = true;
end

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

        if text_area._visible_line_count < text_area.max_lines and available_vertical_space - line_height >= 0 then
            text_area._visible_line_count++; // There is enough visible space to display this line!

        call array_push(text_area._visible_lines, text_to_add);
        call array_push(text_area._visible_line_colors, normalized_line_color);
        
        total_added_text_characters_count += text_to_add_length;
    end

    if autoscroll then begin
        variable new_start_index = len_array(text_area._visible_lines) - text_area.max_lines;
        if new_start_index < 0 then new_start_index = 0;
        text_area._visible_lines_start = new_start_index;
    end
end
