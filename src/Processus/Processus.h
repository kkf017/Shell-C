typedef struct TPID_T TPID_T;
struct TPID_T{
	int element;
	TPID_T *next;
};


pid_t *getForeground();
TPID_T **getBackground();


void push(TPID_T **first,pid_t n);
int pop(TPID_T **first);
int popv(TPID_T **first,pid_t n);
int in(TPID_T **first, pid_t n);
void clear(TPID_T **first);
void display(TPID_T **first);

