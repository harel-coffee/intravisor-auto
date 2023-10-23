#include <asm/host_ops.h>
#include <asm/cpu.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <asm-generic/ucontext.h>
#include <asm/sched.h>

void lkl_do_trap(int trapnr, int signr, char *str, struct ucontext *uctx,
		 long error_code, struct siginfo *info)
{
	struct task_struct* task;
	long ret;

	/* BUG: kernel not ready to process trap */
	BUG_ON(!lkl_is_running());

	LKL_TRACE("enter\n");

	/* Acquire lock to ensure that syscall trigger will
	 * not consume the signal generated by lkl_do_trap */
	ret = lkl_cpu_get();

	/* Failing to trap lead to inconsistent system, so trigger panic */
	if (ret < 0) {
		lkl_ops->panic();
		return;
	}

	/*
	 * We need to context switch to the correct LKL host task that is
	 * associated with this host thread.
	 *
	 * This code assumes that it is executed by the lthread that
	 * triggered the exeception.
	 */

	task = lkl_get_current_task_struct();

	LKL_TRACE("switching to host task (task=%s)\n", task->comm);
	switch_to_host_task(task);

#if 0
	LKL_TRACE("injecting signal into lkl\n");
	force_sig_info((struct kernel_siginfo *)info);
#else
	lkl_printf("not implemented at %d %s\n", __LINE__, __func__);
#endif
	/* invoke the signal handler for this trap once we have given up the CPU */
	/* otherwise we may take the CPU lock again and fail. */
	lkl_process_trap(signr, uctx);  
	
	lkl_cpu_put();
}