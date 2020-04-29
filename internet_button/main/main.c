/* Internet Button
*/
#include "button_server.h"
#include "sdkconfig.h"


#ifndef CONFIG_BUTTON_WIFI_PASSWORD
#error "WiFi PASSWORD must be configured in menuconfig before flashing."
#endif 

void app_main()
{
    start_the_server();
}
