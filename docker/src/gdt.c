#include "../inc/stdint.h"
#include "../inc/stddef.h"
#include "../inc/gdt.h"

struct gdt_segment_descriptor_struct gdt_entries[7];
struct gdt_ptr_struct gdt_ptr;

static void setGdtEntries(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt_entries[index].limit_1 = (limit & 0xFFFF);

    gdt_entries[index].base_1 = (base & 0xFFFF);
    gdt_entries[index].base_2 = (base >> 16) & 0xFF;

    gdt_entries[index].access_byte = access;

    gdt_entries[index].flags = (limit >> 16) & 0x0F;
    gdt_entries[index].flags |= (granularity & 0xF0);

    gdt_entries[index].base_3 = (base >> 24) & 0xFF;
}

static void initGdt() {
    gdt_ptr.limit = (sizeof(gdt_segment_descriptor_struct) * 7) - 1;
    gdt_ptr.base = &gdt_entries;

    setGdtEntries(0, 0, 0, 0, 0);   // Null descriptor

    setGdtEntries(1, 0, LIMIT, 0x9A, FLAG);   // Kernel Mode Code Segment
    setGdtEntries(2, 0, LIMIT, 0x92, FLAG);   // Kernel Mode Data Segment
   
    // setGdtEntries(3, 0, LIMIT, ?? , FLAG);   // Kernel Mode Stack Segment

    setGdtEntries(4, 0, LIMIT, 0xFA, FLAG);  // User Mode Code Segment
    setGdtEntries(5, 0, LIMIT, 0xF2, FLAG);  // User Mode Data Segment
    
    // setGdtEntries(6, 0, LIMIT, ?? , FLAG);  // User Mode Stack Segment

}

int main(void)
{
    initGdt();
    return (SUCCESS);
}