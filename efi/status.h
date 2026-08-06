#pragma once
// UEFI Spec Appendix D: Status Codes

#define EFI_SUCCESS 0										// The operation completed successfully.
#define EFI_LOAD_ERROR				0x8000000000000001ULL	// The image failed to load.
#define EFI_INVALID_PARAMETER		0x8000000000000002ULL	// A parameter was incorrect.
#define EFI_UNSUPPORTED				0x8000000000000003ULL	// The operation is not supported.
#define EFI_BAD_BUFFER_SIZE			0x8000000000000004ULL	// The buffer was not the proper size for the request.
#define EFI_BUFFER_TOO_SMALL		0x8000000000000005ULL	// The buffer is not large enough to hold the requested data.The required buffer size is returned in the appropriate parameter when this error occurs.
#define EFI_NOT_READY				0x8000000000000006ULL	// There is no data pending upon return.
#define EFI_DEVICE_ERROR			0x8000000000000007ULL	// The physical device reported an error while attempting the operation.
#define EFI_WRITE_PROTECTED			0x8000000000000008ULL	// The device cannot be written to.
#define EFI_OUT_OF_RESOURCES		0x8000000000000009ULL	// A resource has run out.
#define EFI_VOLUME_CORRUPTED		0x800000000000000AULL	// An inconstancy was detected on the file system causing the operating to fail.
#define EFI_VOLUME_FULL				0x800000000000000BULL	// There is no more space on the file system.
#define EFI_NO_MEDIA				0x800000000000000CULL	// The device does not contain any medium to perform the operation.
#define EFI_MEDIA_CHANGED			0x800000000000000DULL	// The medium in the device has changed since the last access.
#define EFI_NOT_FOUND				0x800000000000000EULL	// The item was not found.
#define EFI_ACCESS_DENIED			0x800000000000000FULL	//  Access was denied.
#define EFI_NO_RESPONSE				0x8000000000000010ULL	//  The server was not found or did not respond to the request.
#define EFI_NO_MAPPING				0x8000000000000011ULL	// A mapping to a device does not exist.
#define EFI_TIMEOUT					0x8000000000000012ULL	// The timeout time expired.
#define EFI_NOT_STARTED				0x8000000000000013ULL	// The protocol has not been started.
#define EFI_ALREADY_STARTED			0x8000000000000014ULL	// The protocol has already been started.
#define EFI_ABORTED					0x8000000000000015ULL	// The operation was aborted.
#define EFI_ICMP_ERROR				0x8000000000000016ULL	// An ICMP error occurred during the network operation.
#define EFI_TFTP_ERROR				0x8000000000000017ULL	// A TFTP error occurred during the network operation.
#define EFI_PROTOCOL_ERROR			0x8000000000000018ULL	// A protocol error occurred during the network operation.
#define EFI_INCOMPATIBLE_VERSION	0x8000000000000019ULL	// The function encountered an internal version that was incompatible with a version requested by the caller.
#define EFI_SECURITY_VIOLATION		0x800000000000001AULL	// The function was not performed due to a security violation.
#define EFI_CRC_ERROR				0x800000000000001BULL	// A CRC error was detected.
#define EFI_END_OF_MEDIA			0x800000000000001CULL	// Beginning or end of media was reached
#define EFI_END_OF_FILE				0x800000000000001FULL	// The end of the file was reached.
#define EFI_INVALID_LANGUAGE		0x8000000000000020ULL	// The language specified was invalid.
#define EFI_COMPROMISED_DATA		0x8000000000000021ULL	// The security status of the data is unknown or compromised and the data must be updated or replaced to restore a valid security status.
#define EFI_IP_ADDRESS_CONFLICT		0x8000000000000022ULL	// There is an address conflict address allocation
#define EFI_HTTP_ERROR				0x8000000000000023ULL	// A HTTP error occurred during the network operation.

#define EFI_WARN_UNKNOWN_GLYPH 1	// The string contained one or more characters that the device could not render and were skipped.
#define EFI_WARN_DELETE_FAILURE  2	// The handle was closed, but the file was not deleted.
#define EFI_WARN_WRITE_FAILURE 3	// The handle was closed, but the data to the file was not flushed properly.
#define EFI_WARN_BUFFER_TOO_SMALL 4	// The resulting buffer was too small, and the data was truncated to the buffer size.
#define EFI_WARN_STALE_DATA 5		// The data has not been updated within the timeframe set by local policy for this type of data.
#define EFI_WARN_FILE_SYSTEM 6		// The resulting buffer contains UEFI - compliant file system.
#define EFI_WARN_RESET_REQUIRED 7	// The operation will be processed across a system reset