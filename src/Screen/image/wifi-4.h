const uint32_t wifi4_width = 44;
const uint32_t wifi4_height = 34;
const uint8_t wifi4_data[(44*34)/2] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x42, 0x75, 0x87, 0x78, 0x57, 0x24, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x52, 0xA8, 0xCB, 0xCC, 0xCC, 0xCC, 0xCC, 0xBC, 0x8A, 0x25, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x10, 0x84, 0xCB, 0xCD, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xBC, 0x59, 0x01, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x10, 0xA6, 0xCC, 0xCC, 0xCC, 0xDC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x6A, 0x01, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xA5, 0xCC, 0xCC, 0xCC, 0xBC, 0x8A, 0x56, 0x44, 0x44, 0x65, 0x98, 0xCB, 0xCC, 0xCC, 0xCC, 0x5A, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x82, 0xCC, 0xCC, 0xCC, 0x8B, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0xB8, 0xCC, 0xCC, 0xCC, 0x29, 0x00, 0x00, 
	0x00, 0x50, 0xCB, 0xCC, 0xCC, 0x5A, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x95, 0xCC, 0xCC, 0xBC, 0x05, 0x00, 
	0x00, 0xC6, 0xCC, 0xCC, 0x5A, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xA5, 0xCC, 0xCC, 0x7C, 0x01, 
	0x71, 0xCC, 0xCC, 0x6C, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xB6, 0xCC, 0xCC, 0x18, 
	0xC8, 0xCC, 0xAC, 0x04, 0x00, 0x00, 0x00, 0x00, 0x21, 0x64, 0x77, 0x77, 0x46, 0x12, 0x00, 0x00, 0x00, 0x00, 0x30, 0xCA, 0xCC, 0x9C, 
	0xCC, 0xCC, 0x29, 0x00, 0x00, 0x00, 0x10, 0x74, 0xCA, 0xCC, 0xDD, 0xDD, 0xCC, 0xAC, 0x47, 0x01, 0x00, 0x00, 0x00, 0x82, 0xCC, 0xCC, 
	0xC9, 0x8C, 0x01, 0x00, 0x00, 0x10, 0xA5, 0xDC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCD, 0x5A, 0x01, 0x00, 0x00, 0x10, 0xC8, 0xAC, 
	0x51, 0x15, 0x00, 0x00, 0x00, 0xA4, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x4A, 0x00, 0x00, 0x00, 0x41, 0x25, 
	0x00, 0x00, 0x00, 0x00, 0x71, 0xCC, 0xCC, 0xCC, 0x9B, 0x57, 0x34, 0x43, 0x75, 0xB9, 0xCC, 0xCC, 0xCC, 0x17, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x20, 0xC9, 0xCC, 0xCC, 0x6A, 0x02, 0x00, 0x00, 0x00, 0x00, 0x20, 0xA5, 0xCC, 0xCC, 0x9C, 0x02, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xA2, 0xCC, 0xCC, 0x5A, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0xA5, 0xCC, 0xCC, 0x2A, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xD6, 0xCC, 0x8C, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xC8, 0xCC, 0x7D, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xD6, 0xCD, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xDC, 0x6D, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x71, 0x59, 0x00, 0x00, 0x00, 0x00, 0x53, 0x87, 0x78, 0x35, 0x01, 0x00, 0x00, 0x00, 0x95, 0x17, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x95, 0xCC, 0xCC, 0xDD, 0xCC, 0x59, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x93, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0xCB, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xBC, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xB2, 0xCC, 0xCC, 0x6A, 0x34, 0x43, 0xA6, 0xCC, 0xCC, 0x2B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC3, 0xCC, 0x6B, 0x01, 0x00, 0x00, 0x10, 0xB6, 0xCC, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xAC, 0x04, 0x00, 0x00, 0x00, 0x00, 0x30, 0xCA, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xA7, 0x8A, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x91, 0xCD, 0xDC, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC4, 0xCC, 0xCC, 0x5C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC6, 0xCC, 0xCC, 0x7D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC4, 0xCC, 0xCC, 0x5C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x91, 0xCC, 0xCC, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xC8, 0x9C, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	};