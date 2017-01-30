.text                         /* or section.text - used for keeping the actual code */
.globl    _start              /* tells kernel where program execution begins */

start = 0                     /* starting value for the loop index; note that this is a symbol (constant), not a variable */
max = 31                      /* loop exits when the index hits this number (loop condition is i<max) */
zero = 48                     /* start of decimal notation for character 0 */

_start:
    mov     $start,%r15       /* loop index start is in register 15 */
    mov     $10,%r13          /* put value 10 into register 13 */

loop:
    mov     $zero,%r14        /* loop index */
    mov     %r15,%rax         /* move data from register 15 into accumulator register */
    mov     $0,%rdx           /* put value 0 into data register */

    div     %r13              /* divide rax by register 13 and put quotient into rax and remainder into rdx*/

    mov     $zero,%r14        /* loop index */
    add     %rax,%r14         /* add quotient(in rax) to register 14 */
    movb    %r14b,msg+6       /* add 6 bits to register 14 */

    mov     $zero,%r14        /* loop index */
    add     %rdx,%r14         /* add remainder(in rdx) to register 14 */
    movb    %r14b,msg+7       /* add 7 bits to register 14*/

    movq    $len,%rdx
    movq    $msg,%rsi
    movq    $1,%rax
    syscall

    inc     %r15              /* increment index */
    cmp     $max,%r15         /* see if we're done */
    jne     loop              /* loop if we're not */

    mov     $0,%rdi           /* exit status */
    mov     $60,%rax          /* syscall sys_exit */
    syscall

.data                         /* for SEGFAULT error, stores as read/write */

msg:    .ascii "Loop:    \n"
        len = . - msg
