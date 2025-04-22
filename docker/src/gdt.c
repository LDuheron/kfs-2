#include "../inc/stdint.h"
#include "../inc/stddef.h"
#include "../inc/gdt.h"

extern void writeGdtToRegisters(struct gdt_ptr_struct*);

struct gdt_segment_descriptor_struct gdt_entries[7];
struct gdt_ptr_struct gdt_ptr;

static void setGdtEntries(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt_entries[index].limit_1 = LOWER_16_BITS(limit);

    gdt_entries[index].base_1 = LOWER_16_BITS(base);
    gdt_entries[index].base_2 = BITS_16_TO_24(base);

    gdt_entries[index].access_byte = access;

    gdt_entries[index].flags = BITS_16_TO_20(limit);
    gdt_entries[index].flags |= ISOLATE_BITS_4_TO_8(granularity);

    gdt_entries[index].base_3 = BITS_24_TO_32(base);
}

static void initGdt() {
    gdt_ptr.limit = (sizeof(struct gdt_segment_descriptor_struct) * 7) - 1;
    gdt_ptr.base = (unsigned int) &gdt_entries;

    setGdtEntries(0, 0, 0, 0, 0);
    setGdtEntries(1, 0, LIMIT, KERNEL_MODE | CODE_MODE, FLAG);
    setGdtEntries(2, 0, LIMIT, KERNEL_MODE | DATA_MODE, FLAG);
    setGdtEntries(3, 0, LIMIT, KERNEL_MODE | DATA_MODE, FLAG); // Kernel Mode Stack Segment

    setGdtEntries(4, 0, LIMIT, USER_MODE | CODE_MODE, FLAG);
    setGdtEntries(5, 0, LIMIT, USER_MODE | DATA_MODE, FLAG);
    setGdtEntries(6, 0, LIMIT, USER_MODE | DATA_MODE, FLAG); // User Mode Stack Segment

    writeGdtToRegisters(&gdt_ptr);
}
