#pragma once

#define KEYBOARD_DX_SCAN_CODE_TO_TEXT_INI_PATH(language_code) \
    ("mods/CommonLib/Keyboard/ScanCodeToText." + language_code + ".ini")

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
        return "";
    end

    // Does this have 2 parts? If so, the second part is the text when SHIFT is pressed.
    variable space_index = string_pos(text, " ");
    if space_index != -1 then begin
        if shift then
            return substr(text, space_index + 1, 0);
        else
            return substr(text, 0, space_index);
    end

    return text;
end
