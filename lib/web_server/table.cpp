#include <Arduino.h>
#include "status.h"
#include "table.h"

String concat_data_table(Status *status) {
    char buffer[255];
    String html_code = "<table><thead><tr>";
    html_code.concat("<th>Parameter</th><th>Wert</th>");
    html_code.concat("</tr></thead><tbody>");
    add_table_row(buffer, &html_code, "Ofentemperatur", "&#176;C", status->probe_temperature);
    add_table_row(buffer, &html_code, "Umgebungstemperatur", "&#176;C", status->ambient_temperature);
    add_table_row(buffer, &html_code, "Batteriespannung", "V", status->battery_voltage);
    html_code.concat("</tbody></table>");
    return html_code;
}

String concat_json(Status *status) {
    char buffer[255];
    String json = "{";
    add_json_entry(buffer, &json, "probe_temperature", status->probe_temperature);
    add_json_entry(buffer, &json, "ambient_temperature", status->ambient_temperature);
    add_json_entry(buffer, &json, "battery_voltage", status->battery_voltage);
    json.concat("\"\":0}");
    return json;
}

void add_json_entry(char *buffer, String *json_buffer, const char *name, const float data) {
    sprintf(buffer, "\"%s\": %.2f,", name, data);
    json_buffer->concat(buffer);
}

void add_table_row(char *buffer, String *html_buffer, const char *name, const char *unit, float data) {
    sprintf(buffer, "<tr><td>%s</td><td>%.2f %s</td></tr>", name, data, unit);
    html_buffer->concat(buffer);
}

void add_table_row(char *buffer, String *html_buffer, const char *name, const char *unit, int32 data) {
    sprintf(buffer, "<tr><td>%s</td><td>%d %s</td></tr>", name, data, unit);
    html_buffer->concat(buffer);
}

void add_table_row(char *buffer, String *html_buffer, const char *name, const char *unit, bool data) {
    String state;
    if (data) {
        state = "true";
    } else {
        state = "false";
    }
    sprintf(buffer, "<tr><td>%s</td><td>%d %s</td></tr>", name, data, unit);
    html_buffer->concat(buffer);
}