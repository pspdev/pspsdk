/*
 * PSP Software Development Kit - http://www.pspdev.org
 * -----------------------------------------------------------------------
 * Licensed under the BSD license, see LICENSE in PSPSDK root for details.
 *
 * gdb-stub.c - Simple remote GDB stub for the psp.
 *
 * Copyright (c) 2005 James Forshaw <tyranid@gmail.com>
 *
 * $Id: gdb-stub.c 1152 2005-10-16 20:37:00Z tyranid $
 */

/* Note: there is the odd small bit which comes from the gdb stubs/linux mips stub */
/* As far as I am aware they didn't have an explicit license on them so... */

#include <pspkernel.h>
#include <pspdebug.h>
#include <string.h>
#include <signal.h>

//#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINTF(fmt, ...) pspDebugScreenPrintf(fmt, ## __VA_ARGS__)
#else
#define DEBUG_PRINTF(fmt, ...)
#endif

/*
 * breakpoint and test functions
 */
void pspDebugBreakpoint(void);
void putDebugChar(char ch);
char getDebugChar(void);
int _gdbSupportLibWriteByte(char val, unsigned char *dest);
int _gdbSupportLibReadByte(unsigned char *address, unsigned char *dest);
//void _pspDebugExceptionResume(void);
void pspDebugResumeFromException(void);
void _gdbSupportLibFlushCaches(void);
extern u32 _pspDebugResumePatch;

extern int sceKernelSuspendIntr(void);
extern void sceKernelResumeIntr(int intr);

static void handle_exception(PspDebugRegBlock *regs);

#define MAX_BUF 2048

void _GdbExceptionHandler(void);
static PspDebugRegBlock *_GdbExceptRegs;
static int initialised = 0;
static char input[MAX_BUF];
static char output[MAX_BUF];
static const char hexchars[]="0123456789abcdef";
static char last_cmd = 0;
static int attached = 0;

/* Define a software breakpoint structure */
struct sw_breakpoint
{
	unsigned int addr;
	unsigned int oldinst;
	unsigned int active;
};

static struct sw_breakpoint g_stepbp[2];

/*
 * send the packet in buffer.
 */
static void putpacket(unsigned char *buffer)
{
	unsigned char checksum;
	int count;
	unsigned char ch;

	/*
	 * $<packet info>#<checksum>.
	 */

	do {
		putDebugChar('$');
		checksum = 0;
		count = 0;

		while ((ch = buffer[count]) != 0) {
			checksum += ch;
			count += 1;
			putDebugChar(ch);
		}

		putDebugChar('#');
		putDebugChar(hexchars[(checksum >> 4) & 0xf]);
		putDebugChar(hexchars[checksum & 0xf]);

		DEBUG_PRINTF("calculated checksum = %02X\n", checksum);
	}
	while ((getDebugChar() & 0x7f) != '+');
}

static char get_char(void)
{
	int ch;

	while((ch = pspDebugSioGetchar()) == -1);

	return ch;
}

/*
 * send the packet in buffer.
 */
static int stdout_handler(const char *data, int len)
{
	unsigned char checksum;
	int count;
	unsigned char ch;

	if(!attached)
	{
		return 0;
	}

	/*
	 * $<packet info>#<checksum>.
	 */

	do {
		pspDebugSioPutchar('$');
		pspDebugSioPutchar('O');
		
		checksum = 'O';
		count = 0;

		while(1)
		{
			if(count == len)
			{
				break;
			}

			ch = hexchars[(data[count] >> 4) & 0xF];
			pspDebugSioPutchar(ch);
			checksum += ch;
			ch = hexchars[data[count] & 0xF];
			pspDebugSioPutchar(ch);
			checksum += ch;
			count += 1;
		}

		pspDebugSioPutchar('#');
		pspDebugSioPutchar(hexchars[(checksum >> 4) & 0xf]);
		pspDebugSioPutchar(hexchars[checksum & 0xf]);
	}
	while ((get_char() & 0x7f) != '+');

	return count;
}

/*
 * Convert ch from a hex digit to an int
 */
static int hex(unsigned char ch)
{
	if (ch >= 'a' && ch <= 'f')
		return ch-'a'+10;
	if (ch >= '0' && ch <= '9')
		return ch-'0';
	if (ch >= 'A' && ch <= 'F')
		return ch-'A'+10;
	return -1;
}

/*
 * scan for the sequence $<data>#<checksum>
 */
