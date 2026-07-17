#include "emulator.h"

void execute_instruction(struct machine *mach, uint32_t insn);

void emulate(FILE *fp_in, FILE *fp_out)
{
    /* Création et initialisation de la machine émulée */
    struct machine *mach = malloc(sizeof *mach);
    machine_init(mach);

    /* Chargement des instructions assemblées dans la mémoire */
    int insn_count = 0;
    uint32_t insn;
    while(fscanf(fp_in, "%x", &insn) > 0) {
        machine_suw(mach, 4 * insn_count, insn);
        insn_count++;
    }

    /* Boucle de lecture - décodage - exécution des instructions */
    // TODO: Boucle :
    // 1. Lire l'opcode à l'adresse mach->PC avec une fonction machine_...()
    // 2. Si l'opcode vaut 0, on arrête l'émulation
    // 3. Sinon, l'afficher (pour debugger), l'exécuter, et continuer
    while(machine_luw(mach, mach->PC)!= 0){
            execute_instruction(mach, insn);
    }
    /* Affiche de l'état final dans fp_out */
    // TODO: Afficher dans fp_out (avec fprintf()) la valeur finale des
    // registres (mach->regs[0..31]) sous la forme spécifiée dans l'énoncé
    for(int i = 0; i<32; i++){
        fprintf(fp_out, "x%d: %d\n",i ,mach->regs[i]);
    }
    free(mach);
}

void B_type(uint32_t insn, int *rs1, int *rs2, int *imm)
{
    *rs1 = (insn >> 15) & 0x1f;
    *rs2 = (insn >> 20) & 0x1f;
    *imm = (((int32_t)insn >> 31) << 12)
           | (((insn >> 7) & 1) << 11)
           | (((insn >> 25) & 0x3f) << 5)
           | (((insn >> 8) & 0xf) << 1);
    printf(":: B type (rs1=%d rs2=%d imm=%d)\n", *rs1, *rs2, *imm);
}

void J_type(uint32_t insn, int *rd, int *imm)
{
    *rd = (insn >> 7) & 0x1f;
    *imm = (((int32_t)insn >> 31) << 20)
           | (((insn >> 12) & 0xff) << 12)
           | (((insn >> 20) & 1) << 11)
           | (((insn >> 21) & 0x3ff) << 1);
    printf(":: J type (rd=%d imm=%d)\n", *rd, *imm);
}


void R_type(uint32_t insn, int *rd, int *rs1, int *rs2)
{
    // TODO: Décoder un opcode R-type

    printf(":: R type (rd=%d rs1=%d rs2=%d)\n", *rd, *rs1, *rs2);
}

void I_type(uint32_t insn, int *rd, int *rs1, int *imm)
{
    // TODO: Décoder un opcode I-type (/!\ extension de signe)

    printf(":: I type (rd=%d rs1=%d imm=%d)\n", *rd, *rs1, *imm);
}

void S_type(uint32_t insn, int *rs1, int *rs2, int *imm)
{
    // TODO: Décoder un opcode S-type (/!\ recollage imm + extension de signe)

    printf(":: S type (rs1=%d rs2=%d imm=%d)\n", *rs1, *rs2, *imm);
}

// TODO: do_addi(), do_add(), etc. toutes sur le même modèle

void do_bge(struct machine *mach, uint32_t insn)
{
    int rs1, rs2, imm;
    B_type(insn, &rs1, &rs2, &imm);
    printf(":: bge\n");

    if(mach->regs[rs1] >= mach->regs[rs2])
        mach->PC += imm;
    else
        mach->PC += 4;
}

void do_jal(struct machine *mach, uint32_t insn)
{
    int rd, imm;
    J_type(insn, &rd, &imm);
    printf(":: jal\n");

    if(rd != 0)
        mach->regs[rd] = mach->PC + 4;
    mach->PC += imm;
}


void execute_instruction(struct machine *mach, uint32_t insn)
{
    if((insn & 0x0000707f) == 0x00005063) /* bge */
        do_bge(mach, insn);
    else if((insn & 0x0000007f) == 0x0000006f) /* jal */
        do_jal(mach, insn);
    else {
        fprintf(stderr, "error: invalid instruction %08x at PC=%08x\n",
            insn, mach->PC);
        exit(1);
    }
}
