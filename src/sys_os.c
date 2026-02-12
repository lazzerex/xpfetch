/*
 * OS information detection
 */

#include "sysinfo.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>

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
        version_name = "Windows 10";
    } else if (major == 4) {
        version_name = "Windows NT 4.0";
    }
    
    sprintf(buffer, "%s (Build %lu)", version_name, build);
}

void get_os_info(char *buffer, size_t size) {
    const char *reg_path = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
    char product_name[256] = "";
    char version[64] = "";
    char build[64] = "";
    char csd_version[128] = "";
    char version_str[256];
    DWORD major = 0, minor = 0, build_num = 0;
    OSVERSIONINFOEXA osvi;
    
    /* Try reading from registry first (most reliable) */
    if (read_registry_string(HKEY_LOCAL_MACHINE, reg_path, "ProductName", 
                            product_name, sizeof(product_name)) == ERROR_SUCCESS &&
        read_registry_string(HKEY_LOCAL_MACHINE, reg_path, "CurrentVersion", 
                            version, sizeof(version)) == ERROR_SUCCESS &&
        read_registry_string(HKEY_LOCAL_MACHINE, reg_path, "CurrentBuildNumber", 
                            build, sizeof(build)) == ERROR_SUCCESS) {
        
        /* Parse version string (e.g., "5.1" for XP) */
        if (sscanf(version, "%lu.%lu", &major, &minor) >= 1) {
            build_num = atol(build);
            
            /* Get service pack info */
            read_registry_string(HKEY_LOCAL_MACHINE, reg_path, "CSDVersion",
                               csd_version, sizeof(csd_version));
            
            get_version_string(major, minor, build_num, version_str, sizeof(version_str));
            
            /* Try to determine edition from product name */
            if (strstr(product_name, "Home")) {
                if (strlen(csd_version) > 0) {
                    sprintf(buffer, "%s Home Edition %s", version_str, csd_version);
                } else {
                    sprintf(buffer, "%s Home Edition", version_str);
                }
            } else if (strstr(product_name, "Professional") || strstr(product_name, "Pro")) {
                if (strlen(csd_version) > 0) {
                    sprintf(buffer, "%s Professional %s", version_str, csd_version);
                } else {
                    sprintf(buffer, "%s Professional", version_str);
                }
            } else if (strstr(product_name, "Server")) {
                if (strlen(csd_version) > 0) {
                    sprintf(buffer, "%s Server %s", version_str, csd_version);
                } else {
                    sprintf(buffer, "%s Server", version_str);
                }
            } else {
                /* Fallback: use product name as-is */
                if (strlen(csd_version) > 0) {
                    sprintf(buffer, "%s %s", version_str, csd_version);
                } else {
                    sprintf(buffer, "%s", version_str);
                }
            }
            return;
        }
    }
    
    /* Fallback to GetVersionEx if registry read fails */
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEXA));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXA);
    
    #pragma warning(push)
    #pragma warning(disable: 4996)
    if (GetVersionExA((OSVERSIONINFOA*)&osvi)) {
        char edition[64] = "";
        
        get_version_string(osvi.dwMajorVersion, osvi.dwMinorVersion, 
                          osvi.dwBuildNumber, version_str, sizeof(version_str));
        
        if (osvi.wProductType == VER_NT_WORKSTATION) {
            if (osvi.wSuiteMask & VER_SUITE_PERSONAL) {
                strcpy(edition, "Home Edition");
            } else {
                strcpy(edition, "Professional");
            }
        } else {
            strcpy(edition, "Server");
        }
        
        if (strlen(osvi.szCSDVersion) > 0) {
            sprintf(buffer, "%s %s %s", version_str, edition, osvi.szCSDVersion);
        } else {
            sprintf(buffer, "%s %s", version_str, edition);
        }
    } else {
        strcpy(buffer, "Unknown Windows NT");
    }
    #pragma warning(pop)
}
