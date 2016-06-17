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

/**
 * Add param to 'this.x'
 */
static bool
add_handler (const jerry_object_t *function_obj_p, /**< function object */
             const jerry_value_t this_p, /**< this arg */
             const jerry_value_t *args_p, /**< function arguments */
             const jerry_length_t args_cnt, /**< number of function arguments */
             jerry_value_t *ret_val_p) /**< [out] return argument */
{
  /* Get 'this.x' */
  jerry_value_t x_val = jerry_get_object_field_value (jerry_get_object_value (this_p),
                                                      (const jerry_char_t *) "x");


  if (!jerry_value_is_error (x_val))
  {
    /* Convert Jerry API values to double */
    double x = jerry_get_number_value (x_val);
    double d = jerry_get_number_value (*args_p);

    /* Add the parameter to 'x' */
    jerry_value_t res_val = jerry_create_number_value (x + d);

    /* Set the new value of 'this.x' */
    jerry_set_object_field_value (jerry_get_object_value (this_p),
                                  (const jerry_char_t *) "x",
                                  res_val);

  }

  return true;
} /* add_handler */

int
main (int argc, char * argv[])
{
  jerry_completion_code_t status = JERRY_COMPLETION_CODE_OK;

  /* Initialize engine */
  jerry_init (JERRY_FLAG_EMPTY);

  /* Create a JS object */
  const jerry_char_t my_js_object[] = " \
    MyObject = \
    { x : 12, \
      y : 'Value of x is ', \
      foo: function () \
      { \
        return this.y + this.x; \
      } \
    } \
  ";

  jerry_value_t my_js_obj_val;

  /* Evaluate script */
  status = jerry_eval (my_js_object,
                       strlen ((const char *) my_js_object),
                       false,
                       false,
                       &my_js_obj_val);

  jerry_object_t *object_p = jerry_get_object_value (my_js_obj_val);

  /* Create a JS function object and wrap into a jerry value */
  jerry_object_t *add_func_obj_p = jerry_create_external_function (add_handler);
  jerry_value_t object_value = jerry_create_object_value (add_func_obj_p);

  /* Set the native function as a property of previously created MyObject */
  jerry_set_object_field_value (object_p,
                                (const jerry_char_t *) "add2x",
                                object_value);
  jerry_release_value (object_value);

  /* Free JavaScript value, returned by eval (my_js_object) */
  jerry_release_value (my_js_obj_val);

  const jerry_char_t script[] = " \
    var str = MyObject.foo (); \
    print (str); \
    MyObject.add2x (5); \
    print (MyObject.foo ()); \
  ";
  size_t script_size = strlen ((const char *) script);

  jerry_value_t eval_ret;

  /* Evaluate script */
  status = jerry_eval (script,
                       script_size,
                       false,
                       false,
                       &eval_ret);

  /* Free JavaScript value, returned by eval */
  jerry_release_value (eval_ret);

  /* Cleanup engine */
  jerry_cleanup ();

  return (int) status;
}
