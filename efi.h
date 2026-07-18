#pragma once

/*
                                                         
                                                         
        __.....__               .--.         .           
    .-''         '.        _.._ |__|       .'|           
   /     .-''"'-.  `.    .' .._|.--.      <  |           
  /     /________\   \   | '    |  |       | |           
  |                  | __| |__  |  |       | | .'''-.    
  \    .-------------'|__   __| |  |       | |/.'''. \   
   \    '-.____...---.   | |    |  | ,.--. |  /    | |   
    `.             .'    | |    |__|//    \| |     | |   
      `''-...... -'      | |        \\    /| |     | |   
                         | |         `'--' | '.    | '.  
                         |_|               '---'   '---' 
 https://github.com/NevermindExpress/efi.h
                                                            */

#include "efi/types.h"
#include "efi/status.h"
#include "efi/protocols.h"
#include "efi/bootservices.h"
#include "efi/runtimeservices.h"
#include "efi/systemtable.h"

#define EFI_H_VERSION 0x01030000
#define EFI_H_VERSION_STRING "1.3"

// The Entry Point prototype, first thing the developer would use...
typedef EFI_STATUS (EFIAPI *EFI_IMAGE_ENTRY_POINT) (
  IN EFI_HANDLE                  ImageHandle,
  IN EFI_SYSTEM_TABLE            *SystemTable
  );

#ifdef _MSC_VER
    #pragma comment(linker, "/ENTRY:EfiMain")
#endif