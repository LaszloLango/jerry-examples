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

  jerry_completion_code_t return_code = jerry_run_simple (script,
                                                          script_size,
                                                          JERRY_FLAG_EMPTY);

  return return_code;
}
