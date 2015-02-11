/* devgibson: hackers in 'yo kernel!
 * Copyright (C) 2015 @cyphar <cyphar@cyphar.com>
 * Copyright (C) 2015 @sysr-q <chris@gibsonsec.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define pr_fmt(fmt) "[" KBUILD_MODNAME "]: " fmt

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>

#include "plague.h"

struct gibson_t {
	bool done;
	bool first;

	struct script_t *script;
	int line;

	size_t msg_len;
	char *msg;
	char *msgp;
};

#define DEVICE_NAME "gibson"
#define LINE_FORMAT "<%s> %s\n"

extern struct script_t hackers;

static void __gibson_msg_reset(struct gibson_t *gibson) {
	kfree(gibson->msg);
	gibson->msg_len = 0;
	gibson->msg = NULL;
	gibson->msgp = NULL;
}

static int gibson_open(struct inode *inode, struct file *filp) {
	struct gibson_t *gibson;

	gibson = kzalloc(sizeof(*gibson), GFP_KERNEL);
	if(!gibson)
		return -ENOMEM;

	gibson->first = true;
	gibson->script = &hackers;

	gibson->line = 0;
	gibson->msg = NULL;
	gibson->msgp = NULL;

	filp->private_data = gibson;
	return 0;
}

static int gibson_release(struct inode *inode, struct file *filp) {
	struct gibson_t *gibson = filp->private_data;

	kfree(gibson->msg);
	kfree(gibson);
	return 0;
}

static ssize_t gibson_read(struct file *filp, char *buffer, size_t length, loff_t *offset) {
	struct gibson_t *gibson = filp->private_data;
	int bytes_read = 0;

	if(gibson->done)
		return 0;

	if(gibson->first) {
		pr_info("%s presents: `%s' (directed by %s)\n", gibson->script->presenter, gibson->script->title, gibson->script->director);
		gibson->first = false;
	}

	if(gibson->msg && (gibson->msgp - gibson->msg) >= gibson->msg_len) {
		__gibson_msg_reset(gibson);
		gibson->line++;
	}

	if(gibson->line >= gibson->script->len) {
		gibson->done = true;
		return 0;
	}

	if(!gibson->msg) {
		struct line_t *cur = &gibson->script->lines[gibson->line];

		/* get the required buffer size */
		int size = snprintf(NULL, 0, LINE_FORMAT, cur->character, cur->text) + 1;
		gibson->msg = kzalloc(size + 1, GFP_KERNEL);
		if(!gibson->msg)
			return -ENOMEM;
		snprintf(gibson->msg, size, LINE_FORMAT, cur->character, cur->text);

		/* update length and pointers */
		gibson->msgp = gibson->msg;
		gibson->msg_len = size - 1;
	}

	while((length-- > 0) && (gibson->msgp - gibson->msg) < gibson->msg_len) {
		put_user(*(gibson->msgp++), buffer++);
		bytes_read++;
	}

	return bytes_read;
}

static loff_t gibson_llseek(struct file *filp, loff_t off, int whence) {
	struct gibson_t *gibson = filp->private_data;
	int new_pos = 0;

	switch(whence) {
		case SEEK_SET:
			new_pos = off;
			break;

		case SEEK_CUR:
			new_pos = gibson->line + off;
			break;

		case SEEK_END:
			new_pos = gibson->script->len + off;
			break;

		default:
			return -EINVAL;
	}

	if(new_pos < 0 || new_pos > gibson->script->len)
		return -EINVAL;

	__gibson_msg_reset(gibson);
	gibson->line = new_pos;
	return new_pos;
}

static ssize_t gibson_write(struct file *filp, const char *buff, size_t len, loff_t *off) {
	pr_err("ARF! ARF! WE GOTCHA!\n");
	return -EINVAL;
}

static const struct file_operations fops = {
	.owner   = THIS_MODULE,
	.read    = gibson_read,
	.write   = gibson_write,
	.llseek  = gibson_llseek,
	.open    = gibson_open,
	.release = gibson_release,
};

static struct miscdevice gibson_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name  = DEVICE_NAME,
	.fops  = &fops,
	.mode  = S_IRUGO,
};

static int gibson_init(void) {
	int ret = misc_register(&gibson_dev);
	if(ret) {
		pr_err("There's a new virus in the database.\n");
		pr_err("It's replicating -- eating up memory.\n");
		pr_err("Type 'cookie', you idiot.\n");

		return ret;
	}

	pr_info("Passphrase 'GOD' accepted.\n");
	pr_info("Clearly someone hasn't read Linus' carefully prepared shitstorm of a memo on out-of-tree patchsets.\n");
	pr_info("w00t w00t, g0t r00t. :)\n");

	return 0;
}

static void gibson_exit(void) {
	int ret = misc_deregister(&gibson_dev);
	if (ret) {
		pr_err("A rabbit is in the misc device registration system.\n");
		pr_err("Administering flu shot... done.\n");
		return;
	}

	pr_info("MESS WITH THE BEST, DIE LIKE THE REST.\n");
}

module_init(gibson_init);
module_exit(gibson_exit);

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Aleksa Sarai (cyphar)");
MODULE_DESCRIPTION("Hackers in yo' kernel!");
MODULE_SUPPORTED_DEVICE(DEVICE_NAME);
