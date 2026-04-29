/*
 * XPFetch configuration parser
 */

#include "config.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

static char *trim_left(char *text) {
    while (*text != '\0' && isspace((unsigned char)*text)) {
        text++;
    }

    return text;
}

static void trim_right(char *text) {
    size_t length;

    length = strlen(text);
    while (length > 0 && isspace((unsigned char)text[length - 1])) {
        text[length - 1] = '\0';
        length--;
    }
}

static int equals_ignore_case(const char *left, const char *right) {
    while (*left != '\0' && *right != '\0') {
        if (tolower((unsigned char)*left) != tolower((unsigned char)*right)) {
            return 0;
        }

        left++;
        right++;
    }

    return *left == '\0' && *right == '\0';
}

static int parse_bool(const char *value) {
    if (equals_ignore_case(value, "1") ||
        equals_ignore_case(value, "true") ||
        equals_ignore_case(value, "yes") ||
        equals_ignore_case(value, "on")) {
        return 1;
    }

    if (equals_ignore_case(value, "0") ||
        equals_ignore_case(value, "false") ||
        equals_ignore_case(value, "no") ||
        equals_ignore_case(value, "off")) {
        return 0;
    }

    return 1;
}

static void copy_string(char *destination, size_t size, const char *source) {
    if (size == 0) {
        return;
    }

    strncpy(destination, source, size - 1);
    destination[size - 1] = '\0';
}

void config_init(XPFetchConfig *config) {
    if (config == NULL) {
        return;
    }

    config->show_os = 1;
    config->show_host = 1;
    config->show_kernel = 1;
    config->show_uptime = 1;
    config->show_shell = 1;
    config->show_resolution = 1;
    config->show_cpu = 1;
    config->show_gpu = 1;
    config->show_memory = 1;
    config->show_disk = 1;
    copy_string(config->logo, sizeof(config->logo), "xp");
}

int load_config(XPFetchConfig *config, const char *path) {
    FILE *file;
    char line[256];
    int loaded;

    if (config == NULL || path == NULL) {
        return 0;
    }

    file = fopen(path, "r");
    if (file == NULL) {
        return 0;
    }

    loaded = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        char *key;
        char *value;
        char *equals;

        trim_right(line);
        key = trim_left(line);

        if (*key == '\0' || *key == '#' || *key == ';') {
            continue;
        }

        equals = strchr(key, '=');
        if (equals == NULL) {
            continue;
        }

        *equals = '\0';
        value = trim_left(equals + 1);
        trim_right(key);
        key = trim_left(key);

        if (*key == '\0' || *value == '\0') {
            continue;
        }

        if (equals_ignore_case(key, "show_os")) {
            config->show_os = parse_bool(value);
        } else if (equals_ignore_case(key, "show_host")) {
            config->show_host = parse_bool(value);
        } else if (equals_ignore_case(key, "show_kernel")) {
            config->show_kernel = parse_bool(value);
        } else if (equals_ignore_case(key, "show_uptime")) {
            config->show_uptime = parse_bool(value);
        } else if (equals_ignore_case(key, "show_shell")) {
            config->show_shell = parse_bool(value);
        } else if (equals_ignore_case(key, "show_resolution")) {
            config->show_resolution = parse_bool(value);
        } else if (equals_ignore_case(key, "show_cpu")) {
            config->show_cpu = parse_bool(value);
        } else if (equals_ignore_case(key, "show_gpu")) {
            config->show_gpu = parse_bool(value);
        } else if (equals_ignore_case(key, "show_memory")) {
            config->show_memory = parse_bool(value);
        } else if (equals_ignore_case(key, "show_disk")) {
            config->show_disk = parse_bool(value);
        } else if (equals_ignore_case(key, "logo")) {
            copy_string(config->logo, sizeof(config->logo), value);
        }

        loaded = 1;
    }

    fclose(file);
    return loaded;
}