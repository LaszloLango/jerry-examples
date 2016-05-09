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
 
#include <string.h>
#include "jerry.h"

int
main (int argc, char * argv[])
{
  const jerry_api_char_t script[] = "print ('Hello, World!');";
  size_t script_size = strlen ((const char *) script);

  // Initialize engine
  jerry_init (JERRY_FLAG_EMPTY);

  // Setup Global scope code
  jerry_api_object_t *error_object_p = NULL;
  if (!jerry_parse (script, script_size, &error_object_p))
  {
    // Error object must be freed, if parsing is failed
    jerry_api_release_object (error_object_p);
  }
  else
  {
    // Execute Global scope code
    jerry_api_value_t error_value = jerry_api_create_void_value ();
    jerry_completion_code_t return_code = jerry_run (&error_value);

    if (return_code == JERRY_COMPLETION_CODE_UNHANDLED_EXCEPTION)
    {
      // Error value must be freed, if 'jerry_run' returns with an unhandled exception
      jerry_api_release_value (&error_value);
    }
  }

  // Cleanup engine
  jerry_cleanup ();

  return 0;
}
