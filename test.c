#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>

#define JACK "Jack"
#define NAME_LEN 24

struct person {
    unsigned int id;
    char *name;
    unsigned short age;
    unsigned short height;
    unsigned short is_fat:1;
    char hometown;
    struct kobject kobj;
    struct kobj_type type;
    struct sysfs_ops ops;
};

struct persion_attribute {
    struct attribute attr;
    ssize_t (*show)(struct kobject *kobj, struct persion_attribute *attr, char *buf); 
    ssize_t (*store)(struct kobject *kobj, struct persion_attribute *attr, const char *buf, size_t count); 
};


struct person *Jack = NULL;
struct person *Lucy = NULL;

ssize_t get_jack_name(struct kobject *kobj, struct persion_attribute *attr, char *buf)
{
	if(Jack)
		memcpy(buf, Jack->name, NAME_LEN);
	return NAME_LEN;
}
ssize_t set_jack_name(struct kobject *kobj, struct persion_attribute *attr, const char *buf, size_t count)
{
	memcpy(Jack->name, buf, count);
	return count;
}

struct persion_attribute jack_attr = {
	.attr.name = "name",
	.attr.mode = 0755,
	.show = get_jack_name,
	.store = set_jack_name,
};

void person_release(struct kobject *kobj)
{
	struct person *per = container_of(kobj, struct person, kobj);
    printk("person_release\n");
	kfree(per);
}

static ssize_t per_show(struct kobject *kobj, struct attribute *attr, char *buf)
{
	struct persion_attribute *name = container_of(attr, struct persion_attribute, attr);
	ssize_t ret = -EIO;
	if(name->show) {
		ret = name->show(kobj, name, buf);
	}
    return ret;
}
static ssize_t per_store(struct kobject *kobj, struct attribute *attr, const char *buf, size_t count)
{
    struct persion_attribute *name = container_of(attr, struct persion_attribute, attr);
	ssize_t ret = -EIO;
	if(name->store) {
		ret = name->store(kobj, name, buf, count);
	}
    return ret;
}
const struct sysfs_ops per_sysfs_ops = {
    .show   = per_show,
    .store  = per_store,
};
static struct kobj_type person_type = {
	.release = person_release,
	.sysfs_ops = &per_sysfs_ops,
};

static int check_name(char *name)
{
    char *c = NULL;
    if(!name)
		return -1;
	c = name;
	if(*c == '\0')
		return -2;
	while(*c != '\0')
	{
		if((*c >= 'a' && *c <= 'z') || (*c >= 'A' && *c <= 'Z'))
		{
			c ++;
		} else {
			printk("Invalid character!\n");
			return -3;
		}
	}
	return 0;
}

static struct person *create_person(char *name)
{
	struct person *per = NULL;

	if(check_name(name) != 0)
	{
		printk("error name for a person\n");
		return NULL;
	}
	per = (struct person *)kmalloc(sizeof(struct person), GFP_KERNEL);
	if(!per)
	{
		printk("kmalloc person failed!\n");
		return NULL;
	}
	memset(per, 0, sizeof(struct person));
	per->name = name;

	return per;
}



/* 驱动模块加载 */
static int __init test_kobject_init(void)
{
    int ret;
	struct kset *people = NULL;
	
	people = kset_create_and_add("people", NULL, NULL);
	if(people == NULL) {
		printk("Failed to make a dir named people in sysfs\n");
		return -1;
    }

	Jack = create_person(JACK);
	if(!Jack) {
		printk("failed to create a person named %s\n", JACK);
		return -2;
    }

	Jack->kobj.kset = people;
	kobject_init(&Jack->kobj, &person_type);
    ret = kobject_add(&Jack->kobj, NULL, JACK);
	if(ret != 0) {
		printk("An error found while add %s\n", JACK);
		kfree(Jack);
	}

	ret = sysfs_create_file(&Jack->kobj, &jack_attr.attr);
	if(ret != 0) {
		printk("Waring, Failed to create a file named name\n");
	}

	return 0;
}

/* 驱动模块卸载 */
static void __exit test_kobject_exit(void)
{
	if(Jack) {
		sysfs_remove_file(&Jack->kobj, &jack_attr.attr);
		kobject_del(&Jack->kobj);
		if(Jack->kobj.kset) {
			kset_unregister(Jack->kobj.kset);
		}
	}
}

module_init(test_kobject_init);
module_exit(test_kobject_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("suguoxu");
