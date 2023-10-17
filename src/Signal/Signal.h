void exitp();
void  exitForeground(int signal);
void exitAll(int signal);
void killBackground(int signal, siginfo_t *siginfo, void *context);
