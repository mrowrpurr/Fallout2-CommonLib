#pragma once

// Returns the count of test log messages written to LOGGER_TEST_LOGS (or zero)
#define test_log_count \
    (len_array(LOGGER_TEST_LOGS) if LOGGER_TEST_LOGS else 0)

// Helper to ensure test logs array is initialized (because it defaults to 0)
#define initialize_test_logs \
    if not LOGGER_TEST_LOGS then begin \
        LOGGER_TEST_LOGS = []; \
        fix_array(LOGGER_TEST_LOGS); \
    end \
    false

// Returns the array of test log messages written to LOGGER_TEST_LOGS.
// Returns 0 if no logs have been written.
// Can alternatively explicitly call `initialize_test_logs()`
#define test_log_messages LOGGER_TEST_LOGS

// Returns the most recent message written to test log messages (or zero)
#define most_recent_test_log_message \
    (LOGGER_TEST_LOGS[len_array(LOGGER_TEST_LOGS) - 1] if LOGGER_TEST_LOGS else 0)

// Returns the test log message at the given index (or zero)
#define test_log_message_at(index) \
    (LOGGER_TEST_LOGS[index] if LOGGER_TEST_LOGS else 0)

// Clears the test log messages array
#define clear_test_log_messages \
    if LOGGER_TEST_LOGS and len_array(LOGGER_TEST_LOGS) > 0 then \
        call array_cut(LOGGER_TEST_LOGS, 0, len_array(LOGGER_TEST_LOGS))
