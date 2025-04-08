## **About the project**

- **Kernel from Scratch (KFS)** is a 10-part project developed by the 42 Network, focused on building a computer kernel from scratch, without any existing software, API, or such. The architecture `i386 (x86)` is mandatory.
- **Kfs-2** aims to implement a **Global Descriptor Table (GDT)**.  The **GDT** must be declared to the `BIOS` and be set at address `0x00000800`.

## Getting started

1. **Clone the repository:**

```bash
git clone git@github.com:LDuheron/kfs-2.git
```

1. **Build the docker image :**

The Dockerfile is building our own cross-compiler using the multistage technique to optimize the compilation process. The process can take around 20 minutes to build the Docker 
image. To build the Docker image, run:

```
make
```

# Global descriptor table

The **Global Descriptor Table (GDT)** is a data structure used by Intel processors to define characteristics of various memory areas, known as **segments**.

These segments contain crucial information, such as the **base address** (where the segment starts), the **limit** (the size of the segment), and **access rights** (permissions like read, write, or execute). This information helps the CPU manage and protect memory by enforcing access control on different areas.

Each segment in the GDT is represented by a **descriptor**. A descriptor is a data structure that holds all the relevant information for a segment, allowing the CPU to interpret and manage the memory region associated with it. Specifically, the descriptor includes details like the segment's base address, size, and the segment's access rights.

In our implementation, the structure of the segment descriptor is defined in the **gdt.h** file, as shown below:

```c
struct  gdt_segment_descriptor_struct {
	short   limit;
	short   base_1;
	char    base_2;
	char    access_byte;
	char    limit_2;
	char    flags; 
	char    base_3;
};
```

**The GDT is specific to x86 processors.**

While **64-bit processors** typically rely on **paging** for memory management, **i386 (x86)** processors combine both **paging and GDT** to handle memory. The GDT defines the segments, whereas paging enables more advanced memory management techniques like virtual memory. This hybrid approach allows the **i386 architecture** to efficiently manage and protect memory while providing flexibility in how memory is accessed and organized. The size of the GDT can vary depending on the number of segments defined and the specific design of the operating system.

## Resources

- OsDev Global descriptor table : https://wiki.osdev.org/Global_Descriptor_Table
- OsDEV GDT tutorial : https://wiki.osdev.org/GDT_Tutorial
- OsDev Paging : https://wiki.osdev.org/Paging
- OsDev Segmentation : https://wiki.osdev.org/Segmentation
- OsDev Segment selectors : https://wiki.osdev.org/Segment_Selector 
- OliveStem - x86 Operating systems - Implementing a GDT : https://youtu.be/jwulDRMQ53I?feature=shared