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
main (int argc, char * argv[]) {
  const jerry_api_char_t str[] = "Hello, World!";
  const jerry_api_char_t var_name[] = "s";
  const jerry_api_char_t script[] = "print (s);";

  // Initializing JavaScript environment
  jerry_init (JERRY_FLAG_EMPTY);

  // Getting pointer to the Global object
  jerry_api_object_t *object_p = jerry_api_get_global ();

  // Constructing string
  jerry_api_string_t *str_val_p = jerry_api_create_string (str);

  // Constructing string value descriptor
  jerry_api_value_t value;
  value.type = JERRY_API_DATA_TYPE_STRING;
  value.u.v_string = str_val_p;

  // Setting the string value to field of the Global object
  jerry_api_set_object_field_value (object_p, var_name, &value);

  // Releasing string value, as it is no longer necessary outside of engine
  jerry_api_release_string (str_val_p);

  // Same for pointer to the Global object
  jerry_api_release_object (object_p);

  jerry_api_value_t eval_ret;

  // Now starting script that would output value of just initialized field
  jerry_api_eval (script,
                  strlen ((const char *) script),
                  false,
                  false,
                  &eval_ret);

  // Free JavaScript value, returned by eval
  jerry_api_release_value (&eval_ret);

  // Freeing engine
  jerry_cleanup ();

  return 0;
}