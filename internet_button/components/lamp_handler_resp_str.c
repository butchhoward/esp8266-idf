#include "internal/lamp_handler_priv.h"
#include <stdio.h>
#include "sdkconfig.h"

#define IPSTR_FORMAT "%s"
#define STATUS_FORMAT "%s"
#define CLASSNAME_FORMAT "%s"

static const char* HELLO_BACK_AT_YA=
"<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>" CONFIG_BUTTON_MDNS_INSTANCE "</title>"
        "<style>"
            "html, body {"
                "margin: 0;"
                "padding: 0;"
                "height: 100%%;"
            "}"
            "body {"
                "display: flex; /* or css grid for more intricate layouts */"
                "flex-direction: column;"
                "text-align: center;"
            "}"
            "#pagewrap {"
                "background-color: black;"
                "flex-grow: 1;"
                "overflow-y: scroll;"
                "display: inline-block;"
            "}"
            ".LAMPBUTTON {"
                "background-color: LightGreen;"
                "border: 2px solid black;"
                "color: black;"
                "padding: 5px 10px;"
                "text-align: center;"
                "display: inline-block;"
                "font-size: 20px; "
                "margin: 10px 30px; "
                "cursor: pointer; "
                "text-decoration:none;"
                "width:80vw;"
                "height:40vh;"
            "}"
            ".OFF_RED {"
                "background-color: LightCoral;"
            "}"
            ".ON_RED {"
                "background-color: red;"
            "}"
            ".OFF_GREEN {"
                "background-color: green;"
            "}"
            ".ON_GREEN {"
                "background-color: LightGreen;"
            "}"
        "</style>"
    "</head>"
    "<body>"
        "<h1>" CONFIG_BUTTON_MDNS_INSTANCE "</h1>"
        "<div id=pagewrap>"
            "<div>"
            "<form action=\"/lamp/on\" method=\"post\">"
            "<input class=\"LAMPBUTTON " CLASSNAME_FORMAT "\" type=\"submit\" value=\"on\">"
            "</form>"
            "</div>"
            "<div>"
            "<form action=\"/lamp/off\" method=\"post\">"
            "<input class=\"LAMPBUTTON " CLASSNAME_FORMAT "\" type=\"submit\" value=\"off\">"
            "</form>"
            "</div>"
        "</div>"
        "<div><p>Currently: " STATUS_FORMAT "</p></div>"
    "</body>"
"</html>";



char* lamp_handler_html_response(const lamp_user_ctx_t* lamp_ctx)
{
    char* resp_str = NULL;
    int ret = asprintf(&resp_str, HELLO_BACK_AT_YA,
        (lamp_ctx->currently_on ? "ON_GREEN" : "OFF_GREEN"),
        (lamp_ctx->currently_on ? "ON_RED" : "OFF_RED"),
        (lamp_ctx->currently_on ? "ON" : "OFF")
    );

    if (ret < 0)
    {
        free(resp_str);
        resp_str = NULL;
    }

    return resp_str;
}
