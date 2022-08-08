#pragma once

/*
    Represents and single-line, single-color text input for user input.
*/

#include "Common/UI/TextArea.h"
#include "Common/Keyboard/ScanCodeToText.h"

#define KEYCODE_WHICH_DOES_NOTHING (255)

procedure TextInput_Create begin
    variable text_input = {};
    fix_array(text_input);

    text_input.textarea = TextArea_Create({
        "font": 103,
        "max_lines": 1,
        "height": 25,
        "color": "hot pink"
    });

    text_input.text = "$ ";
    return text_input;
end

procedure TextInput_InputKeyCode(variable text_input, variable keycode) begin
    variable scan_code = scan_code_to_text(keycode);
    if not scan_code.visible then return;
    text_input.text += scan_code.text;
    call TextArea_Clear(text_input.textarea);
    call TextArea_AddLine(text_input.textarea, text_input.text);
end

procedure TextInput_OnKeypress(variable text_input, variable pressed, variable dx_scan_code) begin
    if text_input.textarea.visible then begin
        if pressed then call TextInput_InputKeyCode(text_input, dx_scan_code);
        return KEYCODE_WHICH_DOES_NOTHING;
    end else
        return dx_scan_code;
end

procedure TextInput_ToggleVisibility(variable text_input) begin
    call TextArea_ToggleVisibility(text_input.textarea);
end