static void getpacket(char *buffer)
{
	unsigned char checksum;
	unsigned char xmitcsum;
	int i;
	int count;
	unsigned char ch;

	do {
		/*
		 * wait around for the start character,
		 * ignore all other characters
		 */
		while ((ch = (getDebugChar() & 0x7f)) != '$') ;

		checksum = 0;
		xmitcsum = -1;
		count = 0;

		/*
		 * now, read until a # or end of buffer is found
		 */
		while (count < MAX_BUF) {
			ch = getDebugChar();
			if (ch == '#')
				break;
			checksum = checksum + ch;
			buffer[count] = ch;
			count = count + 1;
		}

		if (count >= MAX_BUF)
			continue;

		buffer[count] = 0;

		if (ch == '#') {
			xmitcsum = hex(getDebugChar() & 0x7f) << 4;
			xmitcsum |= hex(getDebugChar() & 0x7f);

			if (checksum != xmitcsum)
				putDebugChar('-');	/* failed checksum */
			else {
				putDebugChar('+'); /* successful transfer */

				/*
				 * if a sequence char is present,
				 * reply the sequence ID
				 */
				if (buffer[2] == ':') {
					putDebugChar(buffer[0]);
					putDebugChar(buffer[1]);

					/*
					 * remove sequence chars from buffer
					 */
					count = strlen(buffer);
					for (i=3; i <= count; i++)
						buffer[i-3] = buffer[i];
				}
			}
		}
	}
	while (checksum != xmitcsum);
}

static struct hard_trap_info {
	unsigned char tt;		/* Trap type code for MIPS R3xxx and R4xxx */
	unsigned char signo;		/* Signal that we map this trap into */
} hard_trap_info[] = {
	{ 6, SIGBUS },			/* instruction bus error */
	{ 7, SIGBUS },			/* data bus error */
	{ 9, SIGTRAP },			/* break */
	{ 10, SIGILL },			/* reserved instruction */
	{ 12, SIGFPE },			/* overflow */
	{ 13, SIGTRAP },		/* trap */
	{ 14, SIGSEGV },		/* virtual instruction cache coherency */
	{ 15, SIGFPE },			/* floating point exception */
	{ 23, SIGSEGV },		/* watch */
	{ 31, SIGSEGV },		/* virtual data cache coherency */
	{ 0, 0}				/* Must be last */
};

static int computeSignal(int tt)
{
	struct hard_trap_info *ht;

	for (ht = hard_trap_info; ht->tt && ht->signo; ht++)
		if (ht->tt == tt)
			return ht->signo;

	return SIGHUP;		/* default for things we don't know about */
}


static void _GdbTrapEntry(PspDebugRegBlock *regs)
{
	/* Get the current priority and increment by one ? */
	_GdbExceptRegs = regs;
	handle_exception(regs);

	/* Flush caches */
	_gdbSupportLibFlushCaches();

	pspDebugResumeFromException();
}

int _gdbSupportLibInit(void);

void pspDebugGdbStubInit(void)
{
	_gdbSupportLibInit();
	/* Read out any pending data */
	memset(g_stepbp, 0, 2 * sizeof(struct sw_breakpoint));
	pspDebugInstallStdoutHandler(stdout_handler);
	pspDebugInstallStderrHandler(stdout_handler);

	pspDebugInstallErrorHandler(_GdbTrapEntry);

	initialised = 1;
	attached = 1;
}

static char *mem2hex(unsigned char *mem, char *buf, int count)
{
	unsigned char ch;

	while (count-- > 0) {
		if (_gdbSupportLibReadByte(mem++, &ch) == 0)
		{
			return NULL;
		}

		*buf++ = hexchars[(ch >> 4) & 0xf];
		*buf++ = hexchars[ch & 0xf];
	}

	*buf = 0;

	return buf;
}

static char *hex2mem(char *buf, char *mem, int count, int binary)
{
	int i;
	unsigned char ch;

	for (i=0; i<count; i++)
	{
		if (binary) {
			ch = *buf++;
			if (ch == 0x7d)
				ch = 0x20 ^ *buf++;
		}
		else {
			ch = hex(*buf++) << 4;
			ch |= hex(*buf++);
		}
		if (_gdbSupportLibWriteByte(ch, (unsigned char *) mem++) == 0)
			return 0;
	}

	return mem;
}

static int hexToInt(char **ptr, unsigned int *intValue)
{
	int numChars = 0;
	int hexValue;

	*intValue = 0;

	while (**ptr) {
		hexValue = hex(**ptr);
		if (hexValue < 0)
			break;

		*intValue = (*intValue << 4) | hexValue;
		numChars ++;

		(*ptr)++;
	}

	return numChars;
}

