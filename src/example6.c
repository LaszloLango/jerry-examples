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

struct my_struct
{
  const char *msg;
} my_struct;

/**
 * Get a string from a native object
 */
static bool
get_msg_handler (const jerry_api_object_t *function_obj_p, /**< function object */
                 const jerry_api_value_t *this_p, /**< this arg */
                 jerry_api_value_t *ret_val_p, /**< return argument */
                 const jerry_api_value_t *args_p, /**< function arguments */
                 const jerry_api_length_t args_cnt) /**< number of function arguments */
{
  jerry_api_string_t *msg_str_p = jerry_api_create_string ((const jerry_api_char_t *) my_struct.msg);
  *ret_val_p = jerry_api_create_string_value (msg_str_p);

  return true;
} /* get_msg_handler */

int
main (int argc, char * argv[])
{
  jerry_completion_code_t status = JERRY_COMPLETION_CODE_OK;

  /* Initialize engine */
  jerry_init (JERRY_FLAG_EMPTY);

  /* Do something with the native object */
  my_struct.msg = "Hello World";

  /* Create an empty JS object */
  jerry_api_object_t *object_p = jerry_api_create_object ();

  /* Create a JS function object and wrap into a jerry value */
  jerry_api_value_t object_value;
  object_value.type = JERRY_API_DATA_TYPE_OBJECT;
  object_value.u.v_object = jerry_api_create_external_function (get_msg_handler);

  /* Set the native function as a property of the empty JS object */
  jerry_api_set_object_field_value (object_p,
                                    (const jerry_api_char_t *) "myFunc",
                                    &object_value);
  jerry_api_release_value (&object_value);

  /* Wrap the (now it is not empty) JS object into a jerry api value */
  object_value.type = JERRY_API_DATA_TYPE_OBJECT;
  object_value.u.v_object = object_p;
  jerry_api_object_t *global_obj_p = jerry_api_get_global ();

  /* Add the JS object to the global context */
  jerry_api_set_object_field_value (global_obj_p,
                                    (const jerry_api_char_t *) "MyObject",
                                    &object_value);
  jerry_api_release_value (&object_value);
  jerry_api_release_object (global_obj_p);

  /* Now we have a "builtin" object called MyObject with a function called myFunc()
   *
   * Equalent JS code:
   *                  var MyObject = { myFunc() { return "some string value"; } }
   */
  const jerry_api_char_t script[] = "var str = MyObject.myFunc(); \
                                     print (str);";
  size_t script_size = strlen ((const char *) script);

  jerry_api_value_t eval_ret;

  /* Evaluate script */
  status = jerry_api_eval (script,
                           script_size,
                           false,
                           false,
                           &eval_ret);

   /* Free JavaScript value, returned by eval */
   jerry_api_release_value (&eval_ret);

  /* Cleanup engine */
  jerry_cleanup ();

  return status;
}
