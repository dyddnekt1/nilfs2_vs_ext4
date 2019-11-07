// yong woo kim, sang geun bae 2019.10.30
#include <linux/init.h>
#include <linux/module.h>
#include <linux/bio.h>

extern struct my_data my_queue[MY_QUEUE_SIZE];
extern int my_idx;
extern int my_number;
extern bool my_queue_enable;
extern void my_enqueue(struct my_data queue[], struct my_data data);
extern struct my_data my_dequeue(struct my_data queue[]);

static int hello_init(void)
{
	while(my_number != 0)
		my_dequeue(my_queue);
	printk(KERN_ALERT "Module init\n");
	my_queue_enable = true;
	return 0;
}
static void hello_exit(void)
{
	printk(KERN_INFO "%d data in queue", my_number);
	while(my_number != 0)
	{
		struct my_data data;
		data = my_dequeue(my_queue);
		printk(KERN_INFO "%-7s %-12lld %-8llu", data.name, data.time ,data.block_number);
	}
	printk(KERN_ALERT "Module exit\n");
	my_queue_enable = false;
}
module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("KYW");
MODULE_DESCRIPTION("It's Simple");
MODULE_LICENSE("GPL");
MODULE_VERSION("NEW");
