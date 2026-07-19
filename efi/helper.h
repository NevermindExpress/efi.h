#pragma once
// helper.h - convenience functions for efi.h.
//
// Single-header library pattern: declarations are always visible, but the
// function bodies are only compiled once - in exactly one .c file in your
// project, define EFI_H_HELPER_IMPLEMENTATION before including this header:
//
//   #define EFI_H_HELPER_IMPLEMENTATION
//   #include "helper.h"
//
// Every other file just #include "helper.h" normally and gets plain
// (non-static) declarations - real extern linkage, one compiled copy of
// each function total, not one per translation unit.

#include "efi/types.h"
#include <stdarg.h>

// ---------------------------------------------------------------------
// Declarations - always visible
// ---------------------------------------------------------------------

extern EFI_SYSTEM_TABLE *gST;

VOID EfiHInitHelpers(EFI_SYSTEM_TABLE *SystemTable);

// String helpers (CHAR16 / wide strings - UEFI has no libc to supply these)
UINTN   StrLen(CONST CHAR16 *s);
VOID    StrCpy(CHAR16 *dst, CONST CHAR16 *src);
VOID    StrnCpy(CHAR16 *dst, CONST CHAR16 *src, UINTN n);
VOID    StrCat(CHAR16 *dst, CONST CHAR16 *src);
INTN    StrCmp(CONST CHAR16 *a, CONST CHAR16 *b);
INTN    StrnCmp(CONST CHAR16 *a, CONST CHAR16 *b, UINTN n);
CHAR16  ToLowerChar(CHAR16 c);
INTN    StriCmp(CONST CHAR16 *a, CONST CHAR16 *b);
CHAR16 *StrChr(CONST CHAR16 *s, CHAR16 c);
CHAR16 *StrDuplicate(CONST CHAR16 *s);

// Number -> string conversion (used internally by VPrint, exposed since
// they're independently useful)
UINTN UIntToStr(UINT64 value, UINTN base, BOOLEAN upperCase, CHAR16 *out);
UINTN IntToStr(INT64 value, CHAR16 *out);

// Print() / VPrint() - supported specifiers, kept deliberately small
// (not a full libc printf): %s (CHAR16*), %a (CHAR8*/ASCII), %d (INT64),
// %u (UINT64), %x / %X (hex, lower/upper), %c (CHAR16), %%
VOID EfiHPutStr(CONST CHAR16 *s);
VOID EfiHPutAsciiStr(CONST CHAR8 *s);
VOID VPrint(CONST CHAR16 *fmt, va_list args);
VOID Print(CONST CHAR16 *fmt, ...);
CHAR16 *PoolPrint(CONST CHAR16 *fmt, ...);

// Console helpers
EFI_INPUT_KEY WaitForKey(VOID);
VOID    ClearScreen(VOID);
VOID    SetCursorPosition(UINTN Column, UINTN Row);
VOID    EnableCursor(BOOLEAN Visible);
VOID    SetTextAttribute(UINTN Attribute);

// ---------------------------------------------------------------------
// Implementation - compiled once, only where EFI_H_HELPER_IMPLEMENTATION
// is defined before this header is included
// ---------------------------------------------------------------------
#ifdef EFI_H_HELPER_IMPLEMENTATION

EFI_SYSTEM_TABLE *gST = NULL;

VOID EfiHInitHelpers(EFI_SYSTEM_TABLE *SystemTable) {
	gST = SystemTable;
}

UINTN StrLen(CONST CHAR16 *s) {
	UINTN len = 0;
	while (s[len] != 0) len++;
	return len;
}

VOID StrCpy(CHAR16 *dst, CONST CHAR16 *src) {
	while ((*dst++ = *src++));
}

VOID StrnCpy(CHAR16 *dst, CONST CHAR16 *src, UINTN n) {
	UINTN i = 0;
	for (; i < n && src[i] != 0; i++) dst[i] = src[i];
	for (; i < n; i++) dst[i] = 0;
}

VOID StrCat(CHAR16 *dst, CONST CHAR16 *src) {
	while (*dst) dst++;
	while ((*dst++ = *src++));
}

INTN StrCmp(CONST CHAR16 *a, CONST CHAR16 *b) {
	while (*a && (*a == *b)) { a++; b++; }
	return (INTN)(*a) - (INTN)(*b);
}

INTN StrnCmp(CONST CHAR16 *a, CONST CHAR16 *b, UINTN n) {
	for (UINTN i = 0; i < n; i++) {
		if (a[i] != b[i] || a[i] == 0) return (INTN)(a[i]) - (INTN)(b[i]);
	}
	return 0;
}

CHAR16 ToLowerChar(CHAR16 c) {
	if (c >= L'A' && c <= L'Z') return (CHAR16)(c + (L'a' - L'A'));
	return c;
}

INTN StriCmp(CONST CHAR16 *a, CONST CHAR16 *b) {
	while (*a && (ToLowerChar(*a) == ToLowerChar(*b))) { a++; b++; }
	return (INTN)ToLowerChar(*a) - (INTN)ToLowerChar(*b);
}

CHAR16 *StrChr(CONST CHAR16 *s, CHAR16 c) {
	while (*s) {
		if (*s == c) return (CHAR16 *)s;
		s++;
	}
	return (c == 0) ? (CHAR16 *)s : NULL;
}

CHAR16 *StrDuplicate(CONST CHAR16 *s) {
	UINTN size = (StrLen(s) + 1) * sizeof(CHAR16);
	VOID *buf = NULL;
	EFI_STATUS status = gST->BootServices->AllocatePool(EfiBootServicesData, size, &buf);
	if (EFI_ERROR(status) || buf == NULL) return NULL;
	StrCpy((CHAR16 *)buf, s);
	return (CHAR16 *)buf;
}

