#ifndef __ANSWER_H__

struct Status;

void answer1(struct Status *sta);
void answer2(struct Status *sta);
void answer3(struct Status *sta);
void answer4(struct Status *sta);
void answer4_fast(struct Status *sta);
void answer_do_nothing(struct Status *sta);

void answer_select_rpc(unsigned short var, void *para);

#endif // !__ANSWER_H__
