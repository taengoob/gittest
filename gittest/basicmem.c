#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/slab.h>
#include <linux/vmalloc.h>

void kmalloc_test( void )
{
    char *buff;
	unsigned long allocsize;
    
    printk( "kmalloc test\n" );
    
	/* TODO: 1024 사이즈 만큼 kmalloc로 buff에 할당하기 */
	allocsize = 4096;
	buff = kmalloc(allocsize, GFP_KERNEL);	 
	if( buff != NULL )
    {
        sprintf( buff, "kmalloc test memory\n" );
        printk( buff );
    
        kfree( buff );
    }    
    
    /* TODO: kmalloc를 이용해 kmalloc의 최대 만큼 할당해 보기 */
	allocsize = KMALLOC_MAX_SIZE;
	buff = kmalloc(allocsize, GFP_KERNEL);
	if( buff != NULL )
    {
        printk( "Big Memory Ok\n" );
        kfree( buff );
    }
    
}

void vmalloc_test( void )
{
    char *buff;
	unsigned long allocsize;
    printk( "vmalloc test\n" );
    
    /* TODO: vmalloc를 사용해 kmalloc의 최대 + 100 만큼 할당하기 */
	allocsize = KMALLOC_MAX_SIZE + 100;
	buff = vmalloc(allocsize);
	if( buff != NULL )
    {
        sprintf( buff, "vmalloc test ok\n" );
        printk( buff );
    
        vfree( buff );
    }    

}

void get_free_pages_test( void )
{
    char *buff;
    int   order;

    printk( "get_free_pages test\n" );
    
    order = get_order(8192);
    buff  = (char *)(__get_free_pages( GFP_KERNEL, order ));
    if( buff != NULL) 
    {
        sprintf( buff, "__get_free_pages test ok [%d]\n", order );
        printk( buff );
        
        free_pages((unsigned long)buff, order);
    }
}

int memtest_init(void)      
{ 
    //char *data;
    
    printk("Module Memory Test\n" );
    
    kmalloc_test();
    vmalloc_test();
    get_free_pages_test();
    
    return 0; 
}

void memtest_exit(void)  
{ 
    printk("Module Memory Test End\n"); 
}

module_init(memtest_init);
module_exit(memtest_exit);

MODULE_LICENSE("Dual BSD/GPL");
