#include "turn.h"
#include <sys/_stdint.h>

int8_t turn_abs_cnt = 0;
float turn_abs_angle = 0;
int8_t turn_abs_max_speed = 5;

struct PID *turn_abs_pid;
float turn_abs_origin;
float turn_abs_move_line_angle;
static struct pid_data turn_abs_head_data;
struct PID *turn_abs_XZ_pid = NULL;

/**
 * 初始化转向PID结构体
 */

// 初始化转向 得到原始角度 设置pid的值
void turn_abs_head_init()
{
    turn_abs_origin = Get_gyr_value(gyr_z_yaw) + 180;
    pid_init(&turn_abs_head_data, 0, 0.6, 0, 0, 5);
}

void turn_abs(void *para)
{
    float diff;

    diff = turn_head_diff(turn_abs_angle, turn_abs_origin);
    int turn_speed = pid_inc(&turn_abs_head_data, -diff);
    if ((diff <= 2) && (diff >= -2))
    {
        turn_abs_cnt--;
        if (turn_abs_cnt == 0)
        {
            turn_abs_angle = 0;
            status.wheels[FONT_LEFT].target = 0;
            status.wheels[FONT_RIGHT].target = 0;

            return;
        }
    }
    if (turn_speed > 100)
        turn_speed = TURN_SPEED;
    if (turn_speed < -100)
        turn_speed = -TURN_SPEED;
    status.wheels[FONT_LEFT].target = -turn_speed;
    status.wheels[FONT_RIGHT].target = turn_speed;

    
    Task T = task_new(turn_abs, para);
    task_timed_insert(&task.timed, T, (uint32_t)para & 0xff);
}

void turn_abs_start_turn(int16_t angle, uint8_t time)
{
    uint32_t para = angle <<16 | time;     
    turn_abs_angle = (float)angle;
    turn_abs_cnt = 1;
    // turn_abs_XZ_pid = initPID(0.1, 0, 0, 1, 10);
    turn_abs((void *)para);
}