#define SW_BREAK_INST	0x0000000d
/* Define some opcode stuff for the stepping function */
#define BEQ_OPCODE		0x4
#define BEQL_OPCODE		0x14
#define BGTZ_OPCODE 	0x7
#define BGTZL_OPCODE	0x17
#define BLEZ_OPCODE		0x6
#define BLEZL_OPCODE	0x16
#define BNE_OPCODE		0x5
#define BNEL_OPCODE		0x15

/* Reg Imm */
#define REGIMM_OPCODE 	0x1
#define BGEZ_OPCODE		0x1
#define BGEZAL_OPCODE	0x11
#define BGEZALL_OPCODE	0x13
#define BGEZL_OPCODE	0x3
#define BLTZ_OPCODE		0
#define BLTZAL_OPCODE	0x10
#define BLTZALL_OPCODE	0x12
#define BLTZL_OPCODE	0x2

#define J_OPCODE		0x2
#define JAL_OPCODE		0x3

/* Special opcode */
#define SPECIAL_OPCODE	0
#define JALR_OPCODE		0x9
#define JR_OPCODE		0x8

/* Cop Branches (all the same) */
#define COP0_OPCODE		0x10
#define COP1_OPCODE		0x11
#define COP2_OPCODE		0x12
#define BCXF_OPCODE		0x100
#define BCXFL_OPCODE	0x102
#define BCXT_OPCODE		0x101
#define BCXTL_OPCODE	0x103

/* Generic step command , if skip then will try to skip over jals */
static void step_generic(PspDebugRegBlock *regs, int skip)
{
	u32 opcode;
	u32 epc;
	u32 targetpc;
	int branch = 0;
	int cond   = 0;
	int link   = 0;

	epc = regs->epc;
	targetpc = epc + 4;

	opcode = _lw(epc);

	switch(opcode >> 26)
	{
		case BEQ_OPCODE:
		case BEQL_OPCODE:
		case BGTZ_OPCODE:
		case BGTZL_OPCODE:
		case BLEZ_OPCODE:
		case BLEZL_OPCODE: 
		case BNE_OPCODE:
		case BNEL_OPCODE:
						    {
							   short ofs;

							   ofs = (short) (opcode & 0xffff);
							   cond = 1;
							   branch = 1;
							   targetpc += ofs * 4;
						   }
						   break;
		case REGIMM_OPCODE: {
								switch((opcode >> 16) & 0x1f)
								{
									case BGEZ_OPCODE:
									case BGEZAL_OPCODE:
									case BGEZALL_OPCODE:	
									case BGEZL_OPCODE:
									case BLTZ_OPCODE:
									case BLTZAL_OPCODE:
									case BLTZALL_OPCODE:
									case BLTZL_OPCODE: {
														   short ofs;

														   ofs = (short) (opcode & 0xffff);
														   cond = 1;
														   branch = 1;
														   targetpc += ofs * 4;
													   }
													   break;
								}
						    }
							break;
		case JAL_OPCODE:	link = 1;
		case J_OPCODE: {
							 u32 ofs;
							 
							 ofs = opcode & 0x3ffffff;
							 targetpc = (ofs << 2) | (targetpc & 0xf0000000);
							 branch = 1;
							 cond = 0;
						 }
						 break;
		case SPECIAL_OPCODE:
						 {
							 switch(opcode & 0x3f)
							 {
								 case JALR_OPCODE: link = 1;
								 case JR_OPCODE:
												 {
													 u32 rs;

													 rs = (opcode >> 21) & 0x1f;
													 targetpc = regs->r[rs];
													 branch = 1;
													 cond = 0;
												 }
												 break;
							 };
						 }
						 break;
		case COP0_OPCODE:
		case COP1_OPCODE:
		case COP2_OPCODE:
						 {
							 switch((opcode >> 16) & 0x3ff)
							 {
								 case BCXF_OPCODE:
								 case BCXFL_OPCODE:
								 case BCXT_OPCODE:
								 case BCXTL_OPCODE:
									 				{
														short ofs;

														ofs = (short) (opcode & 0xffff);
														cond = 1;
														branch = 1;
														targetpc += ofs * 4;
													}
													break;
							 };
						 }
						 break;
	};

	if(link && skip)
	{
		g_stepbp[1].addr = epc + 8;
		g_stepbp[1].oldinst = _lw(epc + 8);
		g_stepbp[1].active = 1;
		_sw(SW_BREAK_INST, epc + 8);
	}
	else if(branch)
	{
		g_stepbp[0].addr = targetpc;
		g_stepbp[0].oldinst = _lw(targetpc);
		g_stepbp[0].active = 1;
		_sw(SW_BREAK_INST, targetpc);
			
		if((cond) && (targetpc != (epc + 8)))
		{
			g_stepbp[1].addr = epc + 8;
			g_stepbp[1].oldinst = _lw(epc + 8);
			g_stepbp[1].active = 1;
			_sw(SW_BREAK_INST, epc + 8);
		}

	}
	else
	{
		g_stepbp[0].addr = targetpc;
		g_stepbp[0].active = 1;
		g_stepbp[0].oldinst = _lw(targetpc);
		_sw(SW_BREAK_INST, targetpc);
	}
}

