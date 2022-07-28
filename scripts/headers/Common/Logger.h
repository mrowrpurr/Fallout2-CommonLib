#pragma once

// Log levels
#define LOGGER_LEVEL_ALL   (7)
#define LOGGER_LEVEL_TRACE (6)
#define LOGGER_LEVEL_DEBUG (5)
#define LOGGER_LEVEL_INFO  (4)
#define LOGGER_LEVEL_WARN  (3)
#define LOGGER_LEVEL_ERROR (2)
#define LOGGER_LEVEL_FATAL (1)
#define LOGGER_LEVEL_NONE  (0)

#define LOGGER_LEVEL_ALL_NAME   "ALL"
#define LOGGER_LEVEL_TRACE_NAME "TRACE"
#define LOGGER_LEVEL_DEBUG_NAME "DEBUG"
#define LOGGER_LEVEL_INFO_NAME  "INFO"
#define LOGGER_LEVEL_WARN_NAME  "WARN"
#define LOGGER_LEVEL_ERROR_NAME "ERROR"
#define LOGGER_LEVEL_FATAL_NAME "FATAL"
#define LOGGER_LEVEL_NONE_NAME  "NONE"

// By default, show all logs.
variable                     LOGGER_LOG_LEVEL = LOGGER_LEVEL_ALL;
#define set_log_level(level) LOGGER_LOG_LEVEL = get_log_level(level)
#define disable_logging      LOGGER_LOG_LEVEL = LOGGER_LEVEL_NONE
#define enable_logging_all   LOGGER_LOG_LEVEL = LOGGER_LEVEL_ALL

// By default, output logs to debug_msg.
variable                         LOGGER_DEBUG_MSG = true;
#define enable_log_to_debug_msg  LOGGER_DEBUG_MSG = true
#define disable_log_to_debug_msg LOGGER_DEBUG_MSG = false

// By default, do not output logs to display_msg.
variable                           LOGGER_DISPLAY_MSG = false;
#define enable_log_to_display_msg  LOGGER_DISPLAY_MSG = true
#define disable_log_to_display_msg LOGGER_DISPLAY_MSG = false

// By default, do not store output logs in memory for testing log output.
variable                     LOGGER_TEST = false;
#define enable_test_logging  LOGGER_TEST = true
#define disable_test_logging LOGGER_TEST = false

// By default, log output includes the log level as a prefix, e.g. [WARN]
variable                       LOGGER_DISPLAY_LOG_LEVEL = true;
#define show_log_level_in_logs LOGGER_DISPLAY_LOG_LEVEL = true
#define hide_log_level_in_logs LOGGER_DISPLAY_LOG_LEVEL = false

// Is the log level shown as a prefix? Else as a suffix
variable LOGGER_DISPLAY_LOG_LEVEL_IS_PREFIX = true;
#define show_log_level_output_as_prefix LOGGER_DISPLAY_LOG_LEVEL_IS_PREFIX = true
#define show_log_level_output_as_suffix LOGGER_DISPLAY_LOG_LEVEL_IS_PREFIX = false

// Configure the actual format for the log level output
variable LOGGER_DISPLAY_LOG_LEVEL_FORMAT = "[%s] ";
#define set_log_level_output_format(format) LOGGER_DISPLAY_LOG_LEVEL_FORMAT = format

// Is the log level shown on every \n newline of the provided log message? Default: false
variable LOGGER_DISPLAY_LOG_LEVEL_EVERY_LINE = false;
#define show_log_level_on_every_line LOGGER_DISPLAY_LOG_LEVEL_EVERY_LINE = true
#define hide_log_level_on_every_line LOGGER_DISPLAY_LOG_LEVEL_EVERY_LINE = false

// Set Logger prefix
variable LOGGER_PREFIX;
#define set_logger_prefix(text) LOGGER_PREFIX = text

// Is the Logger prefix shown?
variable LOGGER_DISPLAY_PREFIX = true;
#define show_logger_prefix LOGGER_DISPLAY_PREFIX = true
#define hide_logger_prefix LOGGER_DISPLAY_PREFIX = true

// Is the log prefix shown on every \n newline of the provided log message? Default: false
variable LOGGER_DISPLAY_PREFIX_EVERY_LINE = false;
#define show_log_prefix_on_every_line LOGGER_DISPLAY_PREFIX_EVERY_LINE = true
#define hide_log_prefix_on_every_line LOGGER_DISPLAY_PREFIX_EVERY_LINE = false

