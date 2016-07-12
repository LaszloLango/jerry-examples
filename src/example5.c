/* Copyright 2016 Samsung Electronics Co., Ltd.
 * Copyright 2016 University of Szeged.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdlib.h>
#include <string.h>

#include "jerry-api.h"
#include "jerry-port.h"

static void
print_value (const jerry_value_t value)
{
  if (jerry_value_is_undefined (value))
  {
    jerry_port_logmsg (stdout, "undefined");
  }
  else if (jerry_value_is_null (value))
  {
    jerry_port_logmsg (stdout, "null");
  }
  else if (jerry_value_is_boolean (value))
  {
    if (jerry_get_boolean_value (value))
    {
      jerry_port_logmsg (stdout, "true");
    }
    else
    {
      jerry_port_logmsg (stdout, "false");
    }
  }
  /* Float value */
  else if (jerry_value_is_number (value))
  {
    jerry_port_logmsg (stdout, "number");
  }
  /* String value */
  else if (jerry_value_is_string (value))
  {
    /* Determining required buffer size */
    jerry_size_t req_sz = jerry_get_string_size (value);
    jerry_char_t str_buf_p[req_sz];

    jerry_string_to_char_buffer (value, str_buf_p, req_sz);

    jerry_port_logmsg (stdout, "%s", (const char *) str_buf_p);
  }
  /* Object reference */
  else if (jerry_value_is_object (value))
  {
    jerry_port_logmsg (stdout, "[JS object]");
  }

  jerry_port_logmsg (stdout, "\n");
}

int
main (int argc, char * argv[])
{
  bool is_done = false;

  /* Initialize engine */
  jerry_init (JERRY_INIT_EMPTY);

  while (!is_done)
  {
    char cmd [256];
    char *cmd_tail = cmd;
    size_t len = 0;

    jerry_port_logmsg (stdout, "> ");

    /* Read next command */
    while (true)
    {
      if (fread (cmd_tail, 1, 1, stdin) != 1 && len == 0)
      {
        is_done = true;
        break;
      }
      if (*cmd_tail == '\n')
      {
        break;
      }

      cmd_tail++;
      len++;
    }

    jerry_value_t ret_val;

    /* Evaluate entered command */
    ret_val = jerry_eval ((const jerry_char_t *) cmd,
                          len,
                          false);

    /* If command evaluated successfully, print value, returned by eval */
    if (jerry_value_has_error_flag (ret_val))
    {
      /* Evaluated JS code thrown an exception
       *  and didn't handle it with try-catch-finally */
      jerry_port_errormsg ("Unhandled JS exception occured: ");
    }

    print_value (ret_val);
    jerry_release_value (ret_val);
  }

  /* Cleanup engine */
  jerry_cleanup ();

  return 0;
}
