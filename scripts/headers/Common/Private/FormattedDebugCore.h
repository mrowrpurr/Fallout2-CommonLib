#pragma once

#define debug(text) __formatted_debug_output(DEBUG_PREFIX + text)
#define debug_array(arr) debug(debug_array_str(arr))

// Update to NOT use sprintf_array because you cannot use sprintf_array inside of sprintf_array

#define debug1(text, arg1) \
    debug(text + " (" + arg1 + ")")

#define debug2(text, arg1, arg2) \
    debug(text + " (" + arg1 + ") (" + arg2 + ")")

#define debug3(text, arg1, arg2, arg3) \
    debug(text + " (" + arg1 + ") (" + arg2 + ") (" + arg3 + ")")

#define debug4(text, arg1, arg2, arg3, arg4) \
    debug(text + " (" + arg1 + ") (" + arg2 + ") (" + arg3 + ") (" + arg4 + ")")

#define debug5(text, arg1, arg2, arg3, arg4, arg5) \
    debug(text + " (" + arg1 + ") (" + arg2 + ") (" + arg3 + ") (" + arg4 + ") (" + arg5 + ")")

#define debug6(text, arg1, arg2, arg3, arg4, arg5, arg6) \
    debug(text + " (" + arg1 + ") (" + arg2 + ") (" + arg3 + ") (" + arg4 + ") (" + arg5 + ") (" + arg6 + ")")

#define debug1f(text, arg1)                               debug(sprintf(text, arg1))
#define debug2f(text, arg1, arg2)                         debug(sprintf_array(text, [arg1, arg2]))
#define debug3f(text, arg1, arg2, arg3)                   debug(sprintf_array(text, [arg1, arg2, arg3]))
#define debug4f(text, arg1, arg2, arg3, arg4)             debug(sprintf_array(text, [arg1, arg2, arg3, arg4]))
#define debug5f(text, arg1, arg2, arg3, arg4, arg5)       debug(sprintf_array(text, [arg1, arg2, arg3, arg4, arg5]))
#define debug6f(text, arg1, arg2, arg3, arg4, arg5, arg6) debug(sprintf_array(text, [arg1, arg2, arg3, arg4, arg5, arg6]))
