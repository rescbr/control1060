#pragma once
#include <memory>
#include <string>
#include <stdexcept>
#include <hidapi/hidapi.h>

class HIDAPIWrapper
{
private:
    static void _hid_init_wrapper_impl()
    {
        int res = hid_init();
        if (res != 0)
        {
            throw std::runtime_error("error initializing HIDAPI");
        }
    };
    static void _hid_exit_wrapper_impl(void (*)())
    {
        int res = hid_exit();
        if (res != 0)
        {
            throw std::runtime_error("error closing HIDAPI");
        }
    };
    static const inline auto _hid_init_wrapper = std::shared_ptr<void()>(_hid_init_wrapper_impl, _hid_exit_wrapper_impl);

    std::shared_ptr<hid_device> _handle;
    std::string GetError()
    {
        const wchar_t *error_message_wcs = hid_error(_handle.get());
        std::wstring error_msg_wstr(error_message_wcs);
        std::string error_msg_str(error_msg_wstr.begin(), error_msg_wstr.end());

        return error_msg_str;
    }

public:
    HIDAPIWrapper()
    {
        (*_hid_init_wrapper)();
    };
    void Open(unsigned short vendor_id, unsigned short product_id, const wchar_t *serial_number)
    {
        _handle = std::shared_ptr<hid_device>(hid_open(vendor_id, product_id, serial_number), hid_close);
 
        if (_handle == nullptr)
        {
            throw std::runtime_error(GetError());
        }
    };
    int SendFeatureReport(const unsigned char *data, size_t length)
    {
        int res = hid_send_feature_report(_handle.get(), data, length);
        if (res == -1)
        {
            throw std::runtime_error(GetError());
        }
        return res;
    };
};