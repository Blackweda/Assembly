.text
.globl _start

start = 0   /* loop index */
max = 31    /* number to stop loop at */
num = 48   /* starting ascii value for 0 number */
/* index = %r10 - to store register 10 into index macro */

_start:
    mov     x3,start

loop:
    mov     x4,10           /* for calculating quotient/remainder */

    /* calculate quotient - store in x6 */
    udiv    x6,x3,x4      /* x6 = x3 / 10 */

    /* calculate remainder - store in x7 */
    msub    x7,x4,x6,x3   /* x7 = x3 - (10 * x6) */

    adr     x1, msg         /* msg location memory address */
    add     x6,x6,num       /* atoi */
    add     x7,x7,num       /* atoi */
    strb    w6,[x1,6]       /* store in msg + 6 bytes memory location */
    strb    w7,[x1,7]       /* store in msg + 7 bytes memory location */

    /* print */
    mov     x0,1            /* file descriptor: 1 is stdout */
    mov     x2,len
    mov     x8,64           /* write is syscall #64 */
    svc     0               /* invoke syscall */

    add     x3,x3,1         /* increment index */
    cmp     x3,max          /* check for end of loop */
    bne     loop            /* loop if compare returns false */

    mov     x0,0            /* status -> 0 */
    mov     x8,93           /* exit is syscall #93 */
    svc     0               /* invoke syscall */
 
.data

msg:    .ascii  "Loop:    \n"
        len = . - msg

