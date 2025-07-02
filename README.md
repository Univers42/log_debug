# Benefits of this approach
No global variables
- all lookup table are encapsulated in the singleton
- Thread safe initialization (static local variable)
- clean namespace without pollution

# Efficient memory Usage
- single instance of lookup tables shared
- Easy to extend with new tables 
- no repeated initlaization overhead

# Maintainable design
- all realated data grouped in one structure
- Easy to extend with new table types
- Clear ownership and lifetime management


## Extension Example

### Adding a new format
``` C
// In get_parser_tables() initialization  
tables.char_class_table['='] |= CHAR_FLAG;  // Center align
tables.flag_table['='] = flag_center_align;
```

### Adding custom formatting flags:
``` C
// In get_parser_tables() initialization  
tables.char_class_table['='] |= CHAR_FLAG;  // Center align
tables.flag_table['='] = flag_center_align;
```

This desing maintains all the performance benefits of the pointer table approach while ensuring clean, maintainable code
without global state pollution. The single patter thread safety and efficient ressource usage