// Set Logger suffix
variable LOGGER_SUFFIX;
#define set_logger_suffix(text) LOGGER_SUFFIX = text

// Is the Logger suffix shown?
variable LOGGER_DISPLAY_SUFFIX = true;
#define show_logger_suffix LOGGER_DISPLAY_SUFFIX = true
#define hide_logger_suffix LOGGER_DISPLAY_SUFFIX = true

// Is the log suffix shown on every \n newline of the provided log message? Default: false
variable LOGGER_DISPLAY_SUFFIX_EVERY_LINE = false;
#define show_log_suffix_on_every_line LOGGER_DISPLAY_SUFFIX_EVERY_LINE = true
#define hide_log_suffix_on_every_line LOGGER_DISPLAY_SUFFIX_EVERY_LINE = false

// When test logging is enabled, this is an array of all log messages.
// #include "TestHelpers/Logging.h" for macros for working with logs in tests.
variable LOGGER_TEST_LOGS;

// Reset logger to default configuration values
#define logger_reset \
    begin \
        LOGGER_LOG_LEVEL = LOGGER_LEVEL_TRACE; \
        LOGGER_DEBUG_MSG = true; \
        LOGGER_DISPLAY_MSG = false; \
        LOGGER_TEST = false; \
        free_array(LOGGER_TEST_LOGS); \
        LOGGER_TEST_LOGS = 0; \
        LOGGER_DISPLAY_LOG_LEVEL = true; \
        LOGGER_DISPLAY_LOG_LEVEL_IS_PREFIX = true; \
        LOGGER_DISPLAY_LOG_LEVEL_FORMAT = "[%s] "; \
        LOGGER_DISPLAY_LOG_LEVEL_EVERY_LINE = false; \
        LOGGER_PREFIX = 0; \
        LOGGER_DISPLAY_PREFIX = true; \
        LOGGER_DISPLAY_PREFIX_EVERY_LINE = false; \
        LOGGER_SUFFIX = 0; \
        LOGGER_DISPLAY_SUFFIX = true; \
        LOGGER_DISPLAY_SUFFIX_EVERY_LINE = false; \
    end \
    false

// TODO: if passed a string, return the string back (if possible)
// Get the string name of a log level, e.g. "DEBUG" for level 5
#define log_level_name(level) \
    ( \
        LOGGER_LEVEL_NONE_NAME  if level == LOGGER_LEVEL_NONE  else  ( \
        LOGGER_LEVEL_FATAL_NAME if level == LOGGER_LEVEL_FATAL else  ( \
        LOGGER_LEVEL_ERROR_NAME if level == LOGGER_LEVEL_ERROR else  ( \
        LOGGER_LEVEL_WARN_NAME  if level == LOGGER_LEVEL_WARN  else  ( \
        LOGGER_LEVEL_INFO_NAME  if level == LOGGER_LEVEL_INFO  else  ( \
        LOGGER_LEVEL_DEBUG_NAME if level == LOGGER_LEVEL_DEBUG else  ( \
        LOGGER_LEVEL_TRACE_NAME if level == LOGGER_LEVEL_TRACE else  ( \
        LOGGER_LEVEL_ALL_NAME   if level == LOGGER_LEVEL_ALL   else 0) \
    )))))))

// Returns log level as an int (will convert "DEBUG" to 5)
#define get_log_level(level_int_or_string) \
    ( \
        level_int_or_string if typeof(level_int_or_string) == 1 else ( \
            LOGGER_LEVEL_NONE   if level_int_or_string == LOGGER_LEVEL_NONE_NAME  else ( \
            LOGGER_LEVEL_FATAL  if level_int_or_string == LOGGER_LEVEL_FATAL_NAME else ( \
            LOGGER_LEVEL_ERROR  if level_int_or_string == LOGGER_LEVEL_ERROR_NAME else ( \
            LOGGER_LEVEL_WARN   if level_int_or_string == LOGGER_LEVEL_WARN_NAME  else ( \
            LOGGER_LEVEL_INFO   if level_int_or_string == LOGGER_LEVEL_INFO_NAME  else ( \
            LOGGER_LEVEL_DEBUG  if level_int_or_string == LOGGER_LEVEL_DEBUG_NAME else ( \
            LOGGER_LEVEL_TRACE  if level_int_or_string == LOGGER_LEVEL_TRACE_NAME else ( \
            LOGGER_LEVEL_ALL    if level_int_or_string == LOGGER_LEVEL_ALL_NAME   else 0) \
        ) \
    )))))))

