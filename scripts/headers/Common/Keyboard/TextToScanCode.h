#pragma once

#include "sfall/sfall.h"

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
        return "";
    end

    variable scan_code_int = atoi(scan_code_text);

    if scan_code_int < 1 then begin
        debug_msg("[text_to_scan_code] invalid scan code found for text '" + text +
            "' Scan Codes File: '" + KEYBOARD_TEXT_TO_DX_SCAN_CODE_INI_PATH(language_code) + "'");
        return 0;
    end

    // This is dx scan code requires a shift key
    if scan_code_int % 1000 == 0 then
        return scan_code_int / 1000;
    else
        return scan_code_int;
end

procedure does_text_to_scan_code_require_shift(variable text, variable language_code = "en") begin
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
            debug_msg("[does_text_to_scan_code_require_shift] file not found for language code '" + language_code +
                "'. Expected path: '" + KEYBOARD_TEXT_TO_DX_SCAN_CODE_INI_PATH(language_code) + "'");
        else
            debug_msg("[does_text_to_scan_code_require_shift] text '" + text + "' not found."
                "' Scan Codes File: '" + KEYBOARD_TEXT_TO_DX_SCAN_CODE_INI_PATH(language_code) + "'");
        return false;
    end

    variable scan_code_int = atoi(scan_code_text);

    debug_msg("SHIFT CHECK - scan code text - " + scan_code_text + " for search: " + text);

    if scan_code_int < 1 then begin
        debug_msg("[does_text_to_scan_code_require_shift] invalid scan code found for text '" + text +
            "' Scan Codes File: '" + KEYBOARD_TEXT_TO_DX_SCAN_CODE_INI_PATH(language_code) + "'");
        return false;
    end

    // This is dx scan code requires a shift key
    if scan_code_int % 1000 == 0 then
        return true;
    else
        return false;
end
