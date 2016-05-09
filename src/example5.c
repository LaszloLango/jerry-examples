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

#include "jerry.h"

static void
print_value (const jerry_api_value_t *value_p)
{
  switch (value_p->type)
  {
    // Simple values: void, undefined, null, false, true
    case JERRY_API_DATA_TYPE_VOID:
    {
      printf ("void");
      break;
    }
    case JERRY_API_DATA_TYPE_UNDEFINED:
    {
      printf ("undefined");
      break;
    }
    case JERRY_API_DATA_TYPE_NULL:
    {
      printf ("null");
      break;
    }
    case JERRY_API_DATA_TYPE_BOOLEAN:
    {
      if (value_p->u.v_bool)
      {
        printf ("true");
      }
      else
      {
        printf ("false");
      }
      break;
    }
    // Float value
    case JERRY_API_DATA_TYPE_FLOAT32:
    {
      printf ("%f", value_p->u.v_float32);
      break;
    }
    // Double value
    case JERRY_API_DATA_TYPE_FLOAT64:
    {
      printf ("%lf", value_p->u.v_float64);
      break;
    }
    // Unsigned integer value
    case JERRY_API_DATA_TYPE_UINT32:
    {
      printf ("%d", value_p->u.v_uint32);
      break;
    }
    // String value
    case JERRY_API_DATA_TYPE_STRING:
    {
      // Determining required buffer size
      jerry_api_size_t req_sz = jerry_api_get_string_size (value_p->u.v_string);
      jerry_api_char_t *str_buf_p = (jerry_api_char_t *) malloc (req_sz);
      jerry_api_string_to_char_buffer (value_p->u.v_string,
                                       str_buf_p,
                                       req_sz);

      printf ("%s", (const char *) str_buf_p);

      free (str_buf_p);
      break;
    }
    // Object reference
    case JERRY_API_DATA_TYPE_OBJECT:
    {
      printf ("[JS object]");
      break;
    }
  }

  printf ("\n");
}

static void print_value (const jerry_api_value_t *value_p);

int
main (int argc, char * argv[])
{
  jerry_completion_code_t status = JERRY_COMPLETION_CODE_OK;

  // Initialize engine
  jerry_init (JERRY_FLAG_EMPTY);

  char cmd [256];
  while (true)
  {
    printf ("> ");

    // Input next command
    if (fgets (cmd, sizeof (cmd), stdin) == NULL
        || strcmp (cmd, "quit\n") == 0)
    {
      // If the command is 'quit', exit from loop
      break;
    }

    jerry_api_value_t ret_val;

    // Evaluate entered command
    status = jerry_api_eval ((const jerry_api_char_t *) cmd,
                             strlen (cmd),
                             false,
                             false,
                             &ret_val);

    // If command evaluated successfully, print value, returned by eval
    if (status == JERRY_COMPLETION_CODE_OK)
    {
      // 'eval' completed successfully
      print_value (&ret_val);
      jerry_api_release_value (&ret_val);
    }
    else
    {
      // Evaluated JS code thrown an exception
      // and didn't handle it with try-catch-finally
      printf ("Unhandled JS exception occured\n");
    }

    fflush (stdout);
  }

  // Cleanup engine
  jerry_cleanup ();

  return status;
}
