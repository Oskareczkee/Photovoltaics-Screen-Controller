const uint32_t logo_width = 54;
const uint32_t logo_height = 34;
const uint8_t logo_data[(54*34)/2] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x0B, 0x30, 0x33, 0x33, 0x44, 0x55, 0x57, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x3B, 0x22, 0x33, 0x33, 0x44, 0x55, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x22, 0x33, 0x43, 0x44, 0x55, 0x66, 0x77, 0x67, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x22, 0x33, 0x44, 0x54, 0x55, 0x66, 0x76, 0x66, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xCB, 0x32, 0x43, 0x44, 0x54, 0x65, 0x66, 0x67, 0x66, 0x06, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x21, 0x32, 0x43, 0x44, 0x55, 0x65, 0x76, 0x67, 0x56, 0x55, 0x00, 0x00, 0x00, 
	0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x26, 0x31, 0x43, 0x54, 0x55, 0x66, 0x76, 0x66, 0x56, 0x55, 0x34, 0x33, 0x23, 
	0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x89, 0x56, 0x66, 0x76, 0x66, 0x54, 0x54, 0x65, 0x66, 0x67, 0x66, 0x56, 0x45, 0x34, 0x33, 0x23, 
	0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x9B, 0x46, 0x33, 0x33, 0x54, 0x65, 0x66, 0x67, 0x66, 0x55, 0x47, 0x65, 0x76, 0x66, 0x66, 0x55, 0x45, 0x44, 0x33, 0x23, 
	0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x3B, 0x32, 0x43, 0x44, 0x55, 0x65, 0x76, 0x67, 0x56, 0x45, 0x44, 0x33, 0x71, 0x66, 0x56, 0x55, 0x44, 0x34, 0x23, 0x23, 
	0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAB, 0x33, 0x43, 0x54, 0x55, 0x66, 0x66, 0x66, 0x55, 0x45, 0x44, 0x33, 0x42, 0x66, 0x55, 0x55, 0x44, 0x33, 0x23, 0x42, 
	0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x33, 0x44, 0x54, 0x55, 0x76, 0x56, 0x55, 0x66, 0x66, 0x66, 0x35, 0x22, 0x65, 0x55, 0x44, 0x34, 0x23, 0x22, 0x32, 
	0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x9B, 0x56, 0x54, 0x55, 0x55, 0x55, 0x55, 0x66, 0x66, 0x77, 0x67, 0x35, 0x36, 0x55, 0x44, 0x33, 0x33, 0x33, 0x00, 
	0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x5E, 0x55, 0x55, 0x55, 0x55, 0x66, 0x66, 0x76, 0x66, 0x56, 0x55, 0x55, 0x44, 0x33, 0x33, 0x03, 0x00, 
	0x00, 0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x4B, 0x65, 0x55, 0x65, 0x76, 0x77, 0x00, 0x60, 0x65, 0x55, 0x55, 0x45, 0x45, 0x05, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x8B, 0x55, 0x55, 0x65, 0x66, 0x76, 0x67, 0x66, 0x55, 0x55, 0x55, 0x44, 0x44, 0x44, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x5B, 0x55, 0x55, 0x66, 0x66, 0x76, 0x66, 0x66, 0x55, 0x55, 0x55, 0x44, 0x44, 0x44, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x5B, 0x55, 0xA5, 0x66, 0x76, 0x67, 0x66, 0x56, 0x55, 0x55, 0x44, 0x43, 0x44, 0x44, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xB0, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x5B, 0x65, 0x66, 0x66, 0x67, 0x66, 0x66, 0x56, 0x55, 0x55, 0x44, 0x44, 0x34, 0x43, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x5B, 0x65, 0x66, 0x66, 0x66, 0x66, 0x66, 0x56, 0x55, 0x55, 0x44, 0x44, 0x34, 0x03, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x8B, 0x65, 0x66, 0x76, 0x66, 0x66, 0x66, 0x00, 0x00, 0x40, 0x44, 0x44, 0x44, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x66, 0x66, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xBB, 0xBB, 0xBB, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x77, 0x00, 0x00, 0x50, 0x55, 0x55, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xBB, 0xBB, 0xBB, 0x0B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x77, 0x77, 0x00, 0x00, 0x55, 0x55, 0x65, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAB, 0x66, 0x66, 0x76, 0x77, 0x77, 0x67, 0x66, 0x56, 0x55, 0x55, 0x55, 0x44, 0x44, 0x44, 0x34, 0x33, 0x33, 0x33, 0x03, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xAB, 0x66, 0x66, 0x76, 0x77, 0x66, 0x66, 0x66, 0x56, 0x55, 0x55, 0x45, 0x44, 0x44, 0x44, 0x34, 0x33, 0x33, 0x33, 0x03, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x66, 0x76, 0x77, 0x67, 0x66, 0x66, 0x66, 0x55, 0x55, 0x55, 0x45, 0x44, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x03, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x66, 0x77, 0x67, 0x66, 0x66, 0x66, 0x55, 0x55, 0x55, 0x55, 0x44, 0x44, 0x44, 0x34, 0x33, 0x33, 0x33, 0x22, 0x02, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x77, 0x67, 0x66, 0x66, 0x66, 0x55, 0x55, 0x55, 0x55, 0x44, 0x44, 0x44, 0x34, 0x33, 0x33, 0x33, 0x23, 0x22, 0x02, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x77, 0x67, 0x66, 0x66, 0x56, 0x55, 0x55, 0x55, 0x45, 0x44, 0x44, 0x34, 0x33, 0x33, 0x33, 0x23, 0x22, 0x22, 0x02, 
	0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0x77, 0x67, 0x66, 0x66, 0x66, 0x55, 0x55, 0x55, 0x45, 0x44, 0x44, 0x33, 0x33, 0x33, 0x33, 0x33, 0x22, 0x22, 0x02, 
	};
