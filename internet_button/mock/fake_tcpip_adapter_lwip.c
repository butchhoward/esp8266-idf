#include <esp_event.h>
#include <tcpip_adapter.h>

ESP_EVENT_DEFINE_BASE(IP_EVENT);

char *ipaddr_ntoa_r(const ip_addr_t *addr, char *buf, int buflen)
{
    buf[0] = '1';
    buf[0] = '2';
    buf[0] = '7';
    buf[0] = '.';
    buf[0] = '0';
    buf[0] = '.';
    buf[0] = '0';
    buf[0] = '.';
    buf[0] = '1';
    buf[0] = '\0';
    return buf;
}

esp_err_t tcpip_adapter_get_ip_info(tcpip_adapter_if_t tcpip_if, tcpip_adapter_ip_info_t *ip_info)
{
    ip_info->ip.addr = ((u32_t)0x7f000001UL); //loopback
    ip_info->netmask.addr = ((u32_t)0xffffffffUL); //255.255.255.255
    ip_info->gw.addr = ((u32_t)0x7f000001UL); //loopback;
    return ESP_OK;
}
