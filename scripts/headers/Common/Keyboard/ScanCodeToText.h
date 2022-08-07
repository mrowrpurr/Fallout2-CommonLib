#pragma once

#define KEYBOARD_DX_SCAN_CODE_TO_TEXT_INI_PATH(language_code) \
    ("mods/CommonLib/Keyboard/ScanCodeToText." + language_code + ".ini")

#define KEYBOARD_DX_SCAN_CODE_TO_TEXT_PREFIX_VISIBLE_CHARACTER ("v")
#define KEYBOARD_DX_SCAN_CODE_TO_TEXT_PREFIX_NONVISIBLE_CHARACTER ("n")
#define KEYBOARD_DX_SCAN_CODE_TO_TEXT_PREFIX_VISIBLE_NUMPAD_CHARACTER ("p")
#define KEYBOARD_DX_SCAN_CODE_TO_TEXT_PREFIX_NONVISIBLE_NUMPAD_CHARACTER ("d")
#define KEYBOARD_DX_SCAN_CODE_TO_TEXT_PREFIX_SPACE_CHARACTER ("x")

procedure scan_code_to_text(variable dx_scan_code, variable language_code = "en", variable shift = false) begin
    variable text = get_ini_string(
        KEYBOARD_DX_SCAN_CODE_TO_TEXT_INI_PATH(language_code) + "|ScanCodeToText|" + dx_scan_code
    );

    if text == "" then begin
        // Hmm, no result?
        // Does the file even exist? Try getting scan code 1 (which always exists)
        variable file_existence_check_result = get_ini_string(
            KEYBOARD_DX_SCAN_CODE_TO_TEXT_INI_PATH(language_code) + "|ScanCodeToText|1"
        );

        if file_existence_check_result == "" then
            debug_msg("[scan_code_to_text] file not found for language code '" + language_code +
                "'. Expected path: '" + KEYBOARD_DX_SCAN_CODE_TO_TEXT_INI_PATH(language_code) + "'");
        else
            debug_msg("[scan_code_to_text] dx scan code '" + dx_scan_code + "' not found."
                "' Scan Codes File: '" + KEYBOARD_DX_SCAN_CODE_TO_TEXT_INI_PATH(language_code) + "'");
        return {};
    end

    variable requires_shift;

    variable prefix = substr(text, 0, 1);

    text = substr(text, 1, 0);

    // Does this have 2 parts? If so, the second part is the text when SHIFT is pressed.
    variable space_index = string_pos(text, " ");
    if space_index != -1 then begin
        if shift then begin
            text = substr(text, space_index + 1, 0);
            requires_shift = true;
        end else
            text = substr(text, 0, space_index);
    end

    variable numpad;
    variable visible;

    switch prefix begin
        case KEYBOARD_DX_SCAN_CODE_TO_TEXT_PREFIX_VISIBLE_CHARACTER: visible = true;
        case KEYBOARD_DX_SCAN_CODE_TO_TEXT_PREFIX_VISIBLE_NUMPAD_CHARACTER: begin
            numpad = true;
            visible = true;
        end
        case KEYBOARD_DX_SCAN_CODE_TO_TEXT_PREFIX_NONVISIBLE_NUMPAD_CHARACTER: begin
            numpad = true;
        end
        case KEYBOARD_DX_SCAN_CODE_TO_TEXT_PREFIX_SPACE_CHARACTER: begin
            text = " ";
            visible = true;
        end
    end

    return {
        "code": dx_scan_code,
        "text": text,
        "visible": visible,
        "numpad": numpad,
        "shift": requires_shift
    };
end
