# `Logger` for Fallout 2 scripts

> Configurable logs for your Star-Trek Scripting Language!

```pascal
#include "Common\Logger.h"

procedure start begin
    // Configure Logger
    set_log_level("INFO");
    set_logger_prefix("[MyMod] "); 
end

procedure my_mod_code begin
    // Use Logger
    log_trace("Low level stuff");
    log_info("Some info!");
    log_warn("Oh noes!");
end
```

#### `debug.log`

```
[MyMod] [INFO] Some info!
[MyMod] [WARN] Oh noes!
```

---

# Installation

### Enable `debug.log`

To view the logs in your `debug.log`, you'll need to enable Fallout 2 debug logs:

1. In `ddraw.ini`, set `DebugMode=2` in the `[Debugging]` section
    ```ini
    [Debugging]
    ; ...
    DebugMode=2
    ```
2. In `fallout2.cfg`, set everything in the `[debug]` section to `=1`
    ```ini
    [debug]
    mode=environment
    output_map_data_info=1
    show_load_info=1
    show_script_messages=1
    show_tile_num=1
    ```

Now the game will generate a new `debug.log` file in your Fallout 2 root directory
whenever you run the game.

> 💡 **Tip** - use a log viewer such as [LogExpert](https://github.com/zarunbal/LogExpert) or
> simply Notepad++'s "_Monitoring (tail -f)_" mode to preview the `debug.log` in real-time.
>
> [LogExpert](https://github.com/zarunbal/LogExpert) makes it easy to highlight lines of `debug.log`
> in different colors, e.g. depending on if the output is `[WARN]` or `[INFO]`

### Download `Logger.h`

1. Copy the latest [`Logger.h`](https://raw.githubusercontent.com/mrowrpurr/Fallout2-Logger/main/scripts/headers/Logger.h) into your `scripts/HEADERS/` folder.
2. `#include "Common\Logger.h"`
3. `log_debug("Hello!");
4. Check your `debug.log`
5. _Done!_

#### Optional

> If you want to test your log output, you can `enable_test_logging;` which will write all 
> log messages to an in-memory array for testing.
>
> For this, copy the latest `LoggerTestHelper.h` into your `scripts/HEADERS/` folder.

# Documentation

> _TODO_
