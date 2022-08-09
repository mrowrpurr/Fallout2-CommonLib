#pragma once

/*
    Represents and single-line, single-color text input for user input.
*/

#include "Common/UI/TextArea.h"
#include "Common/Keyboard/ScanCodeToText.h"

#define KEYCODE_WHICH_DOES_NOTHING (255)

procedure TextInput_Create(variable parameters = 0) begin
    variable text_input = {
        "text": ""
    };
    fix_array(text_input);

    if not parameters then parameters = {};
    parameters.max_lines = 1;

    // Hacky, for now just pass parameters straight to the TextArea
    text_input.textarea = TextArea_Create(parameters);

    text_input.textarea.height = text_input.textarea.line_height;

    return text_input;
end

procedure TextInput_InputKeyCode(variable text_input, variable keycode) begin
    variable scan_code = scan_code_to_text(keycode, text_input.is_shift_pressed);
    if not scan_code.visible then return;
    text_input.text += scan_code.text;
    call TextArea_Clear(text_input.textarea);
    call TextArea_AddLine(text_input.textarea, text_input.text);
end

procedure TextInput_OnKeypress(variable text_input, variable pressed, variable dx_scan_code) begin
    // if is_shift_key_code(dx_scan_code) <-- TODO
    if dx_scan_code == 42 then
        text_input.is_shift_pressed = pressed;

    if text_input.textarea.visible then begin
        if pressed then call TextInput_InputKeyCode(text_input, dx_scan_code);
        return KEYCODE_WHICH_DOES_NOTHING;
    end else
        return dx_scan_code;
end

procedure TextInput_Clear(variable text_input) begin
    text_input.text = "";
    call TextArea_Clear(text_input.textarea);
end

procedure TextInput_ToggleVisibility(variable text_input) begin
    call TextArea_ToggleVisibility(text_input.textarea);
end
