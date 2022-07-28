#pragma once

#define display(text) __formatted_display_output(DISPLAY_PREFIX + text)
#define display_formatted_array(arr) display(debug_array_str(arr))

#define display1(text, arg1) \
    display(text + " (" + arg1 + ")")

#define display2(text, arg1, arg2) \
    display(text + " (" + arg1 + ") (" + arg2 + ")")

#define display3(text, arg1, arg2, arg3) \
    display(text + " (" + arg1 + ") (" + arg2 + ") (" + arg3 + ")")

#define display4(text, arg1, arg2, arg3, arg4) \
    display(text + " (" + arg1 + ") (" + arg2 + ") (" + arg3 + ") (" + arg4 + ")")

#define display5(text, arg1, arg2, arg3, arg4, arg5) \
    display(text + " (" + arg1 + ") (" + arg2 + ") (" + arg3 + ") (" + arg4 + ") (" + arg5 + ")")

#define display6(text, arg1, arg2, arg3, arg4, arg5, arg6) \
    display(text + " (" + arg1 + ") (" + arg2 + ") (" + arg3 + ") (" + arg4 + ") (" + arg5 + ") (" + arg6 + ")")

#define display1f(text, arg1)                               display(sprintf(text, arg1))
#define display2f(text, arg1, arg2)                         display(sprintf_array(text, [arg1, arg2]))
#define display3f(text, arg1, arg2, arg3)                   display(sprintf_array(text, [arg1, arg2, arg3]))
#define display4f(text, arg1, arg2, arg3, arg4)             display(sprintf_array(text, [arg1, arg2, arg3, arg4]))
#define display5f(text, arg1, arg2, arg3, arg4, arg5)       display(sprintf_array(text, [arg1, arg2, arg3, arg4, arg5]))
#define display6f(text, arg1, arg2, arg3, arg4, arg5, arg6) display(sprintf_array(text, [arg1, arg2, arg3, arg4, arg5, arg6]))
