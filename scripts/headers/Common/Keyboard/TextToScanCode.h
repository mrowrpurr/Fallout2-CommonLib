#pragma once

#include "sfall/sfall.h"
#include "sfall/lib.strings.h"

// TODO add a version of this which returns an {} which says if .shift is required! INSTEAD of looking up the code TWICE

#define KEYBOARD_TEXT_TO_DX_SCAN_CODE_INI_PATH(language_code) \
    ("mods/CommonLib/Keyboard/TextToScanCode." + language_code + ".ini")

procedure text_to_scan_code(variable text, variable language_code = "en") begin
    variable search_text = text; 
    if search_text == ";" then search_text = "SEMICOLON"; // escape ; character (which is what .ini uses)
    if search_text == "=" then search_text = "EQUALS"; // escape = character (which is what .ini uses)
    if search_text == "[" then search_text = "LEFT_BRACKET"; // escape ; character (which is what .ini uses)
    if search_text == "]" then search_text = "RIGHT_BRACKET"; // escape = character (which is what .ini uses)

    variable lower, upper;
    if strlen(text) == 1 then begin
        lower = string_tolower(text);
        upper = string_toupper(text);
        if lower != upper and text == lower then
            search_text = "LOWER:" + text;
    end

    variable scan_code_text = get_ini_string(
        KEYBOARD_TEXT_TO_DX_SCAN_CODE_INI_PATH(language_code) + "|TextToScanCode|" + search_text
    );

    if scan_code_text == "" then begin
        // Hmm, no result?
        // Does the file even exist? Try getting text 'ESCAPE' (which always exists)
        variable file_existence_check_result = get_ini_string(
            KEYBOARD_TEXT_TO_DX_SCAN_CODE_INI_PATH(language_code) + "|TextToScanCode|ESCAPE"
        );

        if file_existence_check_result == "" then
            debug_msg("[text_to_scan_code] file not found for language code '" + language_code +
                "'. Expected path: '" + KEYBOARD_TEXT_TO_DX_SCAN_CODE_INI_PATH(language_code) + "'");
        else
            debug_msg("[text_to_scan_code] text '" + text + "' not found. " + search_text + " " +
                "' Scan Codes File: '" + KEYBOARD_TEXT_TO_DX_SCAN_CODE_INI_PATH(language_code) + "'");
        return {};
    end

    if strlen(scan_code_text) < 3 then begin
        debug_msg("[text_to_scan_code] text '" + text + "' has invalid value in config file (too short). " + search_text + " " +
            "' Scan Codes File: '" + KEYBOARD_TEXT_TO_DX_SCAN_CODE_INI_PATH(language_code) + "'");
        return {};
    end

    variable visible_prefix = substr(scan_code_text, 0, 1);
    variable shift_prefix   = substr(scan_code_text, 1, 1);

    scan_code_text = substr(scan_code_text, 2, 0);

    variable dx_scan_code;
    variable numpad_dx_scan_code;

    // Does this have 2 parts? If so, the second part is the NUMPAD code.
    variable space_index = string_pos(scan_code_text, " ");
    if space_index != -1 then begin
        dx_scan_code = atoi(substr(scan_code_text, 0, space_index));
        numpad_dx_scan_code = atoi(substr(scan_code_text, space_index + 1, 0));
    end else
        dx_scan_code = atoi(scan_code_text);

    if dx_scan_code < 1 then begin
        debug_msg("[text_to_scan_code] invalid scan code found for text '" + text +
            "' Scan Codes File: '" + KEYBOARD_TEXT_TO_DX_SCAN_CODE_INI_PATH(language_code) + "'");
        return {};
    end

    return {
        "code": dx_scan_code,
        "text": text,
        "shift": (shift_prefix == "s"),
        "visible": (visible_prefix == "v"),
        "numpad": numpad_dx_scan_code
    };
end