void build_trap_cmd(int sigval, PspDebugRegBlock *regs)
{
	char *ptr;
	/*
	 * reply to host that an exception has occurred
	 */
	ptr = output;
	*ptr++ = 'T';
	*ptr++ = hexchars[(sigval >> 4) & 0xf];
	*ptr++ = hexchars[sigval & 0xf];

	/*
	 * Send Error PC
	 */
	*ptr++ = hexchars[37 >> 4];
	*ptr++ = hexchars[37 & 0xf];
	*ptr++ = ':';
	ptr = mem2hex((unsigned char *) &regs->epc, ptr, sizeof(u32));
	*ptr++ = ';';

	/*
	 * Send frame pointer
	 */
	*ptr++ = hexchars[30 >> 4];
	*ptr++ = hexchars[30 & 0xf];
	*ptr++ = ':';
	ptr = mem2hex((unsigned char *)&regs->r[30], ptr, sizeof(u32));
	*ptr++ = ';';

	/*
	 * Send stack pointer
	 */
	*ptr++ = hexchars[29 >> 4];
	*ptr++ = hexchars[29 & 0xf];
	*ptr++ = ':';
	ptr = mem2hex((unsigned char *)&regs->r[29], ptr, sizeof(u32));
	*ptr++ = ';';

	*ptr++ = 0;
}

static void handle_query(char *str)
{
	static SceUID threads[100];
	static int thread_count = 0;
	static int thread_loc = 0;

	switch(str[0])
	{
		case 'f': 
				if(strncmp(str, "fThreadInfo", strlen("fThreadInfo")) == 0)
				{
					thread_count = sceKernelGetThreadmanIdList(SCE_KERNEL_TMID_Thread, threads, 100, &thread_count);
					if(thread_count > 0)
					{
						thread_loc = 0;
						output[0] = 'm';
						mem2hex((unsigned char *) &threads[thread_loc], &output[1], 4);
						output[9] = 0;
						thread_loc++;
					}
				}
				break;

		case 's':
				if(strncmp(str, "sThreadInfo", strlen("sThreadInfo")) == 0)
				{
					if(thread_loc < thread_count)
					{
						output[0] = 'm';
						mem2hex((unsigned char *) &threads[thread_loc], &output[1], 4);
						output[9] = 0;
						thread_loc++;
					}
					else
					{
						strcpy(output, "l");
					}
				}
				break;
		case 'P':
				break;
	};
}

