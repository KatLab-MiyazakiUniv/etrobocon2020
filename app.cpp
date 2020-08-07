#include "app.h"
#include "EtRobocon2020.h"
#include "Controller.h"

/**
 * メインタスク
 */
// tag::main_task_1[]
void main_task(intptr_t unused)
{
  EtRobocon2020::start();
  ext_tsk();
}
// end::main_task_2[]
