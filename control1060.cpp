#include <iostream>
#include "hidapi.hpp"

int main(int argc, char* argv[])
{
	HIDAPIWrapper device;
	device.Open(0x08f2, 0x6811, NULL);

	//Reset? command. The first byte is the report number (0x0).
	unsigned char reset_enable_keyb_cmd[] = {0x08, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	device.SendFeatureReport(reset_enable_keyb_cmd, sizeof(reset_enable_keyb_cmd));


	//Reset? command. The first byte is the report number (0x0).
	unsigned char full_screen_map_mode1_rst_cmd[] = {0x08, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	unsigned char full_screen_map_mode1_full_cmd[] = {0x08, 0x01, 0x00, 0xff, 0xf0, 0x00, 0xff, 0xf0};
	device.SendFeatureReport(full_screen_map_mode1_rst_cmd, sizeof(full_screen_map_mode1_rst_cmd));
	device.SendFeatureReport(full_screen_map_mode1_full_cmd, sizeof(full_screen_map_mode1_full_cmd));

	return 0;

}