static void handle_exception (PspDebugRegBlock *regs)
{
	int trap;
	int sigval;
	unsigned int addr;
	unsigned int length;
	char *ptr;
	int bflag = 0;

	trap = (regs->cause & 0x7c) >> 2;
	sigval = computeSignal(trap);

	if(sigval == SIGHUP)
	{
		DEBUG_PRINTF("Trap %d\n", trap);
	}

	/* We stopped in breakpoint, so set epc to our ra */
	if((regs->epc == (u32) pspDebugBreakpoint) && (trap == 9))
	{
		regs->epc = regs->r[31];
	}

	/* If step breakpoints set then put back the old values */
	if(g_stepbp[0].active)
	{
		_sw(g_stepbp[0].oldinst, g_stepbp[0].addr);
		g_stepbp[0].active = 0;
	}

	if(g_stepbp[1].active)
	{
		_sw(g_stepbp[1].oldinst, g_stepbp[1].addr);
		g_stepbp[1].active = 0;
	}

	if(last_cmd != 0)
	{
		build_trap_cmd(sigval, regs);
		putpacket((unsigned char *) output);
	}

	while(1)
	{
		getpacket(input);
		DEBUG_PRINTF("Received packet '%s'\n", input);

		output[0] = 0;

		switch (input[0])
		{
		case '?':
			if(last_cmd == 0)
			{
				build_trap_cmd(sigval, regs);
			}
			else
			{
				output[0] = 'S';
				output[1] = hexchars[sigval >> 4];
				output[2] = hexchars[sigval & 0xf];
				output[3] = 0;
			}
			break;

		case 'c':
			ptr = &input[1];
			if (hexToInt(&ptr, &addr))
			{
				regs->epc = addr;
			}
	  
			goto restart;
			break;

		case 'D':
			putpacket((unsigned char *) output);
			attached = 0;
			goto restart;
			break;

		case 'g':
			ptr = output;
			ptr = (char*) mem2hex((unsigned char *)&regs->r[0], ptr, 32*sizeof(u32)); /* r0...r31 */
			ptr = (char*) mem2hex((unsigned char *)&regs->status, ptr, 6*sizeof(u32)); /* cp0 */
			ptr = (char*) mem2hex((unsigned char *)&regs->fpr[0], ptr, 32*sizeof(u32)); /* f0...31 */
			ptr = (char*) mem2hex((unsigned char *)&regs->fsr, ptr, 2*sizeof(u32)); /* cp1 */
			ptr = (char*) mem2hex((unsigned char *)&regs->frame_ptr, ptr, 2*sizeof(u32)); /* frp */
			ptr = (char*) mem2hex((unsigned char *)&regs->index, ptr, 16*sizeof(u32)); /* cp0 */
			break;

		case 'G':
			ptr = &input[1];
			hex2mem(ptr, (char *)&regs->r[0], 32*sizeof(unsigned int), 0);
			ptr += 32*(2*sizeof(unsigned int));
			hex2mem(ptr, (char *)&regs->status, 6*sizeof(unsigned int), 0);
			ptr += 6*(2*sizeof(unsigned int));
			hex2mem(ptr, (char *)&regs->fpr[0], 32*sizeof(unsigned int), 0);
			ptr += 32*(2*sizeof(unsigned int));
			hex2mem(ptr, (char *)&regs->fsr, 2*sizeof(unsigned int), 0);
			ptr += 2*(2*sizeof(unsigned int));
			hex2mem(ptr, (char *)&regs->frame_ptr, 2*sizeof(unsigned int), 0);
			ptr += 2*(2*sizeof(unsigned int));
			hex2mem(ptr, (char *)&regs->index, 16*sizeof(unsigned int), 0);
			strcpy(output,"OK");
			break;

		/*
		 * mAA..AA,LLLL  Read LLLL bytes at address AA..AA
		 */
		case 'm':
			ptr = &input[1];

			if (hexToInt(&ptr, &addr)
				&& *ptr++ == ','
				&& hexToInt(&ptr, &length)) {
				if (mem2hex((unsigned char *)addr, output, length))
					break;
				strcpy (output, "E03");
			} else
				strcpy(output,"E01");
			break;

		/*
		 * XAA..AA,LLLL: Write LLLL escaped binary bytes at address AA.AA
		 */
		case 'X':
			bflag = 1;
			/* fall through */

		/*
		 * MAA..AA,LLLL: Write LLLL bytes at address AA.AA return OK
		 */
		case 'M':
			ptr = &input[1];

			if (hexToInt(&ptr, &addr)
				&& *ptr++ == ','
				&& hexToInt(&ptr, &length)
				&& *ptr++ == ':') {
				if (hex2mem(ptr, (char *)addr, length, bflag))
					strcpy(output, "OK");
				else
					strcpy(output, "E03");
			}
			else
				strcpy(output, "E02");
			bflag = 0;
			break;

		case 's': 	ptr = &input[1];
					if (hexToInt(&ptr, &addr))
					{
						regs->epc = addr;
					}
	  
					step_generic(regs, 0);
					goto restart;
					break;

		case 'q': handle_query(&input[1]);
				  break;

		/*
		 * kill the program; let us try to restart the machine
		 * Reset the whole machine.
		 */
		case 'k':
		case 'r':	sceKernelExitGame();
			break;

		default:
			break;
		}
		/*
		 * reply to the request
		 */

		putpacket((unsigned char *) output);

	} /* while */

restart:
		last_cmd = input[0];
	return ;

}

/* Define the breakpoint function */
asm  (
		".global pspDebugBreakpoint\n"
		".set noreorder\n"
		"pspDebugBreakpoint:\tbreak\n"
		"jr    $31\n"
		"nop\n"
		);
