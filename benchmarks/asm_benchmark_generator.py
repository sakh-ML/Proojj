'''
Dieses Python-Skript generiert automatisch C-Code, der Inline-Assembly-Code enthält.
Der generierte C-Code führt in einer Schleife eine Million Wiederholungen aus, 
in denen eine Sequenz von Assembly-Befehlen ausgeführt wird.
Diese Befehle beinhalten Divisionen und Additionen zwischen verschiedenen CPU-Registern,
um z.B. CPU-Leistung oder bestimmte Instruktionspfade zu benchmarken.
'''


asm = r'''"mov $0xFFFFFFFFFFFFFFFF, %%rax;"
"mov $0xFFFFFFFFFFFFFFFE, %%r8;"
"xor %%rdx, %%rdx;"
'''

for _ in range(1000):
    asm += '"div %%r8;"\n'
    for _ in range(5):
        for register in range(9, 16):
            
            src_register = '%%rdx'; # inorder
            #src_register == '%%r8'; // out of order
            asm += f'"add %%r{register}, {src_register};"' + '\n'

program = rf"""#define REPS 1000000UL

int main() {{
    for (unsigned long i = 0; i < REPS; i++) {{
        asm volatile (
{asm}:::"r8","r9","r10","r11","r12","r13","r14","r15"
        );
    }}
}}

"""

with open("bench.c", "w") as f:
    f.write(program)

