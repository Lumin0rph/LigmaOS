#include "irq.h"
#include "idt.h"
#include "isr.h"
#include <architecture/x86/chips/PIC_8259A.h>
#include <architecture/x86/io.h>
#include <stdio.h>

ISR IRQ_OVERRIDES[16] = { nullptr };

const char* IRQ_MESSAGES[16] = {
	"System timer",
	"Keyboard controller",
	"Serial port COM 2",
	"Serial port COM 1",
	"Line print terminal 2",
	"Floppy controller",
	"Line print terminal 1",
	"RTC timer",
	"Mouse controller",
	"Math co-processor",
	"ATA channel 1",
	"ATA channel 2",
};

void IRQ_dispatcher(struct ISR_parameters const *p)
{
	u8 const irq = p->interrupt - IDT_REPROGRAMABLE_INTERRUPT_START_INDEX;

	if (IRQ_OVERRIDES[irq] != nullptr) {
		(IRQ_OVERRIDES[irq])(p);
		PIC_8259A_eoi(irq);
		return;
	}

	u16 const pending = PIC_8259A_pending();
	x86_io_wait();
	u16 const processing = PIC_8259A_processing();
	printf("Unhandeled IRQ %d: %s\n\tpending irqs: %d\n\tprocessing irqs: %d\n",
	  irq, IRQ_MESSAGES[irq], pending, processing);
}

void IRQ_initialize(void)
{
	PIC_8259A_initialize();

	for (u8 i = IDT_REPROGRAMABLE_INTERRUPT_START_INDEX;
	i < IDT_REPROGRAMABLE_INTERRUPT_START_INDEX + 16; ++i) {
		ISR_OVERRIDES[i] = IRQ_dispatcher;
	}

	IRQ_enable();
}