UINTN UIntToStr(UINT64 value, UINTN base, BOOLEAN upperCase, CHAR16 *out) {
	CONST CHAR16 *digitsLower = L"0123456789abcdef";
	CONST CHAR16 *digitsUpper = L"0123456789ABCDEF";
	CONST CHAR16 *digits = upperCase ? digitsUpper : digitsLower;
	CHAR16 tmp[32];
	UINTN i = 0;

	if (value == 0) {
		out[0] = L'0';
		out[1] = 0;
		return 1;
	}

	while (value != 0) {
		tmp[i++] = digits[value % base];
		value /= base;
	}

	UINTN len = i;
	for (UINTN j = 0; j < len; j++) out[j] = tmp[len - 1 - j];
	out[len] = 0;
	return len;
}

UINTN IntToStr(INT64 value, CHAR16 *out) {
	if (value < 0) {
		out[0] = L'-';
		return 1 + UIntToStr((UINT64)(-value), 10, FALSE, out + 1);
	}
	return UIntToStr((UINT64)value, 10, FALSE, out);
}

VOID EfiHPutStr(CONST CHAR16 *s) {
	gST->ConOut->OutputString(gST->ConOut, (CHAR16 *)s);
}

VOID EfiHPutAsciiStr(CONST CHAR8 *s) {
	CHAR16 buf[2] = { 0, 0 };
	while (*s) {
		buf[0] = (CHAR16)(UINT8)(*s);
		gST->ConOut->OutputString(gST->ConOut, buf);
		s++;
	}
}

UINTN EfiHFormatToBuffer(CHAR16 *out, UINTN outMax, CONST CHAR16 *fmt, va_list args) {
	CHAR16 numbuf[32];
	UINTN pos = 0;

#define EFI_H_EMIT(ch) do { if (pos + 1 < outMax) out[pos++] = (ch); } while (0)
#define EFI_H_EMIT_STR(s) do { for (CONST CHAR16 *p = (s); *p; p++) EFI_H_EMIT(*p); } while (0)

	for (UINTN i = 0; fmt[i] != 0; i++) {
		if (fmt[i] != L'%') {
			EFI_H_EMIT(fmt[i]);
			continue;
		}

		i++;
		switch (fmt[i]) {
			case L's': {
				CHAR16 *s = va_arg(args, CHAR16 *);
				if (s) EFI_H_EMIT_STR(s);
				break;
			}
			case L'a': {
				CHAR8 *s = va_arg(args, CHAR8 *);
				if (s) { for (CHAR8 *p = s; *p; p++) EFI_H_EMIT((CHAR16)(UINT8)(*p)); }
				break;
			}
			case L'd': {
				int v = va_arg(args, int);
				IntToStr((INT64)v, numbuf);
				EFI_H_EMIT_STR(numbuf);
				break;
			}
			case L'u': {
				UINT32 v = va_arg(args, UINT32);
				UIntToStr((UINT64)v, 10, FALSE, numbuf);
				EFI_H_EMIT_STR(numbuf);
				break;
			}
			case L'x': {
				UINT32 v = va_arg(args, UINT32);
				UIntToStr((UINT64)v, 16, FALSE, numbuf);
				EFI_H_EMIT_STR(numbuf);
				break;
			}
			case L'X': {
				UINT64 v = va_arg(args, UINT64);
				UIntToStr(v, 16, TRUE, numbuf);
				EFI_H_EMIT_STR(numbuf);
				break;
			}
			case L'c': {
				CHAR16 v = (CHAR16)va_arg(args, int);
				EFI_H_EMIT(v);
				break;
			}
			case L'%': {
				EFI_H_EMIT(L'%');
				break;
			}
			default: {
				EFI_H_EMIT(L'%');
				EFI_H_EMIT(fmt[i]);
				break;
			}
		}
	}

	out[(pos < outMax) ? pos : outMax - 1] = 0;

#undef EFI_H_EMIT
#undef EFI_H_EMIT_STR

	return pos;
}

#define EFI_H_PRINT_BUFFER_SIZE 1024

VOID VPrint(CONST CHAR16 *fmt, va_list args) {
	CHAR16 buf[EFI_H_PRINT_BUFFER_SIZE];
	EfiHFormatToBuffer(buf, EFI_H_PRINT_BUFFER_SIZE, fmt, args);
	EfiHPutStr(buf);
}

VOID Print(CONST CHAR16 *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	VPrint(fmt, args);
	va_end(args);
}

CHAR16 *PoolPrint(CONST CHAR16 *fmt, ...) {
	CHAR16 buf[EFI_H_PRINT_BUFFER_SIZE];
	va_list args;

	va_start(args, fmt);
	EfiHFormatToBuffer(buf, EFI_H_PRINT_BUFFER_SIZE, fmt, args);
	va_end(args);

	return StrDuplicate(buf);
}

EFI_INPUT_KEY WaitForKey(VOID) {
	UINTN index = 0;
	EFI_INPUT_KEY key = { 0 };

	gST->BootServices->WaitForEvent(1, &gST->ConIn->WaitForKey, &index);
	gST->ConIn->ReadKeyStroke(gST->ConIn, &key);

	return key;
}

VOID ClearScreen(VOID) {
	gST->ConOut->ClearScreen(gST->ConOut);
}

VOID SetCursorPosition(UINTN Column, UINTN Row) {
	gST->ConOut->SetCursorPosition(gST->ConOut, Column, Row);
}

VOID EnableCursor(BOOLEAN Visible) {
	gST->ConOut->EnableCursor(gST->ConOut, Visible);
}

VOID SetTextAttribute(UINTN Attribute) {
	gST->ConOut->SetAttribute(gST->ConOut, Attribute);
}

#endif // EFI_H_HELPER_IMPLEMENTATION