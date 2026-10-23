/*
 * OS information detection
 */

#include "sysinfo.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Read version info from registry - more reliable than GetVersionEx */
static LONG read_registry_string(HKEY hKey, const char *subKey, const char *valueName,
                                  char *buffer, DWORD bufSize) {
    HKEY hSubKey;
    DWORD type = REG_SZ;
    LONG result;

    result = RegOpenKeyExA(hKey, subKey, 0, KEY_READ, &hSubKey);
    if (result != ERROR_SUCCESS) {
        return result;
    }

    result = RegQueryValueExA(hSubKey, valueName, NULL, &type,
                             (LPBYTE)buffer, &bufSize);
    RegCloseKey(hSubKey);
    return result;
}

static int read_registry_dword(HKEY hKey, const char *subKey, const char *valueName,
                               DWORD *value) {
    HKEY hSubKey;
    DWORD type = REG_DWORD;
    DWORD size = sizeof(DWORD);
    LONG result;

    if (RegOpenKeyExA(hKey, subKey, 0, KEY_READ, &hSubKey) != ERROR_SUCCESS) {
        return 0;
    }

    result = RegQueryValueExA(hSubKey, valueName, NULL, &type, (LPBYTE)value, &size);
    RegCloseKey(hSubKey);
    return result == ERROR_SUCCESS && type == REG_DWORD;
}

int get_nt_version(unsigned long *major, unsigned long *minor, unsigned long *build) {
    const char *reg_path = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
    char version[64] = "";
    char build_str[64] = "";
    DWORD reg_major, reg_minor;
    OSVERSIONINFOA osvi;

    if (read_registry_string(HKEY_LOCAL_MACHINE, reg_path, "CurrentBuildNumber",
                            build_str, sizeof(build_str)) == ERROR_SUCCESS) {
        *build = strtoul(build_str, NULL, 10);

        if (read_registry_dword(HKEY_LOCAL_MACHINE, reg_path, "CurrentMajorVersionNumber", &reg_major) &&
            read_registry_dword(HKEY_LOCAL_MACHINE, reg_path, "CurrentMinorVersionNumber", &reg_minor)) {
            *major = reg_major;
            *minor = reg_minor;
            return 1;
        }

        if (read_registry_string(HKEY_LOCAL_MACHINE, reg_path, "CurrentVersion",
                                version, sizeof(version)) == ERROR_SUCCESS &&
            sscanf(version, "%lu.%lu", major, minor) == 2) {
            return 1;
        }
    }

    ZeroMemory(&osvi, sizeof(OSVERSIONINFOA));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
    if (GetVersionExA(&osvi)) {
        *major = osvi.dwMajorVersion;
        *minor = osvi.dwMinorVersion;
        *build = osvi.dwBuildNumber;
        return 1;
    }

    return 0;
}

static void get_version_string(DWORD major, DWORD minor, DWORD build, char *buffer, size_t size) {
    const char *version_name = "Unknown Windows";

    if (major == 5) {
        if (minor == 0) {
            version_name = "Windows 2000";
        } else if (minor == 1) {
            version_name = "Windows XP";
        } else if (minor == 2) {
            version_name = "Windows Server 2003";
        }
    } else if (major == 6) {
        if (minor == 0) {
            version_name = "Windows Vista";
        } else if (minor == 1) {
            version_name = "Windows 7";
        } else if (minor == 2) {
            version_name = "Windows 8";
        } else if (minor == 3) {
            version_name = "Windows 8.1";
        }
    } else if (major == 10) {
        version_name = (build >= 22000) ? "Windows 11" : "Windows 10";
    } else if (major == 4) {
        version_name = "Windows NT 4.0";
    }

    snprintf(buffer, size, "%s (Build %lu)", version_name, build);
}

static const char *edition_from_product_name(const char *product_name) {
    if (strstr(product_name, "Server")) {
        return "Server";
    }
    if (strstr(product_name, "Home")) {
        return "Home Edition";
    }
    if (strstr(product_name, "Professional") || strstr(product_name, "Pro")) {
        return "Professional";
    }
    return "";
}

void get_os_info(char *buffer, size_t size) {
    const char *reg_path = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
    char product_name[256] = "";
    char csd_version[128] = "";
    char version_str[256];
    const char *edition = "";
    unsigned long major, minor, build;
    OSVERSIONINFOEXA osvi;

    if (!get_nt_version(&major, &minor, &build)) {
        strncpy(buffer, "Unknown Windows NT", size - 1);
        buffer[size - 1] = '\0';
        return;
    }

    get_version_string(major, minor, build, version_str, sizeof(version_str));

    if (read_registry_string(HKEY_LOCAL_MACHINE, reg_path, "ProductName",
                            product_name, sizeof(product_name)) == ERROR_SUCCESS) {
        edition = edition_from_product_name(product_name);
        read_registry_string(HKEY_LOCAL_MACHINE, reg_path, "CSDVersion",
                            csd_version, sizeof(csd_version));
    } else {
        ZeroMemory(&osvi, sizeof(OSVERSIONINFOEXA));
        osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXA);
        if (GetVersionExA((OSVERSIONINFOA*)&osvi)) {
            if (osvi.wProductType != VER_NT_WORKSTATION) {
                edition = "Server";
            } else if (osvi.wSuiteMask & VER_SUITE_PERSONAL) {
                edition = "Home Edition";
            } else {
                edition = "Professional";
            }
            snprintf(csd_version, sizeof(csd_version), "%s", osvi.szCSDVersion);
        }
    }

    snprintf(buffer, size, "%s%s%s%s%s", version_str,
             edition[0] ? " " : "", edition,
             csd_version[0] ? " " : "", csd_version);
}