// log_output() macro
// calls the private __log() function *if* the log level is configured to log
#define log_output(level, text) if get_log_level(level) <= LOGGER_LOG_LEVEL then call __log(get_log_level(level), text)

// private __log() called by the log_* macros
// procedure used (instead of macro) so that we can change the text as a variable
procedure __log(variable level, variable text) begin
    variable line, line_index, split_lines;
    if LOGGER_DISPLAY_LOG_LEVEL then
        if LOGGER_DISPLAY_LOG_LEVEL_IS_PREFIX then begin
            if LOGGER_DISPLAY_LOG_LEVEL_EVERY_LINE then begin
                split_lines = string_split(text, "\n");
                text = "";
                foreach line_index: line in split_lines
                    if line_index == (len_array(split_lines) - 1) then // Don't add \n to final line
                        text += sprintf(LOGGER_DISPLAY_LOG_LEVEL_FORMAT, log_level_name(level)) + line;
                    else
                        text += sprintf(LOGGER_DISPLAY_LOG_LEVEL_FORMAT, log_level_name(level)) + line + "\n";
            end else
                text = sprintf(LOGGER_DISPLAY_LOG_LEVEL_FORMAT, log_level_name(level)) + text;
        end else begin // Suffix:
            if LOGGER_DISPLAY_LOG_LEVEL_EVERY_LINE then begin
                split_lines = string_split(text, "\n");
                text = "";
                foreach line_index: line in split_lines
                    if line_index == (len_array(split_lines) - 1) then // Don't add \n to final line
                        text += line + sprintf(LOGGER_DISPLAY_LOG_LEVEL_FORMAT, log_level_name(level));
                    else
                        text += line + sprintf(LOGGER_DISPLAY_LOG_LEVEL_FORMAT, log_level_name(level)) + "\n";
            end else
                text = text + sprintf(LOGGER_DISPLAY_LOG_LEVEL_FORMAT, log_level_name(level));
        end
    if LOGGER_DISPLAY_PREFIX and LOGGER_PREFIX then begin
        if LOGGER_DISPLAY_PREFIX_EVERY_LINE then begin
            split_lines = string_split(text, "\n");
            text = "";
            foreach line_index: line in split_lines
                if line_index == (len_array(split_lines) - 1) then // Don't add \n to final line
                    text += LOGGER_PREFIX + line;
                else
                    text += LOGGER_PREFIX + line + "\n";
        end else
            text = LOGGER_PREFIX + text;
    end
    if LOGGER_DISPLAY_SUFFIX and LOGGER_SUFFIX then begin
        if LOGGER_DISPLAY_SUFFIX_EVERY_LINE then begin
            split_lines = string_split(text, "\n");
            text = "";
            foreach line_index: line in split_lines
                if line_index == (len_array(split_lines) - 1) then // Don't add \n to final line
                    text += line + LOGGER_SUFFIX;
                else
                    text += line + LOGGER_SUFFIX + "\n";
        end else
            text = text + LOGGER_SUFFIX;
    end
    if LOGGER_TEST then begin
        if not LOGGER_TEST_LOGS then begin
            LOGGER_TEST_LOGS = [];
            fix_array(LOGGER_TEST_LOGS);
        end 
        resize_array(LOGGER_TEST_LOGS, len_array(LOGGER_TEST_LOGS) + 1);
        LOGGER_TEST_LOGS[len_array(LOGGER_TEST_LOGS) - 1] = text;
    end
    if LOGGER_DEBUG_MSG then debug_msg(text);
    if LOGGER_DISPLAY_MSG then display_msg(text);
end

// Helpers for logging for different levels
#define log_trace(text) log_output(LOGGER_LEVEL_TRACE, text)
#define log_debug(text) log_output(LOGGER_LEVEL_DEBUG, text)
#define log_info(text)  log_output(LOGGER_LEVEL_INFO, text)
#define log_warn(text)  log_output(LOGGER_LEVEL_WARN, text)
#define log_error(text) log_output(LOGGER_LEVEL_ERROR, text)
#define log_fatal(text) log_output(LOGGER_LEVEL_FATAL, text)
