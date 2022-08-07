#pragma once

/*
    Represents and single-line, single-color text input for user input.
*/

#include "Common/UI/TextArea.h"
#include "Common/Keyboard/ScanCodeToText.h"

procedure TextInput_Create begin
    variable input = {};
    fix_array(input);

    input.textarea = TextArea_Create({
        "font": 101,
        "max_lines": 1,
        "height": 15,
        "color": "green"
    });

    input.text = "";

    call TextArea_Show(input.textarea);

    return input;
end

procedure TextInput_InputKeyCode(variable input, variable keycode) begin
    display_msg("KEYCODE: " + keycode);
    variable key_text = scan_code_to_text(keycode);
    input.text += key_text;
    call TextArea_Clear(input.textarea);
    call TextArea_AddLine(input.textarea, input.text);
end
