#include "logUtils.h"
#include <fabgl.h>

/**
 * @brief Prints a message to all available loggers.
 *
 * @param message the message you want to print
 * @param ...
 */
void LogUtils::xprintf(const char *message, ...)
{
    va_list ap;
    va_start(ap, message);
    int size = vsnprintf(nullptr, 0, message, ap) + 1;
    if (size > 0)
    {
        va_end(ap);
        va_start(ap, message);
        char buf[size + 1];
        vsnprintf(buf, size, message, ap);
        Serial.write(buf);
        Serial.write("\n");
    }
    va_end(ap);
}