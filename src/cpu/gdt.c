#include "../src/header/cpu/gdt.h"

/**
 * global_descriptor_table, predefined GDT.
 * Initial SegmentDescriptor already set properly according to Intel Manual & OSDev.
 * Table entry : [{Null Descriptor}, {Kernel Code}, {Kernel Data (variable, etc)}, ...].
 */
struct GlobalDescriptorTable global_descriptor_table = {
    .table = {
        {
            // Null Descriptor
            .segment_low = 0,
            .base_low = 0,
            .base_mid = 0,
            .type_bit = 0,
            .non_system = 0,
            .previlege_bit = 0,
            .present_bit = 0,
            .segment_limit = 0,
            .available_bit = 0,
            .l_bit = 0,
            .default_bit = 0,
            .granularity_bit = 0,
            .base_high = 0,

        },
        {
            // Kernel Code
            .segment_low = 0xFFFF,
            .base_low = 0x000,

            .base_mid = 0x00,
            .type_bit = 0xA,
            .non_system = 1,
            .previlege_bit = 0,
            .present_bit = 1,
            .segment_limit = 0xF,
            .available_bit = 0,
            .l_bit = 0,
            .default_bit = 1,
            .granularity_bit = 1,
            .base_high = 0x00,
        },
        {
            // Kernel Data
            .segment_low = 0xFFFF,
            .base_low = 0,
            .base_mid = 0,
            .type_bit = 0x2,
            .non_system = 1,
            .previlege_bit = 0,
            .present_bit = 1,
            .segment_limit = 0xF,
            .available_bit = 0,
            .l_bit = 0,
            .default_bit = 1,
            .granularity_bit = 1,
            .base_high = 0x00,
        }
    }
};

/**
 * _gdt_gdtr, predefined system GDTR. 
 * GDT pointed by this variable is already set to point global_descriptor_table above.
 * From: https://wiki.osdev.org/Global_Descriptor_Table, GDTR.size is GDT size minus 1.
 */
struct GDTR _gdt_gdtr = {
    // TODO : Implement, this GDTR will point to global_descriptor_table. 
    //        Use sizeof operator
    .size = sizeof(global_descriptor_table) - 1,
    .address = &global_descriptor_table
};

